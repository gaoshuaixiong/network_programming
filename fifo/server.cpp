#include "fifo.h"

using namespace std;

void server(int reader,int writer)
{
	int fd;
	ssize_t n;
	char buff[MAXLINE+1];
	if((n=read(reader,buff,MAXLINE))==0)
	cerr<<"end of file while reading pathname"<<endl;
	buff[n]=0;
	if((fd=open(buff,O_RDONLY))<0)
	{
		string s = "can't open "+string(buff)+"\n";
		n=strlen(buff);
		write(writer,s.c_str(),s.size());
	}	
	else
	{
		while((n=read(fd,buff,MAXLINE))>0)
			write(writer,buff,n);
	}
	close(fd);
}

int main(int argc, char const *argv[])
{
	int readfd,writefd;

	if((mkfifo(FIFO1,FILE_MODE)<0)&&(errno!=EEXIST))
		cerr<<"server cant create fifo1"<<endl;
	if((mkfifo(FIFO2,FILE_MODE)<0)&&(errno!=EEXIST))
	{
		unlink(FIFO1);
		cerr<<"server cant create fifo2"<<endl;
	}
	readfd = open(FIFO1,O_RDONLY,0);
	writefd = open(FIFO2,O_WRONLY,0);

	server(readfd,writefd);

	exit(0);
	return 0;
}