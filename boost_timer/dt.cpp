/*
 * dt.cpp
 * example program using deadline_timer
 * https://www.youtube.com/watch?v=rwOv_tw2eA4
 *  Created on: 2017. 1. 15.
 *      Author: cho
 */

#include <boost/asio.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/bind.hpp>
#include <thread>
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

void timer_expired( const std::string& id, const boost::system::error_code& e ) {
	log() << " " << id << " enter." << std::endl;
	log() << e.message() << std::endl;
	//std::this_thread::sleep_for( std::chrono::seconds(3));
	log() << " " << id << " leave." << std::endl;

}

int main() {
	log() << "-- start" << std::endl;

	boost::asio::io_service io;
	boost::asio::io_service::strand strand(io);

	boost::asio::deadline_timer timer1( io, boost::posix_time::seconds(1) );
	boost::asio::deadline_timer timer2( io, boost::posix_time::seconds(1) );

	timer1.async_wait( strand.wrap( boost::bind( timer_expired, "timer1", boost::asio::placeholders::error)));
	timer2.async_wait( strand.wrap( boost::bind( timer_expired, "timer2", boost::asio::placeholders::error)));

	std::thread butler1( [&]() { io.run(); } );
	std::thread butler2( [&]() { io.run(); } );

	butler1.join();
	butler2.join();

	log() << "-- end" << std::endl;
}





