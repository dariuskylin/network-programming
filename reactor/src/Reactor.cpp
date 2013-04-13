/*Copyright 2012 NDSL. All Rights Reserved.
 * =====================================================================================
 *       Filename:  Reactor.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  12/24/12 04:20:45
 *         Author:  dongyuchi (dongyuchi), dongyuchi@gmail.com
 *        Company:  UESTC.NDSL
 * =====================================================================================
 */
#include"Reactor.h"
#include"EpollDemultiplexer.h"
#include<stdio.h>


    dk_reactor::Reactor::Reactor() {
        demultiplexer = 0;
    }
    int dk_reactor::Reactor::init() {
        int type = readConfig();
        demultiplexer_t de_type = static_cast<demultiplexer_t>(type);
        switch(de_type) {
            case epoll_demultiplexer:
                fprintf(stderr,"EpollDemultiplexer is selected!\n");
                demultiplexer = new EpollDemultiplexer();
                break;
            case select_demultiplexer:
                //demultiplexer = new SelectDemultiplexer();
                break;
            default:
                demultiplexer = new EpollDemultiplexer();
                break;
        }
        return type;
    }

    int dk_reactor::Reactor::readConfig() {
        demultiplexer_t type =epoll_demultiplexer;        
        return type;
    }
    
    int dk_reactor::Reactor::registerHandler(EventHandler* eh, event_t event) {
        fprintf(stderr,"Reactor::registerHandler\n");
        if(demultiplexer == 0)
            return -1;
        return demultiplexer->registerHandler(eh, event);
    }
    
    int dk_reactor::Reactor::removeHandler(EventHandler* eh) {
        if(demultiplexer == 0) 
            return -1;
        return demultiplexer->removeHandler(eh);
    }
    int dk_reactor::Reactor::handleEvents(int timeouts) {
        if(demultiplexer == 0) 
            return -1;
        return demultiplexer->dispatch(timeouts);
    }
