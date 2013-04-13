/*Copyright 2012 NDSL. All Rights Reserved.
 * =====================================================================================
 *       Filename:  Demultiplexer.h
 *    Description:  
 *        Version:  1.0
 *        Created:  12/24/2012 09:26:27 AM
 *         Author:  dongyuchi (dongyuchi), dongyuchi@gmail.com
 *        Company:  UESTC.NDSL
 * =====================================================================================
 */
#ifndef DEMULTIPLEXER_H_
#define DEMULTIPLEXER_H_

#include"EventHandler.h"

namespace dk_reactor {
class Demultiplexer {
    public:
        virtual ~Demultiplexer() { }
        virtual int registerHandler(EventHandler*, event_t) = 0;    
        virtual int removeHandler(EventHandler*) = 0;
        virtual int dispatch(int timeouts) = 0;
};
}
#endif  // DEMULTIPLEXER_H_
