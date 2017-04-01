/*
 * sync_op.cpp
 *
 *  Created on: 2017. 3. 18.
 *      Author: cho
 */

#include <boost/asio.hpp>

int main() {
	// The io_service represents your program's link to
	// the operating system's I/O services.
	boost::asio::io_service io_service;

	// To perform I/O operations your program will need an I/O object
	// such as a TCP socket:
	boost::asio::ip::tcp::socket socekt(io_service);

	// then the error_code variable ec would be set to the result of the operation,
	// and no exception would be thrown.
	boost::system::error_code ec;
	//socket.connect( server_endpoint, ec );


}


