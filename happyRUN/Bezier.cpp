#include "Bezier.h"
#include "Algorithm.h"
#include <cmath>

Bezier::Bezier(Vector2f p1, Vector2f p2)
    : mOrder(2)
    , mP1(p1)
    , mP2(p2)
    , mP3()
{
}

Bezier::Bezier(Vector2f p1, Vector2f p2, Vector2f p3)
    : mOrder(3)
    , mP1(p1)
    , mP2(p2)
    , mP3(p3)
{
}

Vector2f Bezier::position(float arg)
{
    if(mOrder == 2) {
        return mP1 + arg * (mP2 - mP1);
    }
    return (1 - arg) * (1 - arg) * mP1 + 2 * (1 - arg) * arg * mP2 + arg * arg * mP3;
}
Vector2f Bezier::direction(float arg)
{
    if(mOrder == 2) {
        return mP2 - mP1;
    }
    return 2 * (1 - arg) * (mP2 - mP1) + 2 * arg * (mP3 - mP2);
}


float Bezier::angle(float arg)
{
    Vector2f angle1 = direction(arg);
    return atan2(angle1.y, angle1.x) * 180 / Algorithm::PI + 90;
}

vector<Vector2i> Bezier::stops() const
{
    vector<Vector2i> s;
    s.push_back(Vector2i(mP1.y / 40, mP1.y / 40));
    s.push_back(Vector2i(mP2.y / 40, mP2.y / 40));
    if(mOrder == 3)
        s.push_back(Vector2i(mP2.y / 40, mP2.y / 40));
	return s;
}
