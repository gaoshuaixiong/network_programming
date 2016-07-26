#include <sys/stat.h>
#include <sys/ipc.h>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	struct stat stat1;
	if(argc!=2)
	{
		cout<<"usage:ftok <pathname>"<<endl;
	}
	stat(argv[1],&stat1);
	printf("st_dev: %lx, st_ino: %lx, key: %x\n",(u_long)stat1.st_dev,(u_long)stat1.st_ino,ftok(argv[1],0x57));
	return 0;
}