/*Copyright 2012 NDSL. All Rights Reserved.
 * =====================================================================================
 *       Filename:  echoHandler.h
 *    Description:  
 *        Version:  1.0
 *        Created:  12/25/12 14:20:08
 *         Author:  dongyuchi (dongyuchi), dongyuchi@gmail.com
 *        Company:  UESTC.NDSL
 * =====================================================================================
 */
#include"base.h"
#include"EventHandler.h"

class echoHandler : public dk_reactor::EventHandler {
    public:
        echoHandler(dk_reactor::handle_t);
        virtual ~echoHandler();
        //inherited from EventHandler
        void handleRead();
        void handleWrite();
        void handleError();
    private:
        char* buff_;
        char* recv_;
};
