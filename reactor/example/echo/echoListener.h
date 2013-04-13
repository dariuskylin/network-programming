/*Copyright 2012 NDSL. All Rights Reserved.
 * =====================================================================================
 *       Filename:  echoListener.h
 *    Description:  
 *        Version:  1.0
 *        Created:  12/24/2012 07:49:12 PM
 *         Author:  dongyuchi (dongyuchi), dongyuchi@gmail.com
 *        Company:  UESTC.NDSL
 * =====================================================================================
 */
#ifndef ECHOLISTENER_H_
#define ECHOLISTENER_H_
#include<string>
#include"EventHandler.h"
#include"base.h"

class echoListener : public dk_reactor::EventHandler {
    public:
       echoListener(std::string ip, unsigned short port) :
           ip_(ip) , port_(port), EventHandler(-1) {  }
       int start();
       //inherited from EventHandler
       void handleRead();
       void handleWrite();
       void handleError();
    private:
        std::string ip_;       
        unsigned short port_;
};
#endif  // ECHOLISTENER_H_
