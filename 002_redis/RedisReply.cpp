#include "RedisReply.h"

log4cplus::Logger RedisReply::logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("RedisReply"));
//string RedisReply::typeNames[] = { "STRING", "ARRAY", "INTEGER", "NIL", "STATUS", "ERROR", "unknown" };
string RedisReply::typeNames[] = {"unknown", "STRING", "ARRAY", "INTEGER", "NIL", "STATUS", "ERROR"};

RedisReply::RedisReply(redisReply* reply): _reply(reply) {
	LOG4CPLUS_TRACE(logger, __PRETTY_FUNCTION__);
}

RedisReply::RedisReply(void* reply) {
	LOG4CPLUS_TRACE(logger, __PRETTY_FUNCTION__);
	_reply = (redisReply*) reply;
}

RedisReply::~RedisReply() {
	LOG4CPLUS_TRACE(logger, __PRETTY_FUNCTION__);
	freeReplyObject(_reply);
	_reply = nullptr;
}

long long RedisReply::getInteger() {
	LOG4CPLUS_TRACE(logger, __PRETTY_FUNCTION__);
	return _reply->integer;
}

BinString RedisReply::getBinString() {
	LOG4CPLUS_TRACE(logger, __PRETTY_FUNCTION__);
	BinString bs( _reply->len, _reply->str );
	return bs;
}

vector<BinString> RedisReply::getArray() {
	LOG4CPLUS_TRACE(logger, __PRETTY_FUNCTION__);
	vector<BinString> array;
	array.reserve(_reply->elements);
	for ( size_t i=0; i<_reply->elements; i++ ) {
		LOG4CPLUS_TRACE(logger, "push_back[" << i << "]");
		array.push_back( BinString(_reply->element[i]->len, _reply->element[i]->str ) );
	}
	return array;
}

const string& RedisReply::getTypeName( int t ) {
	switch ( t ) {
		case REDIS_REPLY_STRING : return typeNames[REDIS_REPLY_STRING];
		case REDIS_REPLY_ARRAY 	: return typeNames[REDIS_REPLY_ARRAY];
		case REDIS_REPLY_INTEGER: return typeNames[REDIS_REPLY_INTEGER];
		case REDIS_REPLY_NIL 	: return typeNames[REDIS_REPLY_NIL];
		case REDIS_REPLY_STATUS : return typeNames[REDIS_REPLY_STATUS];
		case REDIS_REPLY_ERROR 	: return typeNames[REDIS_REPLY_ERROR];
		default 				: return typeNames[0];
	}
}

ostream& operator<< ( ostream& os, const RedisReply &reply ) {
	redisReply * pr = reply._reply;
	if ( pr == nullptr ) {
		os << "_reply is nullptr ";
	} else {
		os << "RedisReply["
		<< pr << "]{"
		<< "type:" << pr->type << "(" << RedisReply::getTypeName(pr->type) << "), "
		<< "integer:" << pr->integer << ", "
		<< "{len:" << pr->len << ", "
		//<< "str:" << string(pr->str, (pr->len > 20) ? 20 : pr->len ) << ", "
		<< "str:\"" << string(pr->str, pr->len ) << "\"}, "
		<< "{#elements:" << pr->elements << ", {";
		for ( size_t i=0; i<pr->elements; i++) {
			os << "\"" << pr->element[i]->str << "\", ";
		}
		os << "}}}";
	}

	return os;
}


