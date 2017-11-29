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

	auto buffer = boost::asio::buffer( _recvArray );
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
    	for ( size_t i = 0; i<recvBytes; ++i ) std::cout << _recvArray[i];
    	std::cout << std::endl;

        // 읽은 data를 parsed 후
    	//  - packet이 완성되면 doCommand
        //  - 아직 완성이 안된 경우는 추가로 doRead
        //  - 파싱중 오류 발생하면 parsed buffer를 지우고 doRead
        // decode 결과 해석된 명령 수행
        //  - 정상 수행완료하면 결과 doWrite ( 실패 오류 모두 )
    	DecodeState result = _request.decode( _recvArray.data(), recvBytes);
    	if ( result == COMPLETE ) {
    		LOG4CPLUS_DEBUG(_logger, _request );
    		if ( _request.getParsingError() == 0 ) {
				_response.reset();
				_response.header.putField( 'E', 'D', _request.body().size());
				std::copy( _request.body().begin(),
						_request.body().end(),
						std::back_inserter(_response.body));
    		} else {
    			LOG4CPLUS_ERROR(_logger, "invalid request : " << _request.getParsingError() );
				_response.reset();
				_response.header.putField( 'E', 'N', 1);
				_response.body.push_back( _request.getParsingError() );
    		}

			LOG4CPLUS_DEBUG(_logger, _response );
			_sendBuffer.push_back( boost::asio::buffer(_response.header) );
			_sendBuffer.push_back( boost::asio::buffer(_response.body) );
			_doWrite();
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
void Session::_doWrite() {
	LOG4CPLUS_TRACE(_logger, __PRETTY_FUNCTION__ );

	//auto buffer = boost::asio::buffer( _sendBuf );
	auto handler = boost::bind( &Session::_writeHandler, shared_from_this(),
			boost::asio::placeholders::error);
	boost::asio::async_write( _socket, _sendBuffer, handler );
	LOG4CPLUS_TRACE(_logger, "write " << boost::asio::buffer_size(_sendBuffer) << " bytes." );
}

// write 완료 후 다시 read
void Session::_writeHandler(const boost::system::error_code& ec) {
	LOG4CPLUS_TRACE(_logger, __PRETTY_FUNCTION__ );

    if ( !ec )  {
		LOG4CPLUS_DEBUG(_logger, "write succeed. clean request and read again.");

		_sendBuffer.clear();
		// write 성공하면 버퍼 request 지우고 read 의뢰
		_doRead();
	} else {
		LOG4CPLUS_ERROR(_logger, "error - " << ec.message() << " stop read.");
	}
}
