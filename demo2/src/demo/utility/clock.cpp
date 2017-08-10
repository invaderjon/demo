// clock.cpp
#include "clock.h"

namespace demo
{

namespace util
{

// MEMBER FUNCTIONS
void Clock::tick()
{
    using namespace std::chrono;

    SysClock::time_point now = SysClock::now();
    SysClock::duration dt = now - _time;

    _dt = _timeScale * duration_cast<FSeconds>( dt );
    _elapsed += duration_cast<SysClock::duration>( _dt );

    _time = now;
}

void Clock::reset()
{
    _time = SysClock::now();
    _elapsed = SysClock::duration( 0L );
    _dt = FSeconds( 0.0f );
    _timeScale = 1.0f;
}

} // End nspc util

} // End nspc demo