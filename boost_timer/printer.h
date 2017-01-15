/*
 * printer.h
 *
 *  Created on: 2017. 1. 15.
 *      Author: cho
 */

#ifndef BOOST_TIMER_PRINTER_H_
#define BOOST_TIMER_PRINTER_H_

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#define BOOST_ASIO_ENABLE_HANDLER_TRACKING

class printer {
public:
	printer( boost::asio::io_service& io);
	virtual ~printer();
	void print(const boost::system::error_code& ec);

private:
	std::ostream& log();
	boost::asio::deadline_timer timer_;
	int count_;
};

#endif /* BOOST_TIMER_PRINTER_H_ */
