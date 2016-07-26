#include "fifo.h"
using namespace std;

void client(int reader,int writer)
{
	size_t len;
	ssize_t n;
	char buff[MAXLINE];

	fgets(buff,MAXLINE,stdin);
	len= strlen(buff);
	if(buff[len-1]=='\n')
	{
		len--;
	}
	write(writer,buff,len);

	while((n= read(reader,buff,MAXLINE))>0)
		write(STDOUT_FILENO,buff,n);

}

int main(int argc, char const *argv[])
{
	int readfd,writefd;

	if((mkfifo(FIFO1,FILE_MODE)<0)&&(errno!=EEXIST))
		cerr<<"client cant create fifo1"<<endl;
	if((mkfifo(FIFO2,FILE_MODE)<0)&&(errno!=EEXIST))
	{
		unlink(FIFO1);
		cerr<<"client cant create fifo2"<<endl;
	}
	writefd= open(FIFO1,O_WRONLY,0);
	readfd = open(FIFO2,O_RDONLY,0);

	client(readfd,writefd);

	exit(0);
	return 0;
}