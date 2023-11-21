/*
 * ClientCommunication.h
 *
 *  Created on: 20-Nov-2023
 *      Author: kumar
 */

#ifndef CLIENTCOMMUNICATION_H_
#define CLIENTCOMMUNICATION_H_
#include <iostream>
using namespace std;
class ClientCommunication {
private:


public:
	int sd;

	ClientCommunication();
	ClientCommunication(int sd);
	virtual ~ClientCommunication();
	void Communicate();
	string TerminateConnection();
	string ReceiveCommand();
	string SendResult();
	//string RecvUserNameAndPassword();
};

#endif /* CLIENTCOMMUNICATION_H_ */
