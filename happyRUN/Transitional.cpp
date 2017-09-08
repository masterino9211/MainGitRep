#include "Transitional.h"

using namespace sf;
using namespace std;

vector<Drawable * > Transitional::drawables()
{
    vector<Drawable *> ret;
    return ret;
}

void Transitional::handle(Event &event)
{
    //Only event proccessed by this class is close event.
    if(event.type == Event::Closed) {
        Handler handler;
        handler.type = Handler::Closed;
        mHandlers.push(handler);

    }
}

void Transitional::init(Color &clearColor)
{
    clearColor = cStart;
}

bool Transitional::pollHandler(Handler &handler)
{
    if(mHandlers.empty())
        return false;

    handler = mHandlers.top();
    mHandlers.pop();
    return true;
}

Transitional::Transitional(Color start, Color end, Time time, int next)
    : cStart(start)
    , cEnd(end)
    , cTime(time.asSeconds())
    , cNext(next)
    , mCurrent(start)
    , r(end.r - start.r)
    , g(end.g - start.g)
    , b(end.b - start.b)
    , a(end.a - start.a)
{
}

bool Transitional::update(float time)
{

    //Background color lineary changes from start to end color.

    float param = time / cTime;
    if(param >= 1) {
        Handler handler;
        handler.type = Handler::ChangeScene;
        handler.data = cNext;
        mHandlers.push(handler);
        return false;
    }

    mCurrent.r = cStart.r + (unsigned char)(r * param);
    mCurrent.g = cStart.g + (unsigned char)(g * param);
    mCurrent.b = cStart.b + (unsigned char)(b * param);
    mCurrent.a = cStart.a + (unsigned char)(a * param);

    Handler handler;
    handler.type = Handler::ChangeClearColor;
    handler.color = mCurrent;
    mHandlers.push(handler);
    return false;
}
