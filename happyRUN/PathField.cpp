#include "PathField.h"

PathField::PathField(int x, int y, Texture& texture)
    : mSprite(nullptr)
    , mTexture(&texture)
    , mHandlers()
	, mUpdate(true)
{
    mSprite = new Sprite;
    mSprite->setTexture(*mTexture);
    mSprite->setPosition(40 * y, 40 * x);
}

PathField::~PathField()
{
    delete mSprite;
}

bool PathField::passable()
{
    return true;
}

void PathField::process(Handler& handler)
{

}

bool PathField::pollHandler(Handler& handler)
{
    if(mHandlers.empty())
        return false;
    handler = mHandlers.top();
    mHandlers.pop();
    return true;
}

int PathField::unreact()
{
    Handler handler;
    handler.type = Handler::InvisibleButton;
    handler.data = 3;
    mHandlers.push(handler);
    handler.data = 4;
    mHandlers.push(handler);
    handler.data = 5;
    mHandlers.push(handler);
    handler.data = 6;
    mHandlers.push(handler);
	handler.data = 7;
	mHandlers.push(handler);
	handler.data = 8;
	mHandlers.push(handler);
	handler.data = 9;
	mHandlers.push(handler);
	handler.data = 10;
	mHandlers.push(handler);
	return 0;
}

int PathField::react()
{
    Handler handler;
    handler.type = Handler::InvisibleButton;
    handler.data = 3;
    mHandlers.push(handler);
    handler.data = 4;
    mHandlers.push(handler);
    handler.data = 5;
    mHandlers.push(handler);
    handler.data = 6;
    mHandlers.push(handler);
	handler.data = 7;
	mHandlers.push(handler);
	handler.data = 8;
	mHandlers.push(handler);
	handler.data = 9;
	mHandlers.push(handler);
	handler.data = 10;
	mHandlers.push(handler);
	return 0;
}

bool PathField::update(float& time)
{
	if(mUpdate){
		mUpdate = false;
		return true;
	}
	return false;
}

sf::Drawable* PathField::drawing()
{
	return mSprite;
}
