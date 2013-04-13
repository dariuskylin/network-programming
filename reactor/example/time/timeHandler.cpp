/*Copyright 2012 NDSL. All Rights Reserved.
 * =====================================================================================
 *       Filename:  timeHandler.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  12/27/2012 01:14:56 PM
 *         Author:  dongyuchi (dongyuchi), dongyuchi@gmail.com
 *        Company:  UESTC.NDSL
 * =====================================================================================
 */
#include"timeHandler.h"
#include"Reactor.h"
#include"base.h"
#include<errno.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<time.h>

extern dk_reactor::Reactor g_reactor;

timeHandler::timeHandler(dk_reactor::handle_t handle) :
    EventHandler(handle) {
    buff_ = new char[dk_reactor::BuffLength];
}

timeHandler::~timeHandler() {
    fprintf(stderr,"timeHandler dtor!");
    delete [] buff_;
}

void timeHandler::handleRead() {
    
}

void timeHandler::handleWrite() {
    bzero(buff_, dk_reactor::BuffLength);
    time_t now;
    time(&now);
    sprintf(buff_,"current time: %s",ctime(&now));
    int ret = write(m_handle, buff_, strlen(buff_));
    if(ret < 0) {
        perror("write error!");
    }
    g_reactor.removeHandler(this);
    ::close(m_handle);
    delete this;
}

void timeHandler::handleError() {
  perror("timeHandle closed!");  
  g_reactor.removeHandler(this);
  ::close(m_handle);
  delete this;
}
