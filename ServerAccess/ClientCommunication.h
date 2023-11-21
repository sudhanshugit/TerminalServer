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
public:
	ClientCommunication();
	virtual ~ClientCommunication();
	string TerminateConnection();
	string ReceiveCommand();
	string SendResult();
	//string RecvUserNameAndPassword();
};

#endif /* CLIENTCOMMUNICATION_H_ */
