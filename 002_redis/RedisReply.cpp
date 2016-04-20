#include "RedisReply.h"

log4cplus::Logger RedisReply::logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("RedisReply"));

RedisReply::RedisReply(redisReply* reply): _reply(reply) {
	LOG4CPLUS_TRACE(logger, "constructor redisReply*");
}

RedisReply::RedisReply(void* reply) {
	LOG4CPLUS_TRACE(logger, "constructor void*");
	_reply = (redisReply*) reply;
}

RedisReply::~RedisReply() {
	LOG4CPLUS_TRACE(logger, "destructor");
	this->free();
}

string RedisReply::getValue() {
	LOG4CPLUS_TRACE(logger, "getValue");
	return string(_reply->str, _reply->len);
}

void RedisReply::free() {
	LOG4CPLUS_TRACE(logger, "free");
	freeReplyObject(_reply);
	_reply = nullptr;
}


ostream& operator<< ( ostream& os, const RedisReply &reply ) {
	redisReply * pr = reply._reply;
	if ( pr == nullptr ) {
		os << "_reply is nullptr ";
	} else {
		os << "_reply[" 
		<< pr << "]{"
		<< "type:" << pr->type << ", "
		<< "integer:" << pr->integer << ", "
		<< "len:" << pr->len << ", "
		//<< "str:" << string(pr->str, (pr->len > 20) ? 20 : pr->len ) << ", "
		<< "str:\"" << string(pr->str, pr->len ) << "\", "
		<< "#elements:" << pr->elements << ", "
		<< "}";
	}

	return os;
}
