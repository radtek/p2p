#ifndef H_CONNECTION_MANAGER
#define H_CONNECTION_MANAGER

//custom
#include "connection.hpp"

//include
#include <boost/thread.hpp>
#include <boost/utility.hpp>
#include <network/network.hpp>

//standard
#include <map>

class connection_manager : private boost::noncopyable
{
public:
	connection_manager(network::proactor & Proactor_in);

	/*
	connect_call_back:
		Proactor does call back when there is a new connection.
	disconnect_call_back:
		Proactor does call back when new connection failed, or when existing
		connection closed.
	*/
	void connect_call_back(network::connection_info & CI);
	void disconnect_call_back(network::connection_info & CI);

private:
	network::proactor & Proactor;

	/*
	IP set used to insure connections are unique. Connection maps the
	connection_ID to the state associated with the connection. Mutex locks all
	modification of IP and Connection containers.
	*/
	boost::mutex Mutex;
	std::set<std::string> IP;
	std::map<int, boost::shared_ptr<connection> > Connection;
};
#endif
