#include <iostream>
#include <thread>
#include "MessageQueue.h"
#include "Log.h"
#include "Message.h"

using namespace std;

void producer(MessageQueue<Message>& mq, int count) {
	Log::log( __PRETTY_FUNCTION__ );
	while( --count > 0 ) {
		mq.put( Message{count,"hi"} );
	}
}

void consumer(MessageQueue<Message>& mq, int count) {
	Log::log( __PRETTY_FUNCTION__ );
	while( --count > 0 ) {
		Message& message = mq.get();
		Log::log( to_string(message.id) );
	}
}

int main(int argc, char* argv[]) {
	cout << "START ------------------ " << endl;

	unsigned int max_size = 1;
	int count = 5;

	if ( argc > 1 ) {
		max_size = stoi( argv[1]);
	}

	if ( argc > 2 ) {
		count = stoi( argv[2]);
	}

	MessageQueue<Message> mq{max_size};

	thread th1{producer, ref(mq), count};
	thread th2{consumer, ref(mq), count};

	th1.join();
	th2.join();

	cout << "END   ------------------ " << endl;

	return 0;
}



