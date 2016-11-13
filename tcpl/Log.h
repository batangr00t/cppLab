/*
 * Log.h
 *
 *  Created on: 2016. 11. 13.
 *      Author: cho
 */

#ifndef TCPL_LOG_H_
#define TCPL_LOG_H_

#include <string>
#include <mutex>

class Log {
public:
	static void log(const std::string& msg);
private:
	static std::mutex _m;
};

#endif /* TCPL_LOG_H_ */
