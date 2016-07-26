#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define MAXLINE 100
using namespace std;

int main(int argc, char const *argv[])
{
	int sockfd,n;
	char recvline[MAXLINE+1];
	struct sockaddr_in servaddr;
	if(argc !=2)
	{
		cerr<<"usage: a.out <IPaddress>"<<endl;
	}
	if((sockfd = socket(AF_INET,SOCK_STREAM,0))<0)
	{
		cerr<<"socket_err"<<endl;
	}
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(3000);
	if(inet_pton(AF_INET,argv[1],&servaddr.sin_addr)<0)
	{
		cerr<<"inet_pton error for "<<argv[1]<<endl;
	}
	if(connect(sockfd,(sockaddr *)&servaddr,sizeof(servaddr)))
	{
		cerr<<"connect error"<<endl;
	}
	while((n = read(sockfd,recvline,MAXLINE))>0)
	{
		recvline[n] = 0;
		if(fputs(recvline,stdout) == EOF)
		{
			cerr<<"fputs error"<<endl;
		}
	}
	if(n<0)
	{
		cerr<<"read error"<<endl;
	}
	return 0;
}