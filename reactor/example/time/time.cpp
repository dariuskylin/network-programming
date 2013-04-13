/*Copyright 2012 NDSL. All Rights Reserved.
 * =====================================================================================
 *       Filename:  time.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  12/27/2012 01:48:35 PM
 *         Author:  dongyuchi (dongyuchi), dongyuchi@gmail.com
 *        Company:  UESTC.NDSL
 * =====================================================================================
 */
#include"base.h"
#include"Reactor.h"
#include"timeListener.h"
#include"timeHandler.h"
#include<iostream>
#include<stdio.h>
#include<stdlib.h>

dk_reactor::Reactor g_reactor;

int main(int argc, char* argv[]) {
    if(argc < 3) {
        std::cerr<<"usage: "<<argv[0]<<" ip port"<<std::endl;
        return -1;
    }
    timeListener timeServer(argv[1], atoi(argv[2]));
    if(timeServer.start() < 0) {
        std::cerr<<"echo server failed to start!"<<std::endl;
        return -1;
    }
    std::cerr<<"time server is started!"<<std::endl;
    int ret = g_reactor.init();
    if(ret < 0) {
        std::cerr<<"reactor.init error!"<<std::endl;
    }
    g_reactor.registerHandler(&timeServer, dk_reactor::event_read);
    while(true) {
        g_reactor.handleEvents(100);
    }
    return 0;
}
