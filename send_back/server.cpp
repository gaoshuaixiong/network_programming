#include "network.h"
#include <iostream>
using namespace std;
void dg_echo(int sockfd,sockaddr *pcliaddr,socklen_t clilen)
{
	int n;
	socklen_t  len;
	char mesg[MAXLINE];
	for(;;)
	{
		len = clilen;
		n = recvfrom(sockfd,mesg,MAXLINE,0,pcliaddr,&len);
		cout<<n<<endl;
		sendto(sockfd,mesg,n,0,pcliaddr,len);

	}
}

int main(int argc, char const *argv[])
{
	int sockfd;
	struct sockaddr_in servaddr,cliaddr;
	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(UDP_SERVEPORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(sockfd,(sockaddr *)&servaddr,sizeof(servaddr));
	dg_echo(sockfd,(sockaddr *)&cliaddr,sizeof(cliaddr));

	return 0;
}