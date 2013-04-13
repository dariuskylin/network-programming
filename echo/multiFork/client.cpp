/*Copyright 2012 NDSL. All Rights Reserved.
 * =====================================================================================
 *       Filename:  client.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  12/20/2012 01:02:24 PM
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
#include<time.h>
#include<sys/time.h>

#define BufferLength 1024  // buffer size

int main(int argc, char* argv[]) {
    int sockfd, n;
    char buff[BufferLength];
    char recv[BufferLength];
    struct sockaddr_in servaddr;
    int ret;
    if(argc < 3) {
        std::cout<<"Usage: "<<argv[0]
            <<" ip port"<<std::endl;
        return -1;
    }
    // create new socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) {
        perror("socket error!");
        return -1;
    }
    // configure struct 'servaddr'
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi(argv[2]));
    ret = inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    if(ret < 0 ){
        perror("inet_pton error!");
        return -1;
    }
    ret = connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    if(ret < 0) {
        perror("connet error!");
        return -1;
    }
    std::cout<<"server connected!"<<std::endl;
    // step into loop to write and echo
    while(true) {
        bzero(buff, sizeof(buff));
        bzero(recv, sizeof(recv));
        // input strings from stdin
        if((fgets(buff, BufferLength, stdin)) == NULL) {
            perror("fgets error!");
            break;
        }
        // send to server
        ret = write(sockfd, buff, strlen(buff));
        if(ret < 0) {
            perror("write error!");
            return -1;
        }
        // read echo string from server
        ret = read(sockfd, recv, sizeof(recv));
        if(ret <= 0) {
            // if FIN received
            if(ret == 0) {
                close(sockfd);
                std::cout<< "connectioin closed!" <<std::endl;
                return -1;
            }
            // if interrupt occurs when read
            if(errno == EINTR) {
                continue;
            }
            close(sockfd);
            perror("read error!");
            return -1;
        }
        // print echo string to client
        std::cerr<<">>"<<recv<<std::endl;
    }
    return 0;
}
