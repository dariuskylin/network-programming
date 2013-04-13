/*Copyright 2012 NDSL. All Rights Reserved.
 * =====================================================================================
 *       Filename:  EpollDemultiplexer.h
 *    Description:  
 *        Version:  1.0
 *        Created:  12/24/2012 09:33:00 AM
 *         Author:  dongyuchi (dongyuchi), dongyuchi@gmail.com
 *        Company:  UESTC.NDSL
 * =====================================================================================
 */
#ifndef EPOLLDEMULTIPLEXER_H_
#define EPOLLDEMULTIPLEXER_H_
#include"Demultiplexer.h"
namespace dk_reactor {
    class EpollDemultiplexer : public Demultiplexer {
        public:
            EpollDemultiplexer();
            ~EpollDemultiplexer();
            int registerHandler(EventHandler*, event_t);
            int removeHandler(EventHandler*);
            int dispatch(int timeouts);
        private:
            int epfd;
            int events_num;
    };
}
#endif  // EPOLLDEMULTIPLEXER_H_
