#ifndef EMPTYFIELD_H
#define EMPTYFIELD_H

#include "FieldInterface.h"
#include "pugixml.hpp"
#include <queue>

using pugi::xml_node;

class EmptyField : public FieldInterface
{
public:
	EmptyField();
    EmptyField(xml_node &node, int x, int y, Texture &texture);
    ~EmptyField();
    virtual bool pollHandler(Handler& handler);
    virtual int react();
    virtual bool update(float& time);
    virtual Drawable* drawing();
    virtual void process(Handler& handler);
    virtual int unreact();
    virtual bool passable();
private:
	priority_queue<Handler> mHandlers;
	Sprite *mSprite;
	Texture *mTexture;
	bool mUpdate;
};

#endif // EMPTYFIELD_H
