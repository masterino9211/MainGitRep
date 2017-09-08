#include "EmptyField.h"

EmptyField::EmptyField()
{

}

EmptyField::EmptyField(xml_node &node,int x, int y, Texture &texture)
    : mSprite(nullptr)
    , mHandlers()
	, mTexture(&texture)
	, mUpdate(true){
    mSprite = new Sprite;
    mSprite->setTexture(*mTexture);
	mSprite->setTextureRect(IntRect(0, 0, 40, 40));
    mSprite->setPosition(y * 40, x * 40);
}

EmptyField::~EmptyField()
{
    delete mSprite;
}

bool EmptyField::pollHandler(Handler& handler)
{
	if(mHandlers.empty())
		return false;
	handler = mHandlers.top();
	mHandlers.pop();
	return true;
}

int EmptyField::react()
{
	mSprite->setTextureRect(IntRect(40, 0, 40, 40));
	Handler handler;
	handler.type = Handler::VisibleButton;
	handler.data = 3;
	mHandlers.push(handler);
	handler.data = 4;
	mHandlers.push(handler);
	handler.data = 5;
	mHandlers.push(handler);
	handler.data = 6;
	mHandlers.push(handler);
	handler.type = Handler::InvisibleButton;
	handler.data = 7;
	mHandlers.push(handler);
	handler.data = 8;
	mHandlers.push(handler);
	handler.data = 9;
	mHandlers.push(handler);
	handler.data = 10;
	mHandlers.push(handler);
	
	return 1;
}

int EmptyField::unreact()
{
	mSprite->setTextureRect(IntRect(0, 0, 40, 40));
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

bool EmptyField::update(float& time)
{
	if(mUpdate){
		mUpdate = false;
		return true;
	}
	return false;
}

Drawable* EmptyField::drawing()
{
	return mSprite;
}

void EmptyField::process(Handler& handler)
{
	
}

bool EmptyField::passable()
{
	return true;
}
