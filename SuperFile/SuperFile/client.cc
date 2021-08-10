#include "SuperFile.h"
#include <windows.h>

int test_trans_file() {
	int ans = 0;
	SuperFile::ptr sf = SuperFile::ptr(new SuperFile);
	if( -1 == sf->searchServer("127.0.0.1", 6666)) {
		std::cout << "cant search server!" << std::endl;
		return -1;
	}
	
	std::string recv_file = "";
	while(1) {
		recv_file = "...";
		sf->recvFile();
		std::cout << "recvFile: " << recv_file << std::endl;
	
		for(int i = 0; i < 100000; i++) {
			for(int j = 0; j < 5; j++) {
				;
			}
		}
	}
	return ans;
}

int main() {
	test_trans_file();
}