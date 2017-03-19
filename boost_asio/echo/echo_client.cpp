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
#include "MyHeader.h"

using boost::asio::ip::tcp;

const size_t send_buff_length = 3;

int main(int argc, char* argv[]) {

	log4cplus::initialize();
	log4cplus::PropertyConfigurator::doConfigure("../log4cplus.conf");

	try {
//		if (argc != 3) {
//			std::cerr << "Usage: blocking_tcp_echo_client <host> <port>\n";
//			return 1;
//		}

		boost::asio::io_service io_service;
		tcp::socket s(io_service);
		tcp::resolver resolver(io_service);
		boost::asio::connect(s, resolver.resolve( {"localhost", "2333"}));

		MyHeader header;
		std::array<char, BODY_MAX_SIZE> body;
		while (true) {
			header = {};

			std::cout << "Enter message: ";
			//std::array<char, max_length> request;
			std::cin.getline(body.data(), BODY_MAX_SIZE);
			size_t request_length = std::strlen( body.data() );

			// set header
			header.putField( 'E', 'D', request_length);
			std::cout << header << std::endl;

			// write header
			boost::asio::write(s, boost::asio::buffer(header));

			// write body
			boost::asio::write(s, boost::asio::buffer(body, request_length));
//			for ( size_t i=0; i<request_length; i+=send_buff_length ) {
//				size_t send_length =
//						( (i+send_buff_length) > request_length ) ?
//						request_length - i : send_buff_length;
//				boost::asio::write(s, boost::asio::buffer(body.data()+i, send_length));
//				std::this_thread::sleep_for( std::chrono::seconds(1));
//			}

			// reply
			std::vector<char> reply;

			//TODO timeout
			size_t reply_length =  header.size() + request_length ;
			std::cout << "wait for " << reply_length  << "bytes" << std::endl;
			boost::system::error_code ec;
			size_t read_length =
					boost::asio::read(s, boost::asio::buffer(reply, reply_length), ec);
			std::cout << "Reply " << read_length << " : " << ec.message() ;
			std::cout.write(reply.data(), read_length);
			std::cout << "\n";
		}
	} catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}

