/*Copyright 2012 NDSL. All Rights Reserved.
 * =====================================================================================
 *       Filename:  server.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  12/20/2012 03:40:42 PM
 *         Author:  dongyuchi (dongyuchi), dongyuchi@gmail.com
 *        Company:  UESTC.NDSL
 * =====================================================================================
 */
#include<iostream>
#include<time.h>
#include<sys/time.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>

#define BufferLength 1024

int main(int argc, char* argv[]) {
    int connfd, listenfd;
    int ret;
    struct sockaddr_in servaddr;
    pid_t pid;
    char buff[BufferLength];

    if(argc < 2) {
        std::cerr<<"usage: "<<argv[0]<<" port"<<std::endl;
        return -1;
    }
    // create new socket
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    // handle socket error
    if(listenfd < 0) {
        perror("socket error!");
        return -1;
    }
    // configure struct 'servaddr'
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi(argv[1]));
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    // bind struct 'servaddr' to server socket
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
    // server is listening...
    std::cout<<"server is listening ..."<<std::endl;
    // step into loop to handle request
    while(true) {
        // accept a request
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
        if(connfd < 0) {
            // if interrupt occurs
            if(errno == EINTR) {
                continue;
            }
            perror("accept error!");
            break;
        }
        // fork new child process to handle request
        if((pid = fork()) == 0) { // if this is child process
            close(listenfd);
            while(true) {
                bzero(buff, sizeof(buff));
                ret = read(connfd, buff, sizeof(buff));
                if( ret <= 0) {
                    if( ret == 0) {
                        close(connfd);
                        break;
                    }
                    if( errno == EINTR) {
                        continue;
                    }
                    close(connfd);
                    perror("read error!");
                    break;
                }
                ret = write(connfd, buff, strlen(buff));
                if(ret < 0 ) {
                    perror("write error!");
                    break;
                }
            }
            exit(1);
        }  // end child process
        // this is in parent process
        close(connfd);
    }
    return 0;
}
