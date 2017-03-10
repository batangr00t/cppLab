/*
 * main.cpp
 *
 *  Created on: 2017. 3. 7.
 *      Author: LG CNS
 */

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <iostream>
//#include <memory>
//#include <utility>
//#include <vector>
#include <thread>

class printer
{
public:
	printer(boost::asio::io_service& io)
	: strand_(io),
	  timer1_(io, boost::posix_time::seconds(1)),
	  timer2_(io, boost::posix_time::seconds(1)),
	  count_(0) {
		std::cout << __PRETTY_FUNCTION__ << std::endl;
		timer1_.async_wait(strand_.wrap( boost::bind(&printer::print1, this)));
		timer2_.async_wait(strand_.wrap( boost::bind(&printer::print2, this)));
	}

	~printer() {
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}

	void print1() {
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}

	void print2() {
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}

private:
	boost::asio::io_service::strand strand_;
	boost::asio::deadline_timer timer1_;
	boost::asio::deadline_timer timer2_;
	unsigned int count_;
};
