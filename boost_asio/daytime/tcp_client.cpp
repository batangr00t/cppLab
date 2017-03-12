/*
 * main.cpp
 *
 *  Created on: 2017. 3. 11.
 *      Author: cho
 */

#include <iostream>
#include <boost/asio.hpp>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include <vector>

using boost::asio::ip::tcp;

log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("main"));

int main(int argc, char* argv[]) {
	log4cplus::initialize();
	log4cplus::PropertyConfigurator::doConfigure("../log4cplus.conf");

	LOG4CPLUS_INFO( logger, "-------- start ---------------");

	try {
		boost::asio::io_service ioService;
		tcp::resolver resolver(ioService);
		tcp::resolver::query query( "", "daytime");
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
		tcp::socket socket(ioService);

		boost::asio::connect( socket, endpoint_iterator );

		for(;;) {
			std::vector<char> buf;
			boost::system::error_code ec;

			size_t len = socket.read_some( boost::asio::buffer(buf), ec);
			if ( ec == boost::asio::error::eof ) {
				break; // connection closed cleanly by peer
			} else if ( ec ) {
				LOG4CPLUS_ERROR( logger, "read_some - " << ec.message() );
				break;
			}

			std::cout.write( buf.data(), len);
		}
	} catch ( const std::exception& e ) {
		LOG4CPLUS_ERROR( logger, "exception - " << e.what() );
	}

	LOG4CPLUS_INFO( logger, "-------- end   ---------------");
}


