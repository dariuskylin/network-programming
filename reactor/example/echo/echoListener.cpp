/*Copyright 2012 NDSL. All Rights Reserved.
 * =====================================================================================
 *       Filename:  echoServer.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  12/24/2012 09:47:47 PM
 *         Author:  dongyuchi (dongyuchi), dongyuchi@gmail.com
 *        Company:  UESTC.NDSL
 * =====================================================================================
 */
#include"echoListener.h"
#include"echoHandler.h"
#include"Reactor.h"
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<iostream>
#include<unistd.h>
#include<assert.h>

extern dk_reactor::Reactor g_reactor;

int echoListener::start() {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    int ret = -1;
    struct sockaddr_in servaddr;
    if( fd < 0) {
        perror("socket error!");
        return -1;
    }
    setHandle(fd);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port_);
    ret = inet_pton(AF_INET, ip_.c_str(), &servaddr.sin_addr);
    if(ret < 0) {
        perror("inet_pton error!");
        return -1;
    }
    ret = bind(fd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    if(ret < 0) {
        perror("bind error!");
        return -1;
    }
    ret = listen(fd, 64);
    if(ret < 0) {
        perror("listen error!");
        return -1;
    }
    std::cout<<"server is listening...."<<std::endl;   
    return 0;
}

void echoListener::handleRead() {
    fprintf(stderr,"step into echoListener::handleRead()\n");
    dk_reactor::handle_t connfd = accept(m_handle, (struct sockaddr*)NULL, NULL);
    if(connfd < 0) {
        perror("accept error!");
        fprintf(stderr,"accept error!");
    } 
    else
    {
        echoHandler* handler = new echoHandler(connfd);
        fprintf(stderr,"create echoHander::instance!\n");
        assert( handler!=NULL);
        int ret = g_reactor.registerHandler(handler, dk_reactor::event_read);
        if(ret < 0) {
            perror("registerHandler error");
            delete handler;
        }
        fprintf(stderr,"echoListener::register   echoHandler success!\n");
    }
}

void echoListener::handleWrite() {
    
}

void echoListener::handleError() {
    fprintf(stderr,"eventHandler %d closed!", m_handle);
    ::close(m_handle);
    g_reactor.removeHandler(this);
    delete this;
}
