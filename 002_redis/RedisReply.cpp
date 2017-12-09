#include "RedisReply.h"

RedisReply::RedisReply(redisReply* reply):
	_logger( log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("RedisReply")) ),
	_reply(reply) {
	LOG4CPLUS_TRACE(_logger, __PRETTY_FUNCTION__ << "[" << _reply << "]");
}

RedisReply::RedisReply(void* reply) : RedisReply((redisReply*) reply) {
	LOG4CPLUS_TRACE(_logger, __PRETTY_FUNCTION__ << "[" << _reply << "]");
}

RedisReply::~RedisReply() {
	LOG4CPLUS_TRACE(_logger, __PRETTY_FUNCTION__ << "[" << _reply << "]");
//	if ( _reply != nullptr ) {
//		freeReplyObject(_reply);
//		_reply = nullptr;
//	}
}

long long RedisReply::getInteger() {
	LOG4CPLUS_TRACE(_logger, __PRETTY_FUNCTION__);
	return _reply->integer;
	if ( _reply == nullptr ) {
		LOG4CPLUS_ERROR(_logger, "_reply is nullptr" );
		return 0;
	} else {
		return _reply->integer;
	}
}

BinString RedisReply::getBinString() const {
	LOG4CPLUS_TRACE(_logger, __PRETTY_FUNCTION__);
	if ( _reply == nullptr ) {
		LOG4CPLUS_ERROR(_logger, "_reply is nullptr" );
		return BinString();
	} else {
		return BinString( _reply->str, _reply->len );
	}
}

vector<RedisReply> RedisReply::getArray() const {
	LOG4CPLUS_TRACE(_logger, __PRETTY_FUNCTION__);
	if ( _reply == nullptr ) {
		LOG4CPLUS_ERROR(_logger, "_reply is nullptr" );
		return vector<RedisReply>();
	} else {
		vector<RedisReply> array;
		array.reserve(_reply->elements);
		for ( size_t i=0; i<_reply->elements; i++ ) {
			LOG4CPLUS_TRACE(_logger, "push_back[" << i << "]");
			array.push_back( RedisReply(_reply->element[i]) );
		}
		return array;
	}
}

const string RedisReply::getTypeName( int t ) {
	switch ( t ) {
		case REDIS_REPLY_STRING : return "STRING";
		case REDIS_REPLY_ARRAY 	: return "ARRAY";
		case REDIS_REPLY_INTEGER: return "INTEGER";
		case REDIS_REPLY_NIL 	: return "NIL";
		case REDIS_REPLY_STATUS : return "STATUS";
		case REDIS_REPLY_ERROR 	: return "ERROR";
		default 				: return "UNKNOWN";
	}
}

ostream& operator<< ( ostream& os, const RedisReply &reply ) {
	redisReply * pr = reply._reply;
	if ( pr == nullptr ) {
		os << "_reply is nullptr";
	} else {
		os << "RR["
		<< pr << "]{"
		<< "type:" << pr->type << "(" << RedisReply::getTypeName(pr->type) << "),"
		<< "integer:" << pr->integer << ","
		<< "{len:" << pr->len << ","
		<< "str:\"" << string(pr->str, pr->len ) << "\"}";
		if ( pr->type ==  REDIS_REPLY_ARRAY ) {
			os <<"{#elements:" << pr->elements << ",";
			for ( size_t i=0; i<pr->elements; i++) {
				os << RedisReply( pr->element[i] );
			}
			os << "}";
		}
		os << "}";
	}

	return os;
}


