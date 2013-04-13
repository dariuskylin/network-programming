/*Copyright 2012 NDSL. All Rights Reserved.
 * =====================================================================================
 *       Filename:  echoHandler.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  12/25/12 14:20:31
 *         Author:  dongyuchi (dongyuchi), dongyuchi@gmail.com
 *        Company:  UESTC.NDSL
 * =====================================================================================
 */
#include"echoHandler.h"
#include"Reactor.h"
#include"base.h"
#include<errno.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>

extern dk_reactor::Reactor g_reactor;

echoHandler::echoHandler(dk_reactor::handle_t handle) :
    EventHandler(handle) {
    buff_ = new char[dk_reactor::BuffLength];   
    recv_ = new char[dk_reactor::BuffLength];
}

echoHandler::~echoHandler() {
    fprintf(stderr,"echoHandler dtor!\n");
    delete [] buff_;
    delete [] recv_;
}

void echoHandler::handleRead() {
   fprintf(stderr,"step into handleRead();the fd is %d \n", m_handle);
   bzero(buff_, dk_reactor::BuffLength); 
   fprintf(stderr,"before read()\n");
   int len = read(m_handle, buff_, dk_reactor::BuffLength);
   fprintf(stderr,"after read, the buff is: %s\n",buff_);
   if(len <= 0) {
      if(len == 0) {
          g_reactor.removeHandler(this);
          ::close(m_handle);
          delete this;
      }
      if(errno == EINTR) {
        return ;
      }
      perror("read error!");
      return ;
   }
   if(strncmp("exit", buff_, 4) == 0) {
      g_reactor.removeHandler(this);
      ::close(m_handle);
      delete this;
   }
   else {
      g_reactor.registerHandler(this, dk_reactor::event_write);
   }
}

void echoHandler::handleWrite() {
    bzero(recv_, dk_reactor::BuffLength);
    memcpy(recv_, buff_, dk_reactor::BuffLength);
    int len = write(m_handle, recv_, strlen(recv_));
    if(len < 0) {
        perror("write error!");
    }
    else {
        g_reactor.registerHandler(this, dk_reactor::event_read);
    }
}

void echoHandler::handleError() {
  perror("echoHandle closed!");  
  g_reactor.removeHandler(this);
  ::close(m_handle);
  delete this;
}
