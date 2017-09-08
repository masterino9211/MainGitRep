#ifndef PATHFIELD_H
#define PATHFIELD_H

#include "FieldInterface.h"
#include <queue>

using namespace std;
using namespace sf;

class PathField : public FieldInterface
{
public:
    PathField(int x, int y, Texture& texture);
    ~PathField();
    virtual bool passable();
    virtual void process(Handler& handler);
    virtual bool pollHandler(Handler& handler);
    virtual int unreact();
    virtual int react();
    virtual bool update(float& time);
    virtual sf::Drawable* drawing();
private:
	Sprite *mSprite;
	Texture *mTexture;
	priority_queue<Handler> mHandlers;
	bool mUpdate;
};

#endif // PATHFIELD_H
