/*
 * Server.cpp
 *
 *  Created on: 2017. 3. 8.
 *      Author: LG CNS
 */

#include "Server.h"
#include "Session.h"
#include <boost/bind.hpp>

using namespace boost::asio::ip;

Server::Server( boost::asio::io_service& ioService, unsigned short port)
: _acceptor( ioService, tcp::endpoint( tcp::v4(), port)),
  _socket( ioService ) {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}

Server::~Server() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}

/// @brief TCP 연결을 기다린다
void Server::start() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	_doAccept();
}

// @brief TCP 연결을 더이상 기다리지 않는다.
void Server::stop() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	boost::system::error_code ec;
	_acceptor.close(ec);
	std::cout << "close - " << ec.message() << std::endl;
}

// accept 되면 handler 호출
void Server::_doAccept() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;

	_acceptor.async_accept( _socket, boost::bind( &Server::_acceptHandler, this, boost::asio::placeholders::error ) );
}

// 성공이면 세션 생성하여 session start 수행 후 다시 accept 수행
// operation_aborted 면 더이상 수행하지 않고 종료 (시스템 종료시에도 사용됨, 종료 조건 )
// 그 외 error 인 경우는 다시 기다림
void Server::_acceptHandler(const boost::system::error_code& ec) {
	std::cout << __PRETTY_FUNCTION__ << " - " << ec << std::endl;
	std::cout << ec.message() << std::endl;

	if ( !ec )  {
		std::string ip = _socket.remote_endpoint().address().to_string();
		unsigned short port = _socket.remote_endpoint().port();
		std::cout << "connect from ip = " << ip << ":" << port << std::endl;

		auto session = std::make_shared<Session>( std::move(_socket) );
		session->start();

		// 다시 접속을 기다림
		stop();
		_doAccept();
	} else if ( ec == boost::asio::error::operation_aborted ) {
		std::cout << "operation_aborted. stop listen." << std::endl;
		// 다시 접속하지 않음
	} else {
		std::cout << "error - " << ec.message() << " listen again." << std::endl;
		// 다시 접속을 기다림
		_doAccept();
	}
}
