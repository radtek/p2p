//custom
#include "client_server_bridge.h"
#include "global.h"
#include "server.h"

int main(int argc, char ** argv)
{
	server Server;

	/*
	Normally this is done by the client after resuming downloads. Because the
	client is not started this is done here.
	*/
	client_server_bridge::unblock_server_index();

	while(true){
		portable_sleep::ms(1000);
	}
	return 0;
}
