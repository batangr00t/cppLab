/*
 * Session.h
 *
 *  Created on: 2017. 3. 8.
 *      Author: LG CNS
 */

#ifndef SESSION_H_
#define SESSION_H_

#define BOOST_ASIO_ENABLE_HANDLER_TRACKING

#include "Request.h"
#include "Response.h"
#include <log4cplus/loggingmacros.h>
#include <boost/asio.hpp>
#include <memory>
#include <vector>

using namespace boost::asio::ip;

class Session : public std::enable_shared_from_this<Session> {
public:
	Session(boost::asio::io_service& ioService);
	~Session();

	tcp::socket& socket();
	void start();
    void stop();

private:
    // logger
    log4cplus::Logger _logger;

    // socket
	tcp::socket _socket;

	// receive buffer, send buffer
	enum { MAX_LENGTH = 10 };
	std::array<char, MAX_LENGTH> _recvBuf;
	std::vector<boost::asio::const_buffer> _sendBuffer;

	// request, response
	Request  _request;
	Response _response;

	// read from OS
    void _doRead();

	// read from OS
    void _doReadWithoutReset();

    // 오류 처리하고, 정상 수신이면 Parse
    void _readHandler(const boost::system::error_code& ec, size_t recvBytes);

    // 요청 작업 수행
    // TODO class 분리
    void _doCommand(char command);

    // write to OS
    void _doWrite();

    // write 완료 후 다시 read
    void _writeHandler(const boost::system::error_code& ec);

};

#endif /* SESSION_H_ */
