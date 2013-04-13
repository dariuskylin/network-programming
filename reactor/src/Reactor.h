/*Copyright 2012 NDSL. All Rights Reserved.
 * =====================================================================================
 *       Filename:  Reactor.h
 *    Description:  
 *        Version:  1.0
 *        Created:  12/24/12 04:14:39
 *         Author:  dongyuchi (dongyuchi), dongyuchi@gmail.com
 *        Company:  UESTC.NDSL
 * =====================================================================================
 */
#ifndef REACTOR_H_
#define REACTOR_H_
#include"base.h"
#include"EventHandler.h"
#include"Demultiplexer.h"
namespace dk_reactor {
class Reactor {
    public:
        Reactor();
        int init();
        int registerHandler(EventHandler*, event_t);
        int removeHandler(EventHandler*);
        int handleEvents(int timeouts);
    private:
        int readConfig();
        Reactor(const Reactor&);
        Reactor& operator=(const Reactor& );
    private:
        Demultiplexer* demultiplexer;
};
}
#endif  // REACTOR_H_
