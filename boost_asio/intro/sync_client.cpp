#include <boost/asio.hpp>
#include <iostream>

#define BOOST_ASIO_ENABLE_HANDLER_TRACKING

using namespace boost::asio;

int main() {
	// The io_service represents your program's link to
	// the operating system's I/O services.
	io_service io_service;

	// To perform I/O operations your program will need an I/O object
	// such as a TCP socket:
	ip::tcp::socket sock(io_service);

	ip::tcp::endpoint ep ( ip::address::from_string("127.0.0.1"), 2001);

	// then the error_code variable ec would be set to the result of the operation,
	// and no exception would be thrown.
	boost::system::error_code ec;
	try {
		sock.connect( ep, ec );
	} catch ( const std::exception& e ) {
		std::cout << e.what() << std::endl;
	}
}


