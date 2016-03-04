#ifndef THREAD_HPP
#define THREAD_HPP

#include <thread>

/**
 * @brief The Thread class
 *
 * Represents a thread class. Depends on C++11 standard thread.
 */

class Thread
{

private:
    std::thread t;

public:
    Thread(){}

    /**
     * @brief startThread
     *
     * Public function for starts the thread.
     */
    void startThread()
    {
        this->t = std::thread( &Thread::run, this );
        this->t.detach();
    }

    /**
     * @brief killThread
     *
     * Public function for kill the thread.
     */
    void killThread()
    {
         this->halt();
    }

    /**
     * @brief run
     *
     * The child class implements this function and the startThread() just start this activity in new thread.
     */
    void virtual run() = 0;

    /**
     * @brief halt
     *
     * The child class implements this function and the killThread() just kill the thread.
     */
    void virtual halt() = 0;

    /**
     * @brief sleep
     * @param seconds -> sleep time in seconds
     *
     * Sleeping help function.
     */
    static void sleep( int seconds )
    {
        std::this_thread::sleep_for( std::chrono::milliseconds( seconds*1000 ) );
    }

    /**
     * @brief msleep
     * @param milliseconds -> sleep time in milliseconds
     *
     * Sleeping help function.
     */

    static void msleep( int milliseconds )
    {
        std::this_thread::sleep_for( std::chrono::milliseconds( milliseconds ) );
    }

    /**
     * @brief usleep
     * @param microseconds -> sleep time in microseconds
     *
     * Sleeping help function
     */
    static void usleep( int microseconds )
    {
        std::this_thread::sleep_for( std::chrono::microseconds( microseconds ) );
    }

};

#endif // THREAD_HPP
