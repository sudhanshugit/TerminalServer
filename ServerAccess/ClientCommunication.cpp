/*
 * ClientCommunication.cpp
 *
 *  Created on: 20-Nov-2023
 *      Author: kumar
 */

#include "ClientCommunication.h"

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
#include <fstream>

#define EOF "%^&EOF&^%"

#include <thread>

using namespace std;

ClientCommunication::ClientCommunication() {
	// TODO Auto-generated constructor stub

}

ClientCommunication::ClientCommunication(int sd) {
	// TODO Auto-generated constructor stub
	this->sd = sd;

}

ClientCommunication::~ClientCommunication() {
	// TODO Auto-generated destructor stub
}

void ClientCommunication :: Communicate(){
	//this->sd = sd;
	string sndMsg = "welcome to sudhanshu's linux server \n";
	if(send(sd,&sndMsg[0],sndMsg.length(),0)==-1)
		perror("send welcome:");

	//if(send(sd,&sndMsg[0],sndMsg.length(),0)==-1)
		//perror("send welcome");

	bool connect = true;

	while(connect){

		char cmd[500];
		memset(cmd,'\0',sizeof(char)*500);
		if(recv(sd,cmd,500,0)==-1)
			perror("recv 1");
		cout<<"cmd from client : --- "<<cmd<<"\n";
		//close connection
		if(strcasecmp(cmd,"Exit")==0 || strlen(cmd) == 0)
		{
			cout<<"client exited\n";
			break;
		}
		char fileName[1000];
		memset(fileName,'\0',sizeof(char)*1000);
		if(recv(sd,fileName,1000,0)==-1)
			perror("recv");
		cout<<"fileName from client : --- "<<fileName<<"\n";

		int exitStatus = system(cmd);
		cout<<"system exit status : "<< exitStatus;
		ifstream fin;

		fin.open(fileName);
		//FILE *fp;
		//int status;
		//char cmdOutput[1000];
		//fp = popen(cmd,"r");
		//fin.seekg(0,ios::)
		cout<<"start sending output file\n";
		string line;
		int cntLine =0;
		while(getline(fin,line)){
			//string line;

			cout<<line;
			string fineof = fin.eof() ? "\ntrue\n":"\nfalse\n";
				cout<<fineof;
			if(fin.eof()==true) {
				cout<<"break file read loop";
				break;
			}
			line = line + "\n";
			int sendSuccess = send(sd,&line[0],line.length(),0);
			cout<<"send success "<<sendSuccess<<"\n";
			if(sendSuccess==-1)
			{
				perror("send file :");
				//break;
			}
		}
		cout<<"end sending output file\n";
		fin.close();
		if(send(sd,EOF,strlen(EOF),0)==-1){
			perror("send eof :");
			//break;
		}


		//break;
		/*while(fgets(cmdOutput,1000,fp)!=NULL){
			//getline(cin,line);
			cout<<cmdOutput<<"\n";
			if(send(sd,cmdOutput,strlen(cmdOutput),0)==-1)
				perror("send");
			cout<<cmdOutput<<"\n";

		}*/

	}

}

