
#include "TFile.h"
#include "platforms/win_file/WinFile.h"
#include <direct.h>
#include <memory>
#include <string>
#include <vector>
#include <stdio.h>
#define DIR_SEPARATOR '\\'
class TWinFile : public TFile {
public:
	typedef WinFile::FileData_t FileData_t;
	typedef std::shared_ptr<TWinFile> ptr;
	
	TWinFile(const std::string& filePath) : TFile(filePath) {
		m_fileData = getFileData();
	}
	~TWinFile() {

	}

	int isExit() override {
		return !!m_fileData.size;
	}

	int isDir() override {
		return _A_SUBDIR == m_fileData.attrib;
	}

	int createFile(const char* path) override {
		FILE* pFile = fopen(path, "rb+");
		fclose(pFile);

		return pFile != NULL;
	}

	int createDir(const char* path) override {
		std::string str_path = path;
		formateDirName(str_path);          // end must '\'
		std::vector<std::string> v_dirs;
		
		int beg = 3, len = 0;
		std::string cur_dir_name;
		if(str_path.size() < beg + 1) {
			std::cout << "dir_format err!" << std::endl;
		}
		for(size_t i = beg + 1; i < str_path.size(); i++) {
			if(str_path[i] == DIR_SEPARATOR) {
				len = i - beg;
				cur_dir_name = str_path.substr(beg, len);
				beg = i + 1;

				std::cout << "cur_dir_name = " << cur_dir_name << std::endl;
				v_dirs.push_back(cur_dir_name);
			}
		}
		int mkdirRes = 0;
		std::string dirs = str_path.substr(3);
		while( -1 != mkdirRes) {
			dirs += v_dirs.front();
			v_dirs.pop_front();
			
			mkdirRes = 0;'
			if(-1 == _access(dirs.c_str())) {
				mkdirRes = _mkdir(dirs.c_str());
			}
			else {
				std::cout << "dir: " << dirs.c_str();
			}
		}
	}

	std::vector<std::string> getNamesUnderDir() override {
		std::vector<std::string> subNames;
		if(isDir()) {
			_finddata_t file;
			int k;
			long HANDLE;
			formateDirName(m_path);
			m_path += "*.*";
			std::cout << "getNamesUndjerDir: dirCmd = " << m_path; 
			
			k = HANDLE = _findfirst(m_path.c_str(), &file);	
			while (k != -1) {
				subNames.push_back(std::string(file.name));
				k = _findnext(HANDLE, &file);
			}
			_findclose(HANDLE);
		}
		
	}
	
	//end must '/'
	int formateDirName(std::string& dirPath) override {
		if(dirPath.size() && dirPath[dirPath.size() - 1] != DIR_SEPARATOR) {
			dirPath += DIR_SEPARATOR;
			return 1;
		}
		return 0;
	}

protected:
	FileData_t getFileData() {
		return WinFile::GetFileData(m_path.c_str());
	}
private:
	FileData_t m_fileData;
};
