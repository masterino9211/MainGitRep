#ifndef UPGRADEDISPLAY_H
#define UPGRADEDISPLAY_H

#include <string>
#include "DisplayInterface.h"
#include "TowerInterface.h"
#include "Tower.h"

using namespace std;


class UpgradeDisplay : public DisplayInterface
{
public:
    UpgradeDisplay();
    ~UpgradeDisplay();
    virtual std::vector< Drawable* > drawables();
    virtual void handle(Event& event);
    virtual void init(Color& clearColor);
    virtual bool pollHandler(Handler& handler);
    virtual bool update(float time);
	void updateText(Tower &tower, float money);
	void updateText(float money);
private:
	Tower *mTower;
	Text *mRangePriceText;
	Text *mRatePriceText;
	Text *mPowerPriceText;
	Text *mSellText;
	Text *mRangeText;
	Text *mRateText;
	Text *mPowerText;
	Font *mFont;
};

#endif // UPGRADEDISPLAY_H
