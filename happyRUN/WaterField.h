#ifndef WATERFIELD_H
#define WATERFIELD_H

#include "FieldInterface.h"
#include <queue>

using namespace std;
using namespace sf;

class WaterField : public FieldInterface
{
public:
	WaterField();
    WaterField(int x, int y, Texture &texture);
    ~WaterField();
    virtual void process(Handler& handler);
    virtual bool pollHandler(Handler& handler);
    virtual int unreact();
    virtual int react();
    virtual bool update(float& time);
    virtual sf::Drawable* drawing();
    virtual bool passable();
private:
	priority_queue<Handler> mHandlers;
	Sprite *mSprite;
	Texture *mTexture;
	bool mUpdate;
	
};

#endif // WATERFIELD_H
