#include <QtCore/QCoreApplication>
#include"RegeditUtils.h"
#include<QDebug>
#include<string>
#include<direct.h>
#include<io.h>
#include<thread>
#include<iostream>
using namespace std;
static string processFileName(const string& fileName) {
	string res = " \"";
	for (auto x : fileName) res.push_back(x == '/' ? '\\' : x);
	res += "\" ";
	return res;
}
void copyFile(const string& src, const string& dst)
{
	string command = "copy /Y" + processFileName(src) + processFileName(dst);
	system(command.c_str());
}


vector<string> getSubFiles(const string& path) {
	long long  hFile = 0;
	struct _finddata_t fileinfo;
	string p;
	vector<string> files;
	if ((hFile = _findfirst(p.assign(path).append("/*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if (!(fileinfo.attrib & _A_SUBDIR))
				files.emplace_back(p.assign(path).append("/").append(fileinfo.name));
		} while (_findnext(hFile, &fileinfo) == 0); //寻找下一个，成功返回0，否则-1
		_findclose(hFile);
	}
	return files;
}

vector<string> getSubFolders(const string& path) {
	vector<string> folders;
	long long  hFile = 0;
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("/*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib & _A_SUBDIR)
				&& strcmp(fileinfo.name, ".") != 0
				&& strcmp(fileinfo.name, "..") != 0)
			{
				folders.emplace_back(p.assign(path).append("/").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0); //寻找下一个，成功返回0，否则-1
		_findclose(hFile);
	}
	return folders;
}
#include<future>
void runasync(const std::string& path, int& len)
{
	vector<string> roots = async(getSubFolders, path).get();
	if (roots.empty())
	{
		vector<string> files = async(getSubFiles, path).get();
		len += files.size();
		std::this_thread::sleep_for(std::chrono::microseconds(500));
		return;
	}
	for (const auto& root : roots)
	{
		vector<string> subFiles = async(getSubFiles, root).get();
		if (!subFiles.empty())
		{
			len += subFiles.size();
			std::this_thread::sleep_for(std::chrono::microseconds(500));
		}
		else {
			runasync(root, len);
		}
		std::this_thread::yield();
	}

}

void run(const std::string& path, int& len)
{
	vector<string> files = getSubFiles(path);
	len += files.size();
	files.clear();
	vector<string> roots = getSubFolders(path);
	for (const auto& root : roots)
		run(root, len);
}



void getAllFiles(string path, vector<string>& files)
{

	long long  hFile = 0;
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("/*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getAllFiles(p.assign(path).append("/").append(fileinfo.name), files);
			}
			else
				files.emplace_back(p.assign(path).append("/").append(fileinfo.name));

		} while (_findnext(hFile, &fileinfo) == 0); //寻找下一个，成功返回0，否则-1
		_findclose(hFile);
	}
}
#include<regex>
int main(int argc, char* argv[])
{
	//QCoreApplication a(argc, argv);
	//string path = "E:\\uploaderTestData\\RT_struct";
	//int len = 0;
	//size_t st = clock();
	//run(path, len);
	//std::cout << len << "time:" << clock() - st << endl;
	//st = clock();
	//len = 0;
	//runasync(path, len);
	//std::cout << len << "time:" << clock() - st << endl;
	//vector<string> svec;
	//getAllFiles(path, svec);
	//std::cout << svec.size() << endl;
	//return a.exec();
	using namespace std;
	const string matchingMaskKey = "_lable";
	regex pattern1(".+" + matchingMaskKey + "(\\d*)\\.(mha|mhd|nii\\.gz|nii|hdr|image3d)$");
	string path = "asdadas/aaaasdasd_lable22.mha";
	//auto x = regex_match(path, pattern1);
	//std::cout << x << endl;


	//int y = 5, x = 10, z = 15;
	//string str1, str2;
	//int start = clock();
	//for (int i = 0; i < 1e6; i++)
	//	str1 = to_string(y) + "-" + to_string(x) + "," + to_string(z) + ",";
	//std::cout << clock() - start;

	//char str[20];
	//start = clock();
	//for (int i = 0; i < 1e7; i++) {
	//	sprintf_s(str, 20, "%d-%d,%d,", y, x, z);
	//	str2.assign(str);
	//}
	//std::cout << clock() - start;
	//assert(str1 == str2);
	char cc[12];
	for (int i = 0; i < 12; i++) cc[i] = 2 * i;
	for (int i = 0; i < 12; i++) assert(*(cc +1+ i) == cc[i]);


	getchar();

}
