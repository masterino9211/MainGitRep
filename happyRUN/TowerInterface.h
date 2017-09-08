#ifndef TOWERINTERFACE_H
#define TOWERINTERFACE_H

#include "FieldInterface.h"

class Wave;

class TowerInterface : public FieldInterface
{
public:
    virtual ~TowerInterface(){};
	virtual void fire(Wave *wave) = 0;
	virtual bool isReady() = 0;
	virtual void setPosition(int x, int y) = 0;
	virtual void modify(int modification, float money) = 0;
	virtual void reset() = 0;
	virtual Drawable* rechargeBar() = 0;
	virtual void getStats(float &rate, float &range, float &powerMin, float &powerMax, float &ratePrice, float &rangePrice, float &powerPrice, float &sellPrice) = 0;
};

#endif // TOWERINTERFACE_H
