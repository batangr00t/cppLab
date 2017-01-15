/*
 * st.cpp
 * example program using steady_timer
 * https://theboostcpplibraries.com/boost.asio-io-services-and-io-objects
 *  Created on: 2017. 1. 15.
 *      Author: cho
 */

#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>
#include <chrono>
#include <iostream>
#include <thread>
#include <iomanip>

std::ostream& log() {
	std::time_t curr_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::cout << std::put_time( std::localtime(&curr_time ), "%F|%T" )
	          << "|" << std::hex << std::this_thread::get_id() << std::dec << "|";
	return std::cout;
}

int main() {
	log() << "-- start" << std::endl;

	boost::asio::io_service io;

	boost::asio::steady_timer timer1{io, std::chrono::seconds{4}};
	auto handler1 = [](const boost::system::error_code& ec) {
		log() << " 4 seconds" << std::endl;
		for( int i=0; i<100; ++i) {
			log() << i << std::endl;
			std::this_thread::sleep_for( std::chrono::milliseconds(100));
		}
		log() << "end" << std::endl;
	};
	timer1.async_wait( handler1 );

	boost::asio::steady_timer timer2{io, std::chrono::seconds{3}};
	auto handler2 = [](const boost::system::error_code& ec) {
		log() << " 3 seconds" << std::endl;
		for( int i=100; i<200; ++i) {
			log() << i << std::endl;
			std::this_thread::sleep_for( std::chrono::milliseconds(100));
		}
		log() << "end" << std::endl;
	};
	timer2.async_wait( handler2 );

	std::thread thread1{[&io](){ io.run(); }};
	std::thread thread2{[&io](){ io.run(); }};

	thread1.join();
	thread2.join();

	log() << "-- end" << std::endl;
}





