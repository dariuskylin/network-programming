/*Copyright 2012 NDSL. All Rights Reserved.
 * =====================================================================================
 *       Filename:  echo.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  12/26/2012 01:08:00 AM
 *         Author:  dongyuchi (dongyuchi), dongyuchi@gmail.com
 *        Company:  UESTC.NDSL
 * =====================================================================================
 */
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include"base.h"
#include"Reactor.h"
#include"echoListener.h"
#include"echoHandler.h"

dk_reactor::Reactor g_reactor;

int main(int argc, char* argv[]) {
    if(argc < 3) {
        std::cerr<<"usage: "<<argv[0]<<" ip port"<<std::endl;
        return -1;
    }
    echoListener echoServer(argv[1], atoi(argv[2]));    
    if(echoServer.start() < 0) {
        std::cerr<<"echo server failed to start!"<<std::endl;
        return -1;
    }
    std::cerr<<"echo server is started!"<<std::endl;
    int ret =g_reactor.init();
    if(ret < 0) {
        std::cerr<<"reactor.init error"<<std::endl;
    }
    g_reactor.registerHandler(&echoServer, dk_reactor::event_read);
    while(true) {
        g_reactor.handleEvents(100);        
    }
    return 0;
}
