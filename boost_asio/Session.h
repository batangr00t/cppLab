/*
 * Session.h
 *
 *  Created on: 2017. 3. 8.
 *      Author: LG CNS
 */

#ifndef SESSION_H_
#define SESSION_H_

#include <iostream>
#include <boost/asio.hpp>
#include <memory>
#include <set>

using namespace boost::asio::ip;

class Session : public std::enable_shared_from_this<Session> {
public:
	Session(tcp::socket socket);
	~Session();

	// read
	void start();

	// stop
    void stop();

private:
	tcp::socket _socket;
	enum { MAX_LENGTH = 1024 };
	char _data[MAX_LENGTH];
	//SessionList& _sessions;
	int count = 0;

	// read from OS
    void _doRead();
    // 읽은 데이터 parsing 후 doWrite
    void _readHandler(const boost::system::error_code& ec, size_t recvBytes);
    // write to OS
    void _doWrite(std::size_t length);
    // write 완료 후 다시 read
    void _writeHandler(const boost::system::error_code& ec);

};

#endif /* SESSION_H_ */
