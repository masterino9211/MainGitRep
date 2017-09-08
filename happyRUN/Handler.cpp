#include "Handler.h"

Handler::Handler()
{

}

Handler::Handler(const Handler &handler)
{
    *this = handler;
}

Handler& Handler::operator=(const Handler &handler)
{
    type = handler.type;
    switch(type) {
    case ChangeClearColor:
        color = handler.color;
        break;
	case RangeIndicator:
		rangeData[0] = handler.rangeData[0];
		rangeData[1] = handler.rangeData[1];
		rangeData[2] = handler.rangeData[2];
		break;
	case TowerModified:
		tower = handler.tower;
		break;
	case MoneySpent:
	case Bounty:
		money = handler.money;
		break;
    default:
        data = handler.data;
        break;
    }
    return *this;
}

Handler::~Handler()
{

}


bool operator< (const Handler h1, const Handler h2)
{
    return h1.type < h2.type;
}
