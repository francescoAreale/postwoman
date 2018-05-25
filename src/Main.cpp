#include <iostream>
#include <string.h>
#include "PostWoman.h"

using namespace std;

int main(int argc, char *argv[]) {

	const std::string configFileName(argv[2]);

	if(argc!=3 || strcmp(argv[1],"-c")!=0)
	{
		std::cout<<"Usage: "<<argv[0]<<" -c <log file>"<<std::endl;
		return -1;
	}
	PostWoman *pW = new PostWoman(argv[2]);
	pW->runPostWoman();
	delete pW;

	return 0;
}
