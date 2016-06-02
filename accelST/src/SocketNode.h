/*
 * SocketNode.h
 *
 *  Created on: Jun 2, 2016
 *      Author: developer
 */

#ifndef SOCKETNODE_H_
#define SOCKETNODE_H_

#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <unistd.h>

class SocketNode {
	struct sockaddr_un addr;
	int fd;
	int bytes;


public:
	SocketNode();
	int connectToNode();
	int initConnection();
	int readFromNode(char* readBuffer);
	bool writeToNode(char* writeBuffer, int nBytes);
	virtual ~SocketNode();
};

#endif /* SOCKETNODE_H_ */
