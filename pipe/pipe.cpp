#define MAXLINE 100

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <iostream>

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
	int pipe1[2],pipe2[2];
	pid_t childpid;
	pipe(pipe1);
	pipe(pipe2);
	if((childpid==fork())==0)
	{
		close(pipe1[1]);
		close(pipe2[0]);
		client(pipe1[0],pipe2[1]);
		exit(0);
	}
	close(pipe2[1]);
	close(pipe1[0]);
	server(pipe2[0],pipe1[1]);
	waitpid(childpid,NULL,0);
	return 0;
}