// clock.h
//
// Keeps track of elapsed time.
//
#ifndef DEMO_CLOCK_H
#define DEMO_CLOCK_H

#include <chrono>

namespace demo
{

namespace util
{

class Clock
{
  public:
    // TYPES
    /**
     * Defines the internal clock used by the system.
     */
    typedef std::chrono::steady_clock SysClock;

  private:
    // TYPES
    typedef std::chrono::duration<float> FSeconds;

    // MEMBERS
    /**
     * The last recorded time.
     */
    SysClock::time_point _time;

    /**
     * The total elapsed time.
     */
    SysClock::duration _elapsed;

    /**
     * The tick cycle elapsed time.
     */
    FSeconds _dt;

    /**
     * The time scale.
     */
    float _timeScale;

  public:
    // CONSTRUCTORS
    /**
     * Construct a new Clock.
     */
    Clock();

    /**
     * Construct a copy of a Clock.
     * @param other The other clock.
     */
    Clock( const Clock& other );

    /**
     * Destruct the clock.
     */
    ~Clock();

    // OPERATORS
    /**
     * Assign this as a copy of another Clock.
     * @param other The other clock.
     * @return This.
     */
    Clock& operator=( const Clock& other );

    // ACCESSOR FUNCTIONS
    /**
     * Get the time between the most recent tick and the one before it.
     * @return Delta time in seconds.
     */
    float dt() const;

    /**
     * Get the time scaling factor.
     * @return The time scale factor.
     */
    float timeScale() const;

    /**
     * Get the total accumulated elapsed time.
     * @return The elapsed time.
     */
    SysClock::duration elapsed() const;

    // MUTATOR FUNCTIONS
    /**
     * Set the time scaling factor.
     * If this is negative time will move backwards, which is valid.
     * @param timeScale The time scale factor.
     */
    void setTimeScale( float timeScale );

    // MEMBER FUNCTIONS
    /**
     * Recompute the elapsed time.
     */
    void tick();

    /**
     * Reset the clock.
     */
    void reset();
};

// CONSTRUCTORS
inline
Clock::Clock() : _time( SysClock::now() ), _elapsed( 0L ), _dt( 0.0f ),
                 _timeScale( 1.0f )
{
}

inline
Clock::Clock( const Clock& other )
        : _time( other._time ), _elapsed( other._elapsed ), _dt( other._dt ),
          _timeScale( other._timeScale )
{
}

inline
Clock::~Clock()
{
}

// OPERATORS
inline
Clock& Clock::operator=( const Clock& other )
{
    _time = other._time;

    return *this;
}

// ACCESSOR FUNCTIONS
inline
float Clock::dt() const
{
    return _dt.count();
}

inline
float Clock::timeScale() const
{
    return _timeScale;
}

inline
Clock::SysClock::duration Clock::elapsed() const
{
    return _elapsed;
}

// MUTATOR FUNCTIONS
inline
void Clock::setTimeScale( float timeScale )
{
    _timeScale = timeScale;
}

} // End nspc util

} // End nspc demo

#endif // DEMO_CLOCK_H
