
#include "Server.h"
#include "Session.h"
#include <boost/bind.hpp>

using namespace boost::asio::ip;

Server::Server( boost::asio::io_service& ioService, unsigned short port)
	: _logger( log4cplus::Logger::getInstance("echo.Server") ),
	  _ioService( ioService ),
	  _acceptor( ioService, tcp::endpoint( tcp::v4(), port)) {
	LOG4CPLUS_TRACE(_logger, __PRETTY_FUNCTION__ );
}

Server::~Server() {
	LOG4CPLUS_TRACE(_logger, __PRETTY_FUNCTION__ );
}

/// @brief TCP 연결을 기다린다
void Server::start() {
	LOG4CPLUS_TRACE(_logger, __PRETTY_FUNCTION__ );
	_doAccept();
}

// @brief TCP 연결을 더이상 기다리지 않는다.
void Server::stop() {
	LOG4CPLUS_TRACE(_logger, __PRETTY_FUNCTION__ );

	boost::system::error_code ec;
	_acceptor.close(ec);

	LOG4CPLUS_DEBUG(_logger, "close - " << ec.message() );
}

// accept 되면 handler 호출
void Server::_doAccept() {
	LOG4CPLUS_TRACE(_logger, __PRETTY_FUNCTION__ );

	auto pSession = std::make_shared<Session>( _ioService );
	tcp::socket& socket = pSession->socket();
	auto handler = boost::bind( &Server::_acceptHandler, this,
			pSession, boost::asio::placeholders::error );

	_acceptor.async_accept( socket, handler );
}

// 성공이면 세션 생성하여 session start 수행 후 다시 accept 수행
// operation_aborted 면 더이상 수행하지 않고 종료 (시스템 종료시에도 사용됨, 종료 조건 )
// 그 외 error 인 경우는 다시 기다림
void Server::_acceptHandler(std::shared_ptr<Session> pSession, const boost::system::error_code& ec) {
	LOG4CPLUS_TRACE(_logger, __PRETTY_FUNCTION__ );
	LOG4CPLUS_DEBUG(_logger, ec.message() );

	if ( pSession == nullptr ) {
		LOG4CPLUS_ERROR(_logger, "pSession is nullptr" );
		return;
	}

	tcp::socket& socket = pSession->socket();

	if ( !ec )  {
		std::string ip = socket.remote_endpoint().address().to_string();
		unsigned short port = socket.remote_endpoint().port();
		LOG4CPLUS_INFO(_logger, "connect from ip = " << ip << ":" << port );

		pSession->start();
		// 다시 접속을 기다림
		_doAccept();
	} else if ( ec == boost::asio::error::operation_aborted ) {
		LOG4CPLUS_INFO(_logger, "operation_aborted. stop listen." );
		// 다시 접속하지 않음
	} else if ( ec ){
		LOG4CPLUS_ERROR(_logger, "error - " << ec.message() << " listen again." );
		// 다시 접속을 기다림
		_doAccept();
	}
}
