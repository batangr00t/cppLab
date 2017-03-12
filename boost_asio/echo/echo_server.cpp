/*
 * echo_server.cpp
 *
 *  Created on: 2017. 3. 8.
 *      Author: LG CNS
 */

#include "Session.h"
#include "Server.h"
#include <iostream>
#include <log4cplus/configurator.h>

int main(int argc, char* argv[]) {
	std::cout << "------ Start ----------" << std::endl;

	log4cplus::initialize() ;
	log4cplus::PropertyConfigurator::doConfigure("../log4cplus.conf");

	unsigned short port;
	if ( argc > 1 ) {
		port = atoi(argv[1]);
	} else {
		port = 2333;
	}


	std::cout << "listen port = " << port << std::endl;

	try {
		boost::asio::io_service io;
		Server server( io, port );

		server.start();
		io.run();
	} catch( const std::exception& e ) {
		std::cerr << "Exception : " << e.what() << std::endl;
	}

	std::cout << "------ End ----------" << std::endl;
}

