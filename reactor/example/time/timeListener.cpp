/*Copyright 2012 NDSL. All Rights Reserved.
 * =====================================================================================
 *       Filename:  timeListener.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  12/27/2012 12:55:48 PM
 *         Author:  dongyuchi (dongyuchi), dongyuchi@gmail.com
 *        Company:  UESTC.NDSL
 * =====================================================================================
 */
#include"timeListener.h"
#include"timeHandler.h"
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

int timeListener::start() {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    int ret = -1;
    struct sockaddr_in servaddr;
    if(fd < 0) {
        perror("socket error!");
        return -1;
    }
    setHandle(fd);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port  = htons(port_);
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
    std::cerr<<"time server is listening..."<<std::endl;
    return 0;
}

void timeListener::handleRead() {
    fprintf(stderr,"step into timeListener::handleRead()\n");
    dk_reactor::handle_t connfd = accept(m_handle, (struct sockaddr*)NULL, NULL);
    if(connfd < 0) {
        perror("accept error!");
        fprintf(stderr,"accept error!");
    } 
    else
    {
        timeHandler* handler = new timeHandler(connfd);
        fprintf(stderr,"create timeHander::instance!\n");
        assert( handler!=NULL);
        int ret = g_reactor.registerHandler(handler, dk_reactor::event_write);
        if(ret < 0) {
            perror("registerHandler error");
            delete handler;
        }
        fprintf(stderr,"timeListener::register   timeHandler success!\n");
    }
}

void timeListener::handleWrite() {
    
}

void timeListener::handleError() {
    fprintf(stderr,"eventHandler %d closed!", m_handle);
    ::close(m_handle);
    g_reactor.removeHandler(this);
    delete this;
}
