/*Copyright 2012 NDSL. All Rights Reserved.
 * =====================================================================================
 *       Filename:  timeHandler.h
 *    Description:  
 *        Version:  1.0
 *        Created:  12/27/2012 01:14:22 PM
 *         Author:  dongyuchi (dongyuchi), dongyuchi@gmail.com
 *        Company:  UESTC.NDSL
 * =====================================================================================
 */
#ifndef TIMEHANDLER_H_
#define TIMEHANDLER_H_

#include"base.h"
#include"EventHandler.h"

class timeHandler : public dk_reactor::EventHandler {
    public:
        timeHandler(dk_reactor::handle_t);
        virtual ~timeHandler();
        //inherited from EventHandler
        void handleRead();
        void handleWrite();
        void handleError();
    private:
        char* buff_;
};
#endif  // TIMEHANDLER_H_
