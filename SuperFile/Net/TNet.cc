#include <iostream>
#include <memory>
class TNet {

public:
	typedef std::shared_ptr<TNet> ptr;
	typedef int SockDesc_t;
	typedef int DataSize_t;
	TNet();
	~TNet();

	SockDesc_t Socket();

	static int Bind(const char* ip_addr, short port);

	static int Listen(SockDesc_t sock, int num);

	static SockDesc_t Accept(SockDesc_t sock);

	static int Connect(SockDesc_t sock, const char* ip, short port);

	static DataSize_t RecvData(SockDesc_t sock, void* buffer, int size);

	static DataSize_t SendData(SockDesc_t sock, void buiffer, int size);

};


TNet::TNet() {}



TNet::~TNet() {}



int TNet::Socket() {


}

int TNet::Listen() {}




