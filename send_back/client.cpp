#include "network.h"
#include <iostream>
using namespace std;




void dg_cli(istream &cin,int sockfd,const sockaddr *pseraddr,socklen_t servlen)
{
	int n;
	size_t maxline = MAXLINE;
	string sendline;
	char recvline[MAXLINE+1];
	while(getline(cin,sendline))
	{
		sendto(sockfd,sendline.data(),sendline.size(),0,pseraddr,servlen);
		n = recvfrom(sockfd,recvline,maxline,0,NULL,NULL);
		recvline[n]=0;
		cout<<recvline<<endl;
	}
}








int main(int argc, char const *argv[])
{
	int sockfd;
	struct sockaddr_in servaddr;
	if(argc!=2)
	{
		cerr<<"usage: udpcli <ipadress>"<<endl;
		return -1;
	}
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	if(0==inet_aton(argv[1],&(servaddr.sin_addr)))
	{
		cerr<<"error in inet_aton"<<endl;
		return -1;
	}
	servaddr.sin_port = htons(UDP_SERVEPORT);
	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	dg_cli(cin,sockfd,(sockaddr *)&servaddr,sizeof(servaddr));
	return 0;
}