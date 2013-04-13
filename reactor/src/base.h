/*Copyright 2012 NDSL. All Rights Reserved.
 * =====================================================================================
 *       Filename:  base.h
 *    Description:  
 *        Version:  1.0
 *        Created:  12/24/12 03:26:08
 *         Author:  dongyuchi (dongyuchi), dongyuchi@gmail.com
 *        Company:  UESTC.NDSL
 * =====================================================================================
 */
#ifndef BASE_H_
#define BASE_H_
namespace dk_reactor {
    typedef int handle_t;
    typedef unsigned int event_t;
    enum{
        event_read = 0x01,
        event_write = 0x02,
        event_error = 0x04,
    };
    enum demultiplexer_t{
        epoll_demultiplexer = 1,
        select_demultiplexer = 2,
    };
    const int BuffLength = 1024;
}
#endif  // BASE_H_
