#ifndef H_DOWNLOAD_STATUS
#define H_DOWNLOAD_STATUS

//standard
#include <string>
#include <vector>

class download_status
{
public:
	std::string hash;          //root hash of hash tree
	std::string name;          //name of the file
	boost::uint64_t size;      //size of the file (bytes)
	unsigned percent_complete; //0-100
	unsigned total_speed;      //total download speed (bytes/second)

	//std::pair<IP, speed (bps)>
	std::vector<std::pair<std::string, unsigned> > servers;
};
#endif
