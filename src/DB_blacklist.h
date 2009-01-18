#ifndef H_DB_BLACKLIST
#define H_DB_BLACKLIST

//boost
#include <boost/thread/mutex.hpp>

//custom
#include "atomic_int.h"
#include "global.h"
#include "sqlite3_wrapper.h"

//std
#include <iostream>
#include <sstream>
#include <sstream>
#include <string>

class DB_blacklist
{
public:
	DB_blacklist();

	/*
	add            - add IP to blacklist
	is_blacklisted - returns true if IP on blacklist
	modified       - returns true if IP added to blacklist since last check
	                 precondition: last_state_seen should be initialized to zero
	*/
	void add(const std::string & IP);
	bool is_blacklisted(const std::string & IP);
	bool modified(int & last_state_seen);

private:
	sqlite3_wrapper::database DB;
	atomic_int<int> blacklist_state;
};
#endif
