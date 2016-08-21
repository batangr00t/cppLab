#include <iostream>
#include <thread>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;

class Generator {
public:
	Generator(): _ios(), _interval(1000), _timer(_ios) {
		;
	}
	~Generator() {

	}

	void start() {
		cout << __PRETTY_FUNCTION__ << endl;
		//t.async_wait(boost::bind(print, boost::asio::placeholders::error, &t, &count));
//		_timer.expires_at(boost::posix_time::seconds(1));
		_timer.expires_from_now(boost::posix_time::milliseconds(_interval));
		_timer.async_wait(boost::bind(&Generator::handler, this));
		_t = thread( boost::bind( &boost::asio::io_service::run, &_ios ) );
		_t.detach();

	}

	void stop() {
		cout << __PRETTY_FUNCTION__ << endl;
		_ios.stop();
	}

	void join() {
		//if ( _t.joinable() ) _t.join();
	}

	void addJob( unsigned int interval, void (*callbackFunc)() );

	void handler() {
		std::cout << "Hello" << std::endl;
		_timer.expires_at(_timer.expires_at() + boost::posix_time::seconds(1));
		_timer.async_wait(boost::bind(&Generator::handler, this));
	}

private:
	boost::asio::io_service _ios;
	unsigned int _interval;
	boost::asio::deadline_timer _timer;
	thread _t;


};

void print(const boost::system::error_code& e, boost::asio::deadline_timer* t, int* count) {
	if (*count < 5) {
		std::cout << *count << std::endl;
		++(*count);

		t->expires_at(t->expires_at() + boost::posix_time::seconds(1));
		t->async_wait(
				boost::bind(print, boost::asio::placeholders::error, t, count));
	}
	std::cout << e.message() << std::endl;

}

int main() {

	try {
		Generator g;

		g.start();

		std::this_thread::sleep_for( std::chrono::seconds(1) );

		int stop;
		cin >> stop;
		g.stop();
	} catch ( const exception& e ) {
		cout << e.what() << endl;
	}
	return 0;
}
