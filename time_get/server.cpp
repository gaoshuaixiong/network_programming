#include <iostream>
#include <time>

int main(int argc, char const *argv[])
{
	int listenfd,connfd;
	struct sockaddr_in servaddr;
	char buff[MAXLINE];
	time_t ticks;
	if((listenfd = socket(AF_INET,SOCK_STREAM,0))<0)
	{
		cerr<<"socket_err"<<endl;
	}


	//listenfd  = socket(AF_INET,SOCK_STREAM,0);
	bzero(&servaddr,sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(3000);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(listenfd,(sockaddr *)&servaddr,sizeof(servaddr));

	if ( bind(listenfd, (sockaddr *)&servaddr,sizeof(servaddr)) != 0)
	{
		cerr<<"bind_err"<<endl;
	}
	listen(listenfd,SOMAXCONN);

	for(;;)
	{
		connfd  = accept
	}

	return 0;
}