/*Copyright 2012 NDSL. All Rights Reserved.
 * =====================================================================================
 *       Filename:  server.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  12/20/2012 04:25:02 PM
 *         Author:  dongyuchi (dongyuchi), dongyuchi@gmail.com
 *        Company:  UESTC.NDSL
 * =====================================================================================
 */
#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<pthread.h>

#define BufferLength 1024 // buffer size

// function in new threads
void* str_echo(void* arg) {
    // detach threads from parent
    int ret = pthread_detach(pthread_self());
    if( ret != 0) {
        perror("pthread_detach error");
        pthread_exit(NULL);
    }
    int connfd = (int)arg;
    char buff[BufferLength];
    while(true) {
        bzero(buff, sizeof(buff));
        ret = read(connfd, buff, sizeof(buff));
        if(ret <= 0) {
            if(ret == 0) {
                close(connfd);
                break;
            }
            if(errno == EINTR) {
                continue;
            }
            perror("read error!");
            close(connfd);
            break;
        }
        ret = write(connfd, buff, strlen(buff));
        if(ret < 0) {
            perror("write error!");
            close(connfd);
            break;
        }
    }
    // threads exit
    pthread_exit(NULL);
}
int main(int argc, char* argv[]) {
    int ret;
    pthread_t tid;
    struct sockaddr_in servaddr;
    int connfd, listenfd;

    if(argc < 2){
        std::cerr<<"usage: "<<argv[0]<<" port"<<std::endl;
        return -1;
    }
    // create new socket
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    // handle error
    if(listenfd < 0) {
        perror("socket error!");
        return -1;
    } 
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi(argv[1]));
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    // bind struct 'servaddr' to server socket
    ret = bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    if( ret < 0) {
        perror("bind error!");
        return -1;
    }
    // tell kernel to listen at server socket
    ret = listen(listenfd, 64);
    if(ret<0) { 
        perror("listen error!");
        return -1;  
    }
    std::cerr<<"server is listening..."<<std::endl;
    while(true) {
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
        if(connfd < 0) {
            perror("accept error!");
            break;
        }
        // let threads to handle request
        ret = pthread_create(&tid, NULL, str_echo, (void *)connfd);
        if(ret != 0) {
            perror("pthread_create error!");
            break;
        }
    }
    return 0;
}
