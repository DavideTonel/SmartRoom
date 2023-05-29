#ifndef __TIMESERVICE__
#define __TIMESERVICE__


/**
 * Class used for store time.
*/
class TimeService {
private:
    int hours;
    
public:
    /**
     * Create a new time service.
    */
    TimeService();

    /**
     * Get the current hour.
     * @return the current hour.
    */
    int getHour();

    /**
     * Set the current hour.
     * @param hour the hour.
    */
    void setHour(int hours);
};

#endif
