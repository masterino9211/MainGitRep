#include "WaterField.h"

WaterField::WaterField(){
	
}

WaterField::WaterField(int x, int y, Texture &texture)
    : mSprite(nullptr)
    , mHandlers()
    , mTexture(&texture)
	, mUpdate(true)
{
    mSprite = new Sprite;
    mSprite->setTexture(*mTexture);
    mSprite->setPosition(y * 40, x * 40);
}

WaterField::~WaterField()
{
    delete mSprite;
}

void WaterField::process(Handler& handler)
{

}

bool WaterField::pollHandler(Handler& handler)
{
    if(mHandlers.empty())
        return false;
    handler = mHandlers.top();
    mHandlers.pop();
    return true;
}

int WaterField::unreact()
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

int WaterField::react()
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

bool WaterField::update(float& time)
{
	if(mUpdate){
		mUpdate = false;
		return true;
	}
	return false;
}

sf::Drawable* WaterField::drawing()
{
	return mSprite;
}

bool WaterField::passable()
{
	return false;
}
