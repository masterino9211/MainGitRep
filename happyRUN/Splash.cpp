#include "Splash.h"
#include <cstdio>
#include "Algorithm.h"
#include <cmath>

using namespace sf;
using namespace std;

vector<  Drawable * > Splash::drawables()
{
    vector<Drawable *> drawables;
    for(int i = 0; i < mSprites.size(); i++) {
        drawables.push_back(&mSprites[i]);
    }
    drawables.push_back(&mCurtain);
    return drawables;
}

void Splash::handle(Event &event)
{
    //Only event handled in splash is close event.
    if(event.type == Event::Closed) {
        Handler handler;
        handler.type = Handler::Closed;
        mHandlers.push(handler);

    }
}


void Splash::init(Color &clearColor)
{
    // Data for this splash is initiated.
    mImage.loadFromFile(cImagePath);
    mTextures = Algorithm::textureVec(mImage);
    mSprites = Algorithm::spriteVec(mTextures, Vector2f(0, 0));

    mCurtain.setFillColor(cBackground);
    mCurtain.setSize(Vector2f(800, 600));
    mCurtain.setPosition(0, 0);
    clearColor = cBackground;

}

bool Splash::pollHandler(Handler &handler)
{

    if(mHandlers.empty()) {
        return false;
    }
    handler = mHandlers.top();
    mHandlers.pop();
    return true;
}

Splash::Splash(string imagePath, Color background, Time time, int next)
    : cBackground(background)
    , cImagePath(imagePath)
    , cTime(time.asSeconds())
    , cNext(next)
    , mCurtain()
{
}

bool Splash::update(float time)
{
    float param = time / cTime;
    if(param >= 1) {
        Handler handler;
        handler.type = Handler::ChangeSceneAndDestroy;
        handler.data = cNext;
        mHandlers.push(handler);
    }
    Color c = cBackground;
    //Opacity of curtain is changing from 255 to 0.
    c.a = (unsigned char)(255.f * (1 - sin(param * Algorithm::PI)));
    mCurtain.setFillColor(c);
    return false;
}
