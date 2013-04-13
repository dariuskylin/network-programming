/*Copyright 2012 NDSL. All Rights Reserved.
 * =====================================================================================
 *       Filename:  EpollDemultiplexer.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  12/24/2012 09:40:18 AM
 *         Author:  dongyuchi (dongyuchi), dongyuchi@gmail.com
 *        Company:  UESTC.NDSL
 * =====================================================================================
 */
#include"base.h"
#include"EpollDemultiplexer.h"
#include<sys/epoll.h>
#include<errno.h>
#include<stdio.h>
#include<assert.h>
#include<unistd.h>
#include<vector>
namespace dk_reactor {
    EpollDemultiplexer::EpollDemultiplexer() {
        epfd = epoll_create(1024);//size is unused since linux 2.6.8
        assert(epfd > 0);
        events_num = 0;
    }

    EpollDemultiplexer::~EpollDemultiplexer() {
        if(epfd > 0)
            ::close(epfd);
    }

    int EpollDemultiplexer::registerHandler(EventHandler* eh, event_t event) {
        epoll_event ep_event;
        ep_event.data.ptr = eh;
        ep_event.events = 0;

        if(event & event_read) {
            ep_event.events |= EPOLLIN;
            fprintf(stderr,"EPOLLIN is registered!\n");
        } 
        if(event & event_write) {
            ep_event.events |= EPOLLOUT;
        }
        if(event & event_error) {
            ep_event.events |= EPOLLERR;
            ep_event.events |= EPOLLHUP;
        }
        int res = -1;
        res = epoll_ctl(epfd, EPOLL_CTL_ADD, eh->getHandle(), &ep_event);
        fprintf(stderr,"fd %d is epoll_ctl_Add;the return value is:%d \n",eh->getHandle(),res);
        if(res != 0) {
           if(errno == EEXIST) {
               res = epoll_ctl(epfd, EPOLL_CTL_MOD, eh->getHandle(),&ep_event);
               if(res != 0)
                   return -1;
               else {
                   return 0;
               }
           }
           else
              return -1; 
        }
        events_num++;
        fprintf(stderr,"events_num = %d\n",events_num);
        return 0;
    }

    int EpollDemultiplexer::removeHandler(EventHandler* eh) { 
        //if(errno == EINTR || errno == EEXIST)
            //return 0;
        epoll_event ep_event;
        int ret = epoll_ctl(epfd, EPOLL_CTL_DEL, static_cast<int>(eh->getHandle()), &ep_event);
        if(ret != 0) {
            if(errno == ENOENT) {
                perror("fd is not  registered  with  this epoll instance");
            }
            perror("epoll_ctl(del) error!");
            return -1;
        }
        events_num--;
        return 0;
    } 
    int EpollDemultiplexer::dispatch(int timeouts) {
        int events_count = events_num;
        std::vector<epoll_event> ep_events(events_count);
        //fprintf(stderr,"vector size = %d;events_num = %d \n",ep_events.size(), events_num);
        int nfds = epoll_wait(epfd, &ep_events[0], events_count, timeouts);    
        if(nfds > 0) {
            fprintf(stderr,"epoll_wait captured something:events_num=%d\n",events_count);
            for(int index = 0; index < nfds; index++ ) {
                EventHandler* handler = 
                    static_cast<EventHandler*>(ep_events[index].data.ptr);
                assert(handler != NULL);
                if((ep_events[index].events & EPOLLERR) ||
                       (ep_events[index].events & EPOLLHUP)) {
                    handler->handleError();
                }
                else {
                  if(ep_events[index].events & EPOLLIN) {
                    fprintf(stderr,"handler->handleRead() \n");
                    handler->handleRead();
                  }  
                  if(ep_events[index].events & EPOLLOUT) {
                    fprintf(stderr,"handler->handleWrite() \n");
                    handler->handleWrite();
                  }
                }
            }
        }
        return nfds;
    }

}
