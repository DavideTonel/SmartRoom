#ifndef __TASK__
#define __TASK__


/**
 * Class representing a task.
*/
class Task {
private:
    int myPeriod;
    int timeElapsed;

public:
    /**
     * Create a new task.
    */
    Task() {
      timeElapsed = 0;
    }

    /* periodic */
    /**
     * Initialize the task with the given period.
     * @param period the period of the task.
    */
    virtual void init(int period) {
      myPeriod = period;
    }

    /**
     * Executes the task.
    */
    virtual void tick() = 0;

    /**
     * Check if the task has to be execute.
     * @return true if the task has to be execute, false otherwise
    */
    bool updateAndCheckTime(int basePeriod) {
      timeElapsed += basePeriod;
      if (timeElapsed >= myPeriod) {
        timeElapsed = 0;
        return true;
      } else {
        return false; 
      }
    }
};

#endif
