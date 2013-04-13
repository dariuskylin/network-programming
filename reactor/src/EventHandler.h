/*Copyright 2012 NDSL. All Rights Reserved.
 * =====================================================================================
 *       Filename:  EventHandler.h
 *    Description:  
 *        Version:  1.0
 *        Created:  12/24/12 03:39:07
 *         Author:  dongyuchi (dongyuchi), dongyuchi@gmail.com
 *        Company:  UESTC.NDSL
 * =====================================================================================
 */
#ifndef EVENTHANDLER_H_
#define EVENTHANDLER_H_
#include"base.h"
namespace dk_reactor {
class EventHandler {
    public:
        virtual void handleRead() = 0;
        virtual void handleWrite() = 0;
        virtual void handleError() = 0;
        handle_t getHandle() {
            return m_handle;
        }
    protected:
        EventHandler(handle_t handle)
            : m_handle(handle) { }
        void setHandle(handle_t handle) {
            m_handle = handle;
        }
    protected:
        handle_t m_handle;
};
}
#endif  // EVENTHANDLER_H_
