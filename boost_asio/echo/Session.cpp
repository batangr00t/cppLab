/*
 * Session.cpp
 *
 *  Created on: 2017. 3. 8.
 *      Author: LG CNS
 */

#include "Session.h"
#include <boost/bind.hpp>
#include <boost/asio/use_future.hpp>
#include <iostream>

Session::Session(boost::asio::io_service& ioService)
	: _logger( log4cplus::Logger::getInstance("echo.Session") ),
	  _socket( ioService ) {
	LOG4CPLUS_TRACE(_logger, __PRETTY_FUNCTION__ );
}

Session::~Session() {
	LOG4CPLUS_TRACE(_logger, __PRETTY_FUNCTION__ );
}

tcp::socket& Session::socket() {
	return _socket;
}
void Session::start() {
	LOG4CPLUS_TRACE(_logger, __PRETTY_FUNCTION__ );
	_doRead();
}

void Session::stop() {
	LOG4CPLUS_TRACE(_logger, __PRETTY_FUNCTION__ );

	boost::system::error_code ec;

	_socket.shutdown( tcp::socket::shutdown_both, ec);
	LOG4CPLUS_DEBUG(_logger, "shutdown - " << ec.message() );

	_socket.close(ec);
	LOG4CPLUS_DEBUG(_logger, "close - " << ec.message() );
}

void Session::_doRead() {
	LOG4CPLUS_TRACE(_logger, __PRETTY_FUNCTION__ );

	_request.reset();
	_doReadWithoutReset();
}

void Session::_doReadWithoutReset() {
	LOG4CPLUS_TRACE(_logger, __PRETTY_FUNCTION__ );

	auto buffer = boost::asio::buffer( _recvBuf );
	auto handler = boost::bind( &Session::_readHandler, shared_from_this(),
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred );
	_socket.async_read_some( buffer, handler );
}

// 읽은 데이터 parsing 후 doWrite
void Session::_readHandler(const boost::system::error_code& ec, size_t recvBytes) {
	LOG4CPLUS_TRACE(_logger, __PRETTY_FUNCTION__ );

	if ( !ec )  {
    	LOG4CPLUS_DEBUG(_logger, "received " << recvBytes << " bytes");
    	for ( size_t i = 0; i<recvBytes; ++i ) std::cout << _recvBuf[i];
    	std::cout << std::endl;

        // 읽은 data를 parsed 후
    	//  - packet이 완성되면 doCommand
        //  - 아직 완성이 안된 경우는 추가로 doRead
        //  - 파싱중 오류 발생하면 parsed buffer를 지우고 doRead
        // decode 결과 해석된 명령 수행
        //  - 정상 수행완료하면 결과 doWrite ( 실패 오류 모두 )
    	DecodeState result = _request.parse( _recvBuf.data(), recvBytes);
    	if ( result == COMPLETE ) {
    		LOG4CPLUS_DEBUG(_logger, _request );
    		size_t sendBytes = _request.body().size();
    		std::copy_n( _request.body().data(), sendBytes, _sendBuf.begin() );
    		_doWrite(sendBytes);
    	} else if ( result == PARSING_ERROR ) {
    		LOG4CPLUS_ERROR(_logger, "parse error. reset request. read" << result );
    		_doRead();
    	} else {
    		// read continue
    		_doReadWithoutReset();
    	}
	} else if ( ec == boost::asio::error::operation_aborted ) {
		LOG4CPLUS_INFO(_logger, "operation_aborted. stop" );
	} else if ( ec == boost::asio::error::eof ) {
		LOG4CPLUS_DEBUG(_logger, "eof. stop" );
	} else {
		LOG4CPLUS_ERROR(_logger, "error stop - " << ec.message() );
	}
}

// write to OS
void Session::_doWrite(std::size_t length) {
	LOG4CPLUS_TRACE(_logger, __PRETTY_FUNCTION__ << " " << length << " bytes");

	auto buffer = boost::asio::buffer( _sendBuf, length );
	auto handler = boost::bind( &Session::_writeHandler, shared_from_this(),
			boost::asio::placeholders::error);
	boost::asio::async_write( _socket, buffer, handler );
}

// write 완료 후 다시 read
void Session::_writeHandler(const boost::system::error_code& ec) {
	LOG4CPLUS_TRACE(_logger, __PRETTY_FUNCTION__ );

    if ( !ec )  {
		LOG4CPLUS_DEBUG(_logger, "write succeed. clean request and read again.");

		// write 성공하면 버퍼 request 지우고 read 의뢰
		_doRead();
	} else {
		LOG4CPLUS_ERROR(_logger, "error - " << ec.message() << " stop read.");
	}
}
