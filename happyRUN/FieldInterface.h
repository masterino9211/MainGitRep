#ifndef FIELDINTERFACE_H
#define FIELDINTERFACE_H

#include <SFML/Graphics/Drawable.hpp>
#include "Handler.h"

using sf::Drawable;

enum FieldType{
	Empty = 0,
	Path = 1,
	Water = 2,
};

class FieldInterface
{
public:
    virtual ~FieldInterface(){}
    virtual Drawable* drawing() = 0;
	virtual bool update(float &time) = 0;
	virtual int react() = 0;
	virtual int unreact() = 0;
	virtual bool pollHandler(Handler &handler) = 0;
	virtual void process(Handler &handler) = 0;
	virtual bool passable() = 0;
};

#endif // FIELDINTERFACE_H
