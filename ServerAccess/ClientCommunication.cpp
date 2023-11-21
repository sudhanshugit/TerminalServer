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

	bool connect = true;

	while(connect){



		if(send(sd,&sndMsg[0],sndMsg.length(),0)==-1)
					perror("send");
		char* cmd;
		if(recv(sd,cmd,500,0)==-1)
			perror("recv");
		cout<<cmd<<"\n";


		/*char* fileName;
		if(recv(sd,cmd,500,0)==-1)
			perror("recv");
		cout<<fileName<<"\n";*/

		/*ifstream fin;
		string line;
		fin.open(fileName);*/
		FILE *fp;
		int status;
		char cmdOutput[1000];
		fp = popen(cmd,"r");

		while(fgets(cmdOutput,1000,fp)!=NULL){
			//getline(cin,line);
			if(send(sd,cmdOutput,strlen(cmdOutput),0)==-1)
				perror("send");
			cout<<cmdOutput<<"\n";

		}

	}

}

