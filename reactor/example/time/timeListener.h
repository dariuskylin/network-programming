/*Copyright 2012 NDSL. All Rights Reserved.
 * =====================================================================================
 *       Filename:  timeListener.h
 *    Description:  
 *        Version:  1.0
 *        Created:  12/27/2012 12:49:00 PM
 *         Author:  dongyuchi (dongyuchi), dongyuchi@gmail.com
 *        Company:  UESTC.NDSL
 * =====================================================================================
 */
#ifndef TIMELISTENER_H_
#define TIMELISTENER_H_

#include"base.h"
#include"EventHandler.h"
#include<string>

class timeListener : public dk_reactor::EventHandler {
    public:
        timeListener(std::string ip, unsigned short port) :
            ip_(ip), port_(port), EventHandler(-1) { }
        int start();
        //inherited from EventHandler
        void handleRead();
        void handleWrite();
        void handleError();
    private:
        std::string ip_;
        unsigned short port_;
};

#endif  // TIMELISTENER_H_
