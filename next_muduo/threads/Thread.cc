#include "next_muduo/threads/Thread.h"
#include "next_muduo/Log.h"

#include <thread>
#include <functional>
#include <iostream>
using namespace std;

namespace CurrentThread
{
  __thread int t_cachedTid = 0;
}

namespace nextMuduo {

Thread::Thread(std::shared_ptr<Task> task)
    :_task(task)
{
    LOG_CURRENT_LINE
}

Thread::Thread(Task::TaskCB taskCB)
{
    LOG_CURRENT_LINE
    _task.reset(new Task(taskCB));
}

Thread::~Thread()
{
    join();
    LOG_CURRENT_LINE
}

void Thread::start()
{
    if(_task) {
        _thread.reset(new std::thread(std::bind(&Task::performTask, _task.get())));
    }
}

void Thread::join()
{
    if(_thread) {
        _thread->join();
        _thread.reset();
    }
}
}
