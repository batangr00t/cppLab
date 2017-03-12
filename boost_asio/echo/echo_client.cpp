//
// blocking_tcp_echo_client.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2017 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>
#include <log4cplus/configurator.h>
#include <thread>
#include <chrono>

using boost::asio::ip::tcp;

const size_t max_length = 1024;
const size_t send_buff_length = 3;

int main(int argc, char* argv[]) {

	log4cplus::initialize();
	log4cplus::PropertyConfigurator::doConfigure("../log4cplus.conf");

	try {
		if (argc != 3) {
			std::cerr << "Usage: blocking_tcp_echo_client <host> <port>\n";
			return 1;
		}

		boost::asio::io_service io_service;

		tcp::socket s(io_service);
		tcp::resolver resolver(io_service);
		boost::asio::connect(s, resolver.resolve( { argv[1], argv[2] }));

		while (true) {
			std::cout << "Enter message: ";
			std::array<char, max_length> request;
			std::cin.getline(request.data(), max_length-1);
			size_t request_length = std::strlen( request.data() );
			request[request_length] = 'E';
			request_length++;
			std::cout << "size : " << request_length << std::endl;

			// write
//			boost::asio::write(s, boost::asio::buffer(request, request_length));
			for ( size_t i=0; i<request_length; i+=send_buff_length ) {
				size_t send_length =
						( (i+send_buff_length) > request_length ) ?
						request_length - i : send_buff_length;
				boost::asio::write(s, boost::asio::buffer(request.data()+i, send_length));
				std::this_thread::sleep_for( std::chrono::seconds(1));
			}

			// reply
			char reply[max_length];

			//TODO timeout
			std::cout << "wait for " << request_length << "bytes" << std::endl;
			size_t reply_length = boost::asio::read(s,
					boost::asio::buffer(reply, request_length));
			std::cout << "Reply is: ";
			std::cout.write(reply, reply_length);
			std::cout << "\n";
		}
	} catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}

