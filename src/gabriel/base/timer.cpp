/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *      _____       ___   _____   _____    _   _____   _               *
 *     /  ___|     /   | |  _  \ |  _  \  | | | ____| | |              *
 *     | |        / /| | | |_| | | |_| |  | | | |__   | |              *
 *     | |  _    / / | | |  _  { |  _  /  | | |  __|  | |              *
 *     | |_| |  / /  | | | |_| | | | \ \  | | | |___  | |___           *
 *     \_____/ /_/   |_| |_____/ |_|  \_\ |_| |_____| |_____|          *
 *                                                                     *
 *     gabriel is an angel from the Holy Bible, this engine is named   *
 *   gabriel, means bringing people good news. the goal of gabriel     *
 *   server engine is to help people to develop various online games,  *
 *   welcome you to join in.                                           *
 *                                                                     *
 *   @author: lichuan                                                  *
 *   @qq: 308831759                                                    *
 *   @email: 308831759@qq.com                                          *
 *   @site: www.lichuan.me                                             *
 *   @github: https://github.com/lichuan/gabriel                       *
 *   @date: 2014-02-23 21:30:01                                        *
 *                                                                     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "ace/Recursive_Thread_Mutex.h"
#include "gabriel/base/timer.hpp"

using namespace std;

namespace gabriel {
namespace base {

Timer_Handler::Timer_Handler(function<void()> call)
{
    m_call = call;    
    m_timer_id = -1;
}

void Timer_Handler::timer_id(int64 timer_id)
{
    m_timer_id = timer_id;
}
    
int Timer_Handler::handle_timeout (const ACE_Time_Value &current_time, const void *act)
{
    void *obj = const_cast<void*>(act);    
    Timer *holder = static_cast<Timer*>(obj);
    m_call();
    
    if(m_timer_id != -1)
    {
        holder->cancel_timer(m_timer_id);
    }

    return 0;
}
    
Timer::Timer()
{
}

Timer::~Timer()
{
    for(auto iter : m_timer_handlers)
    {
        TIMER_MGR::instance()->cancel(iter.first);
        delete iter.second;
    }
}

int64 Timer::schedule_timer(function<void()> call, uint32 interval, uint32 delay)
{
    ACE_Time_Value future_time = TIMER_MGR::instance()->current_time();
    uint32 delay_sec = delay / 1000;
    uint32 delay_usec = (delay % 1000) * 1000;
    uint32 interval_sec = interval / 1000;
    uint32 interval_usec = (interval % 1000) * 1000;    
    future_time += ACE_Time_Value(delay_sec, delay_usec);    
    Timer_Handler *handler = new Timer_Handler(call);
    int64 timer_id = 0;
    
    if(interval == 0)
    {
        timer_id = TIMER_MGR::instance()->schedule(handler, this, future_time);
        handler->timer_id(timer_id);
    }
    else
    {
        timer_id = TIMER_MGR::instance()->schedule(handler, this, future_time, ACE_Time_Value(interval_sec, interval_usec));
    }

    if(timer_id >= 0)
    {
        m_timer_handlers.insert(make_pair(timer_id, handler));
    }

    return timer_id;
}

void Timer::cancel_timer(int64 id)
{
    auto iter = m_timer_handlers.find(id);
    
    if(iter != m_timer_handlers.end())
    {
        delete iter->second;
        m_timer_handlers.erase(id);
    }
}

}
}
