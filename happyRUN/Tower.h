#ifndef FIRETOWER_H
#define FIRETOWER_H

#include "TowerInterface.h"
#include <queue>

using namespace std;
using namespace sf;

class Creep;
class Wave;

class Tower : public TowerInterface
{
public:
	enum {
		Delete = 0, Fire = 1, Water = 2, Air = 3, Earth = 4
	};
	enum {
		IncreaseRate = 0, IncreaseRange, IncreasePower
	};
    Tower(Texture &texture, Color bulletColor);
    ~Tower();
    virtual bool isReady();
    virtual void fire(Wave *wave);
    virtual void setPosition(int x, int y);
    virtual bool passable();
    virtual void process(Handler& handler);
    virtual bool pollHandler(Handler& handler);
    virtual int unreact();
    virtual int react();
    virtual bool update(float& time);
    virtual void modify(int modification, float money);
    virtual void reset();
    virtual Drawable* rechargeBar();
    virtual sf::Drawable* drawing();
    virtual void getStats(float& rate, float& range, float& powerMin, float& powerMax, float& ratePrice, float& rangePrice, float& powerPrice, float& sellPrice);
	bool inRange(Creep* creep);
private:
	float mMinimum;
	float mMaximum;
	Color mBulletColor;
	Vector2f mPosition;
	float mRechargeTime;
	float mRange;
	float mRatePrice;
	float mRangePrice;
	float mPowerPrice;
	float mSellPrice;
	float mNextFire;
	float mCurrentTime;
	bool mUpdate;
	Texture *mTexture;
	Sprite *mSprite;
	RectangleShape *mRechargeBar;
	priority_queue<Handler> mHandlers;
};

#endif // FIRETOWER_H
