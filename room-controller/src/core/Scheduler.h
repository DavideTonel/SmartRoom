#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "Task.h"
#include "config.h"


/**
 * Class representing a scheduler.
*/
class Scheduler {
private:
    int basePeriod;
    int nTasks;
    Task* taskList[MAX_TASKS];

public:
    /**
     * Init the scheduler with the given base period.
     * @param basePeriod the base period.
    */
    void init(int basePeriod);

    /**
     * Add a tsk to schedule.
     * @param task the task to schedule.
    */
    virtual bool addTask(Task* task);

    /**
     * Schedule.
    */
    virtual void schedule();
};

#endif
