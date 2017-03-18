/*
 * Server.h
 *
 *  Created on: 2017. 3. 8.
 *      Author: LG CNS
 */

#ifndef SERVER_H_
#define SERVER_H_

#define BOOST_ASIO_ENABLE_HANDLER_TRACKING
#include <iostream>
#include <boost/asio.hpp>
#include <log4cplus/loggingmacros.h>
#include "Session.h"
///
/// start
///   |
///   v----<------+ 성공, or 실패시 다시 accept
///   |           |
/// doAccept   acceptHandler ( abort 시만 종료 )
///   |           ^
///   v           |
///     io_service
///
class Server {
public:
	Server( boost::asio::io_service& ioService, unsigned short port);
	~Server();

	/// @brief TCP 연결을 기다린다
	void start();

	// @brief TCP 연결을 더이상 기다리지 않는다.
	void stop();
private:
	// logger
	log4cplus::Logger _logger;

	// io_service
	boost::asio::io_service& _ioService;

	// acceptor
	boost::asio::ip::tcp::acceptor _acceptor;

	void _doAccept();
	void _acceptHandler(std::shared_ptr<Session> pSession, const boost::system::error_code& ec);
};

#endif /* SERVER_H_ */
