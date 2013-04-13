/*Copyright 2012 NDSL. All Rights Reserved.
 * =====================================================================================
 *       Filename:  server.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  12/30/2012 05:49:57 PM
 *         Author:  dongyuchi (dongyuchi), dongyuchi@gmail.com
 *        Company:  UESTC.NDSL
 * =====================================================================================
 */
#include<iostream>
#include<sys/socket.h>
#include<sys/epoll.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

#define BufferLength 1024   // buffer size
#define MaxEvents 1024

int main(int argc, char* argv[]) {
    int connfd, listenfd;
    char buff[BufferLength];
    struct sockaddr_in servaddr;
    int epfd;  // for epoll 
    struct epoll_event events[MaxEvents];
    struct epoll_event ev;
    int ret = -1;
    if(argc < 2) {
        std::cerr<<"usage: "<<argv[0]<<" port"<<std::endl;
        return -1;
    }
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd < 0) {
        perror("socket error!");
        return -1;
    }
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi(argv[1]));
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    ret = bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    if(ret < 0) {
        perror("bind error!");
        return -1;
    }
    // tell kernel to listen at server socket
    ret = listen(listenfd, 64);
    if(ret < 0) {
        perror("listen error!");
        return -1;
    }
    epfd = epoll_create(MaxEvents);
    if(epfd < 0) {
        perror("epoll_create error!");
        return -1;
    }
    ev.data.fd = listenfd;
    ev.events = EPOLLIN;
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev);
    if(ret < 0) {
        perror("epoll_ctl_add error!");
        return -1;
    }

    return 0;
}
