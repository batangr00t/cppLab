/*
 * async_op.cpp
 *
 *  Created on: 2017. 3. 18.
 *      Author: cho
 */

#include <boost/asio.hpp>
#include <iostream>

#define BOOST_ASIO_ENABLE_HANDLER_TRACKING

void connect_handler( const boost::system::error_code& ec ) {
	std::cout << ec.message() << std::endl;

}

int main() {
	// 1. io_service
	// The io_service represents your program's link to
	// the operating system's I/O services.
	//
	// Proactor : Calls the asynchronous event demultiplexer to dequeue events,
	//            and dispatches the completion handler
	//            (i.e. invokes the function object) associated with the event.
	//            This abstraction is represented by the io_service class.
	boost::asio::io_service io_service;

	// 2. socket
	// To perform I/O operations your program will need an I/O object
	// such as a TCP socket:
	boost::asio::ip::tcp::socket socekt(io_service);

	// 3. endpoint
	boost::asio::ip::tcp::resolver resolver(io_service);
	boost::asio::ip::tcp::resolver::query q("localhost", "2333");
	boost::asio::ip::tcp::resolver::iterator it = resolver.resolve(q );

	//socket.async_connect( boost::asio::ip::tcp::v4(), connect_handler);

	// A call to io_service::run() blocks
	// while there are unfinished asynchronous operations,
	// so you would typically call it as soon as you have started
	// your first asynchronous operation.

	// io_service::run(), the io_service dequeues the result of the operation,
	// translates it into an error_code, and then passes it to
	// your completion handler.
	io_service.run();
}


