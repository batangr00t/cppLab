/*
 * printer.cpp
 *
 *  Created on: 2017. 1. 15.
 *      Author: cho
 */

#include <chrono>
#include <thread>
#include "printer.h"

printer::printer( boost::asio::io_service& io)
	: timer_ ( io, boost::posix_time::seconds(1) ),
	  count_(0) {
	log() << __PRETTY_FUNCTION__ << std::endl;
	timer_.async_wait(boost::bind( &printer::print, this, boost::asio::placeholders::error));
}

printer::~printer() {
	log() << __PRETTY_FUNCTION__ << ", Final count is " << count_ << std::endl;
}

void printer::print(const boost::system::error_code& ec) {
	if ( count_ < 5 ) {
		log() << __PRETTY_FUNCTION__ << ", " << count_ << std::endl;;
		++count_;

		timer_.expires_at( timer_.expires_at() + boost::posix_time::seconds(1));
		timer_.async_wait( boost::bind( &printer::print, this, boost::asio::placeholders::error));
	}
}

std::ostream& printer::log() {
	std::time_t curr_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::cout << std::put_time( std::localtime(&curr_time ), "%F|%T" )
	          << "|" << std::hex << std::this_thread::get_id() << "|";
	return std::cout;
}
