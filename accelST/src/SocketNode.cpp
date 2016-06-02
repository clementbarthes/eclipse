/*
 * SocketNode.cpp
 *
 *  Created on: Nov 18, 2015
 *      Author: clement
 */

#include "SocketNode.h"

SocketNode::SocketNode() {
	fd = -1;
	bytes = 0;
	this->initConnection();
}

int SocketNode::connectToNode() {
	return connect(fd, (struct sockaddr*)&addr, sizeof(addr));
}

int SocketNode::readFromNode(char* readBuffer){
	bytes = read(fd, readBuffer, BUFSIZ+1);
	return bytes;
}

bool SocketNode::writeToNode(char* writeBuffer, int nBytes) {
	int bytesSent = write(fd, writeBuffer, nBytes);
	if (bytesSent == nBytes){
		return true;
	}
	return false;

}

int SocketNode::initConnection() {
	if ( (fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
		perror("socket error");
		return -1;
	}
	char socket_path[] = "/var/run/dataSocket";
	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path)-1);
	bytes = 0;
	return 0;
}

SocketNode::~SocketNode() {

}

