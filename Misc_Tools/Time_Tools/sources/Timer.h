#ifndef  TIMER_H
#define  TIMER_H

#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>

/*
 * Author: Ermin Kreponic
 *     YouTube account:
 *         https://www.youtube.com/channel/UCrHYZGawEmV3MslXcYubNjg
 */

class Timer
{
    std::timed_mutex timedMutx;
    std::atomic_bool locked_;
    void lock()
    {
        timedMutx.lock();
        locked_ = true;
    }
    void unlock()
    {
        timedMutx.unlock();
        locked_ = false;
    }

    bool initialised = false;

    std::thread tThread;
    bool alive       = false;

    //Number of times to repeat user function
    long callNumber  = -1L;
    long repeatCount = -1L;

    //Interval between function calls
    unsigned intervalUnit;
    long signed interval;

    std::function<void(void)> funct = nullptr;

    void sleepAndRun()
    {
        switch(intervalUnit)
        {
            case timeUnits::milliseconds:
                timedMutx.try_lock_for(
                  std::chrono::milliseconds(interval) );
                break;
            case timeUnits::seconds:
                timedMutx.try_lock_for(
                  std::chrono::seconds(interval) );
                break;
            case timeUnits::minutes:
                timedMutx.try_lock_for(
                  std::chrono::minutes(interval) );
                break;
            case timeUnits::hours:
                timedMutx.try_lock_for(
                  std::chrono::hours(interval) );
                break;
        }

        if(alive)
            userFunction()();
    }
    void threadFunc()
    {
        if(callNumber == infinite)
            while(alive)
                sleepAndRun();
        else
            while(repeatCount--)
                sleepAndRun();
    }

    bool unitCheck(unsigned unit)
    {
        if( unit >= timeUnits::milliseconds && unit <= timeUnits::hours )
            return true;
        return false;
    }

public:
    static const long infinite = -1L;

    enum timeUnits
    {
        milliseconds,
        seconds,
        minutes,
        hours
    };

    Timer() { lock(); }
    Timer(const std::function<void(void)> &f) : funct(f) { lock(); }
    Timer(const std::function<void(void)> &f,
          const signed long &i, signed unit,
          const long repeat = infinite) : funct(f), interval(i),
            intervalUnit(unit), callNumber(repeat) { lock(); }
    ~Timer()
    { //In case wake never called
        if(locked_)
            unlock();
    }

    bool init()
    {
        if( !unitCheck(intervalUnit) )
            return false;

        initialised = true;
        return true;
    }

    void start(bool useThread=true)
    {
        if(!initialised)
            return;

        if(isAlive())
            return;

        alive = true;
        repeatCount = callNumber;
        if(useThread)
            tThread = std::thread(&Timer::threadFunc, this);
        else
            threadFunc();
    }
    void stop(bool bWake=true)
    {
        alive = false;
        //Allows for immediate shutdown of Timer
        if(bWake)
            wake();
        if(tThread.joinable())
            tThread.join();
    }
    //Premature return from sleep
    void wake()
    {
        if(locked_)
            unlock();
    }

    void setFunction(const std::function<void(void)> &f) { funct = f; }
    const std::function<void(void)> &userFunction() const { return funct; }


    bool isAlive() const { return alive; }


    bool setRepetitions(const long r)
    {
        if(alive)
            return false;

        callNumber = r;
        return true;
    }
    long remainingRepeat() const { return repeatCount; }
    long numRepitions() const { return callNumber; }


    bool setInterval(const unsigned long &i)
    {
        if(alive)
            return false;

        interval = i;
        return true;
    }
    unsigned long getInterval() const { return interval; }
    bool setIntervalUnit(signed unit)
    {
        if( !unitCheck(unit) )
            return false;

        intervalUnit = unit;
        return true;
    }
    unsigned getIntervalUnit()  const { return intervalUnit; }

};

#endif // TIMER_H
