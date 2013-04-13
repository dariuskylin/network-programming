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

#define BufferLength 1024
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
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) {
        perror("socket error!");
        return -1;
    }
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi(argv[2]));
    ret = inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    if(ret < 0 ){
        perror("inet_pton error!");
        return -1;
    }
    std::cout<<"before connect"<<std::endl;
    ret = connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    if(ret < 0) {
        perror("connet error!");
        return -1;
    }
    bzero(buff, sizeof(buff));
    bzero(recv, sizeof(recv));
    ret = read(sockfd, recv, sizeof(recv));
    if(ret <= 0) {
        if(ret == 0) {
            close(sockfd);
            std::cout<< "connectioin closed!" <<std::endl;
            return -1;
        }
        if(errno == EINTR) {
        }
        close(sockfd);
        perror("read error!");
        return -1;
    }
    std::cerr<<">>"<<recv<<std::endl;
    return 0;
}
