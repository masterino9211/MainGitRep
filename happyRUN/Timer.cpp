#include "Timer.h"

using namespace sf;


Timer::Timer(Time delta)
    : mGlobal()
    , mLocal()
    , mClock()
    , cDelta(delta)
    , mNext(delta)
{
}


Time Timer::getGlobal()
{
    return mGlobal;
}

Time Timer::getLocal()
{
    return mLocal;
}

void Timer::resetLocal()
{
    mLocal = Time::Zero;
}

bool Timer::update()
{
    Time change = mClock.restart();

    mGlobal += change;
    mLocal += change;

    if(mGlobal >= mNext) {
        mNext = mGlobal + cDelta;
        return true;
    }

    return false;
}

bool Timer::update(float &local)
{
    Time change = mClock.restart();

    mGlobal += change;
    mLocal += change;
    local = mLocal.asSeconds();
    if(mGlobal >= mNext) {
        mNext = mGlobal + cDelta;
        return true;
    }

    return false;
}
