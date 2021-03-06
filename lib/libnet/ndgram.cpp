#include <net/ndgram.hpp>

net::ndgram::ndgram()
{

}

net::ndgram::ndgram(const endpoint & ep)
{
	open(ep);
}

void net::ndgram::open(const endpoint & ep)
{
	close();
	if((socket_FD = ::socket(ep.ai.ai_addr->sa_family, SOCK_DGRAM, IPPROTO_UDP)) == -1){
		LOG << strerror(errno);
		close();
	}
	if(bind(socket_FD, ep.ai.ai_addr, ep.ai.ai_addrlen) == -1){
		LOG << strerror(errno);
		close();
		return;
	}
}

int net::ndgram::recv(net::buffer & buf, boost::optional<endpoint> & ep)
{
	ep.reset();
	addrinfo ai;
	sockaddr_storage sas;
	ai.ai_addr = reinterpret_cast<sockaddr *>(&sas);
	ai.ai_addrlen = sizeof(sockaddr_storage);
	buf.tail_reserve(MTU);
	int n_bytes = recvfrom(socket_FD, reinterpret_cast<char *>(buf.tail_start()),
		buf.tail_size(), 0, ai.ai_addr, reinterpret_cast<socklen_t *>(&ai.ai_addrlen));
	if(n_bytes == -1 || n_bytes == 0){
		LOG << strerror(errno);
		close();
		buf.tail_reserve(0);
	}else{
		ep = endpoint(&ai);
		buf.tail_resize(n_bytes);
	}
	return n_bytes;
}

int net::ndgram::send(net::buffer & buf, const endpoint & ep)
{
	int n_bytes = sendto(socket_FD, reinterpret_cast<char *>(buf.data()),
		buf.size(), 0, ep.ai.ai_addr, ep.ai.ai_addrlen);
	if(n_bytes == -1 || n_bytes == 0){
		LOG << strerror(errno);
		close();
	}else{
		buf.erase(0, n_bytes);
	}
	return n_bytes;
}
