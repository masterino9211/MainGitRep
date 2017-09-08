#pragma once

#include <SFML/System.hpp>

using namespace std;
using namespace sf;
/*
 * Timer class.
 * It is used for synchronizing scenes.
 */
class Timer {
public:
    /**
     * Constructor.
     */
    Timer( Time delta =  seconds(1.f/60.f));
    /**
     * Returns global time.
     */
    Time getGlobal();
    /**
     * Returns local time.
     */
    Time getLocal();
    /**
     * Resets local time.
     */
    void resetLocal();
    /**
     * Checks if window is ready to display next frame.
     */
    bool update();
    /**
     * Checks if window is ready to display next frame and passes local time.
     */
    bool update(float &local);
protected:
private:
    Time mGlobal; /**< Global time.*/
    Time mLocal; /**< Local time.*/
    Clock mClock; /**< Clock member.*/
    Time cDelta; /**< Time between two frames.*/
    Time mNext; /**< Time when next frame is ready, relatively to global time.*/
};
