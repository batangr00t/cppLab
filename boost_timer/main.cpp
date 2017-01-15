/*
 * main.cpp
 *
 *  Created on: 2016. 7. 9.
 *      Author: juik
 */

#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "printer.h"

std::ostream& log() {
	std::time_t curr_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::cout << std::put_time( std::localtime(&curr_time ), "%F|%T" )
	          << "|" << std::hex << std::this_thread::get_id() << "|";
	return std::cout;
}

void print( const boost::system::error_code& ec ) {
	log() << "Hello, World!" << std::endl;
}

void print2( const boost::system::error_code& ec,
		     boost::asio::deadline_timer* t, int* count ) {
	log() << "Hello, World!" << std::endl;

	if ( *count < 5 ) {
		log() << *count << std::endl;
		++(*count);
		t->expires_at( t->expires_at() + boost::posix_time::seconds(1));
		t->async_wait(boost::bind( print2, boost::asio::placeholders::error, t, count ) );
	}
}

int main() {
	log() << "-- start" << std::endl;

	// sync
	{
		log() << "---- sync" << std::endl;
		boost::asio::io_service io;
		boost::asio::deadline_timer t(io, boost::posix_time::seconds(1));

		t.wait();
		log() << "Hello, World!" << std::endl;
	}

	// async
	{
		log() << "---- async" << std::endl;
		boost::asio::io_service io;
		boost::asio::deadline_timer t(io, boost::posix_time::seconds(1));
		t.async_wait( print );
		io.run();
	}

	// async2
	{
		log() << "---- async2" << std::endl;
		boost::asio::io_service io;
		boost::asio::deadline_timer t(io, boost::posix_time::seconds(1));
		int count = 0;
		auto handler = boost::bind( print2, boost::asio::placeholders::error, &t, &count );
		t.async_wait( handler );
		log() << "-- do something after sync_wait()" << std::endl;
		std::this_thread::sleep_for( std::chrono::seconds(5));
		log() << "-- do something after sleep_for()" << std::endl;
		io.run();
	}

	// async3
	{
		log() << "---- async3" << std::endl;
		boost::asio::io_service io;
		printer p(io);
		io.run();
	}

	log() << "---- end" << std::endl;
	return 0;
}



