/*
 * Session.cpp
 *
 *  Created on: 2017. 3. 8.
 *      Author: LG CNS
 */

#include "Session.h"
#include <boost/bind.hpp>

Session::Session(tcp::socket socket)
: _socket( std::move(socket) ) {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}

Session::~Session() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void Session::start() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	_doRead();
}

void Session::stop() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	boost::system::error_code ec;
	_socket.shutdown( boost::asio::ip::tcp::socket::shutdown_both, ec);
	std::cout << "shutdown - " << ec.message() << std::endl;
	_socket.close(ec);
	std::cout << "close - " << ec.message() << std::endl;
}

void Session::_doRead() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;

	if ( ++count > 2 ) {
		std::cout << "read count is over - " << count << std::endl;
		stop();
	} else {
		auto buffer = boost::asio::buffer( _data, MAX_LENGTH );
		auto handler = boost::bind( &Session::_readHandler, shared_from_this(),
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred );
		_socket.async_read_some( buffer, handler );
	}
}

// 읽은 데이터 parsing 후 doWrite
void Session::_readHandler(const boost::system::error_code& ec, size_t recvBytes) {
	std::cout << __PRETTY_FUNCTION__ << std::endl;

    if ( !ec )  {
    	std::cout << "recvBytes = " << recvBytes << std::endl;

		// write 의뢰
		_doWrite( recvBytes );
	} else if ( ec == boost::asio::error::operation_aborted ) {
		std::cout << "operation_aborted. stop" << std::endl;
	} else if ( ec == boost::asio::error::eof ) {
		std::cout << "eof. stop" << std::endl;
	} else {
		std::cout << "error - " << ec.message() << std::endl;
	}
}

// write to OS
void Session::_doWrite(std::size_t length) {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	auto buffer = boost::asio::buffer( _data, length );
	auto handler = boost::bind( &Session::_writeHandler, shared_from_this(),
			boost::asio::placeholders::error);
	boost::asio::async_write( _socket, buffer, handler );
}

// write 완료 후 다시 read
void Session::_writeHandler(const boost::system::error_code& ec) {
	std::cout << __PRETTY_FUNCTION__ << std::endl;

    if ( !ec )  {
    	std::cout << "write succeed. read again." << std::endl;

		// read 의뢰
		_doRead();
	} else {
		std::cout << "error - " << ec.message() << " stop read." << std::endl;
	}
}
