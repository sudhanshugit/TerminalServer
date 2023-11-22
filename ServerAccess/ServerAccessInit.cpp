/*
 * ServerAccessInit.cpp
 *
 *  Created on: 20-Nov-2023
 *      Author: kumar
 */

#include "ServerAccessInit.h"
#include <iostream>

#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <netdb.h>

#include <thread>
#include "ClientCommunication.h"
//#include "ip_check.h"
#define MYPORT "3228"
#define SIZE 10


using namespace std;

int main(int argc, char* argv[]){
	ServerAccessInit s;// = new ServerControlInit();
	s.initServer();
};


ServerAccessInit::ServerAccessInit() {
	// TODO Auto-generated constructor stub

}

ServerAccessInit::~ServerAccessInit() {
	// TODO Auto-generated destructor stub
}

int ServerAccessInit::initServer(){
	//cout<<"server is running";

	int sockfd,status;// to get socket and status of getaddrinfo....
	struct addrinfo hints; // to set up things in advance
	struct addrinfo *server_info; // to put in the server information
	struct sockaddr_storage their_addr;
	socklen_t addr_size;
	memset(&hints,0,sizeof(hints));
	hints.ai_family=AF_UNSPEC;
	hints.ai_socktype= SOCK_STREAM;
	hints.ai_flags=AI_PASSIVE;
	if ((status=getaddrinfo(NULL,MYPORT,&hints,&server_info)) !=0)
	{
		perror("getaddrinfo error :");
		exit(1);
	}
	sockfd= socket(server_info->ai_family,server_info->ai_socktype,server_info->ai_protocol);
	if (sockfd<0) perror("socket error::");
	int bind_status;//gettint the bind status
	bind_status=bind(sockfd,server_info->ai_addr,server_info->ai_addrlen);
	if (bind_status==-1)
		{perror("bind failed :");}
	else	puts ("BIND SUCCESSFUL\n");
	if (listen(sockfd,SIZE)<0)
		printf ("the listening failed\n");
	puts("waiting for incoming connections...\n");
	socklen_t sin_size = sizeof(their_addr);
	//unsigned int sin_size= sizeof(their_addr);
	int new_fd[SIZE];
	int pid[SIZE];
	int i=1;
	while(i<SIZE){
		printf("waiting for next incoming connection ....\n");
		if ((new_fd[i]=accept(sockfd,(struct sockaddr *)&their_addr,&sin_size))==-1)
		{
			perror ("not accepted");
			continue;
		}
		//int flag=0;
		struct sockaddr_in* pv4Addr = (struct sockaddr_in*)&their_addr;
		struct in_addr ipAddr = pv4Addr->sin_addr;

		printf("connection from  - %d.%d.%d.%d\n",
				int((ipAddr.s_addr&0xFF)),
				int((ipAddr.s_addr&0xFF00)>>8),
				int((ipAddr.s_addr&0xFF0000)>>16),
				int((ipAddr.s_addr&0xFF000000)>>24));

		//printf("server got connection from %s\n",str);
		//cout<<("server got connection from" )<<inet_ntoa(their_addr.sin_addr))
		ClientCommunication cc;// = new ClientCommunication();
		cc.sd = new_fd[i];
		thread th1(&ClientCommunication::Communicate,&cc);
		th1.join();
		cout<<"thread create\n";
		i++;
		printf("%d %d\n",i,pid[i]);
		if (i>=SIZE) break;
	}
	return 0;
}

