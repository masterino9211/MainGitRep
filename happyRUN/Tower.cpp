#include "Tower.h"

#include "Creep.h"
#include "Wave.h"
#include "Algorithm.h"
#include <ctime>

Tower::Tower(Texture& texture, Color bulletColor)
    : mTexture(&texture)
    , mSprite(nullptr)
    , mUpdate(true)
    , mRechargeTime(1.f)
    , mNextFire(0)
    , mRange(100)
    , mCurrentTime(0)
    , mBulletColor(bulletColor)
    , mMinimum(10.f)
    , mMaximum(15.f)
    , mRechargeBar(nullptr)
    , mRangePrice(50)
    , mRatePrice(50)
    , mPowerPrice(50)
    , mSellPrice(75)
{
    mSprite = new Sprite;
    mSprite->setTexture(*mTexture);
    mRechargeBar = new RectangleShape;
    mRechargeBar->setSize(Vector2f(3, 38));
    mRechargeBar->setOutlineColor(Color::Black);
    mRechargeBar->setOutlineThickness(1);
}

void Tower::setPosition(int x, int y)
{
    mSprite->setPosition(40 * y, 40 * x);
    mPosition.x = 40 * y + 20;
    mPosition.y = 40 * x + 20;
    mRechargeBar->setPosition(mPosition.x - 18, mPosition.y + 18);
}


Tower::~Tower()
{
    delete mSprite;
    delete mRechargeBar;
}


void Tower::fire(Wave* wave)
{

    if(wave == nullptr) {
        return;
    }
    vector<Creep*> creeps;
    if (mNextFire > mCurrentTime)
        return;
    for (forward_list<Creep*>::iterator i = wave->begin(); i != wave->end(); ++i) {
        if (!((*i)->isNotAliveOrPassed()) && inRange(*i)) {
            srand(time(NULL));
            float power = mMinimum + static_cast <float>(rand()) / (static_cast <float>(RAND_MAX / (mMaximum - mMinimum)));
            (*i)->hit(power);
            mNextFire += mRechargeTime;
            break;
        }
    }

}

bool Tower::passable()
{
    return false;
}

void Tower::process(Handler& handler)
{
}

bool Tower::pollHandler(Handler& handler)
{
    if (mHandlers.empty())
        return false;
    handler = mHandlers.top();
    mHandlers.pop();
    return true;
}

int Tower::unreact()
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
    handler.type = Handler::RangeIndicator;
    handler.rangeData[0] = mRange;
    handler.rangeData[1] = 1000;
    handler.rangeData[2] = 1000;
    mHandlers.push(handler);
    return 0;
}

int Tower::react()
{
    Vector2f position = mSprite->getPosition();
    mSprite->setTextureRect(IntRect(40, 0, 40, 40));
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
    handler.type = Handler::VisibleButton;
    handler.data = 7;
    mHandlers.push(handler);
    handler.data = 8;
    mHandlers.push(handler);
    handler.data = 9;
    mHandlers.push(handler);
    handler.data = 10;
    mHandlers.push(handler);
    handler.type = Handler::RangeIndicator;
    handler.rangeData[0] = mRange;
    handler.rangeData[1] = position.x + 20 - mRange;
    handler.rangeData[2] = position.y + 20 - mRange;
    mHandlers.push(handler);
    handler.type = Handler::TowerModified;
    handler.tower = this;
    mHandlers.push(handler);
    return 2;
}

bool Tower::update(float& time)
{
    float recharge = (mNextFire - mCurrentTime) / mRechargeTime;
    if(recharge <= 0 || recharge >= 1) {
        mRechargeBar->setSize(Vector2f(3, -36));
        mRechargeBar->setFillColor(Color::Green);
    } else {
        mRechargeBar->setSize(Vector2f(3, -36 *(1 - recharge)));
        mRechargeBar->setFillColor(Color((unsigned char)(255.f * recharge),(unsigned char)(255.f - 255.f * recharge), 0));
    }
    mCurrentTime = time;
    if (mUpdate) {
        mNextFire = time;
        mUpdate = false;
        return true;
    }
    return true;
}

sf::Drawable* Tower::drawing()
{
    return mSprite;
}

bool Tower::inRange(Creep* creep)
{
    return Algorithm::distance(creep->getPosition(), mPosition) <= mRange;
}

bool Tower::isReady()
{
    return true;
}

void Tower::modify(int modification, float money)
{
    float price;
    bool bought = false;
    Vector2f position = mSprite->getPosition();
    Handler handler;
    switch (modification) {
    case IncreasePower:
        if(mPowerPrice > money) {
            break;
        }
        price = mPowerPrice;
		mSellPrice += price * 0.75;
		mSellPrice = (int)(mSellPrice / 5.f) * 5;
        mMinimum *= 1.1;
        mMaximum *= 1.1;
        mPowerPrice *= 1.2;
        mPowerPrice = ((int)mPowerPrice / 5) * 5.f;
        bought = true;
        break;
    case IncreaseRange:
        if(mRangePrice > money) {
            break;
        }
        mRange += 10;
        price = mRangePrice;
		mSellPrice += price * 0.75;
		mSellPrice = (int)(mSellPrice / 5.f) * 5;
        handler.type = Handler::RangeIndicator;
        handler.rangeData[0] = mRange;
        handler.rangeData[1] = position.x + 20 - mRange;
        handler.rangeData[2] = position.y + 20 - mRange;
        mRangePrice *= 1.2;
        mRangePrice = ((int)mRangePrice / 5) * 5.f;
        mHandlers.push(handler);
        bought = true;
        break;
    case IncreaseRate:

        if(mRatePrice > money) {
            break;
        }
        price = mRatePrice;
		mSellPrice += price * 0.75;
		mSellPrice = (int)(mSellPrice / 5.f) * 5;
        mRechargeTime *= 0.95;
        mRatePrice *= 1.2;
        mRatePrice = ((int)mRatePrice / 5) * 5.f;
        bought = true;
        break;

    }
    if(bought) {
        handler.type = Handler::MoneySpent;
        handler.money = price;
        mHandlers.push(handler);
    }
}

void Tower::reset()
{
    mNextFire = 0.f;
}

Drawable* Tower::rechargeBar()
{
    return mRechargeBar;
}


void Tower::getStats(float& rate, float& range, float& powerMin, float& powerMax, float& ratePrice, float& rangePrice, float& powerPrice, float& sellPrice)
{
    rate = mRechargeTime;
    range = mRange;
    powerMin = mMinimum;
    powerMax = mMaximum;
    ratePrice = mRatePrice;
    rangePrice = mRangePrice;
    powerPrice = mPowerPrice;
    sellPrice = mSellPrice;
}

