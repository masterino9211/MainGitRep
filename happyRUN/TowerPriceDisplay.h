#ifndef TOWERPRICEDISPLAY_H
#define TOWERPRICEDISPLAY_H

#include "DisplayInterface.h"


enum {
    EmptyDisplay = 0,
    TowerPrices = 1,
	UpgradePrices = 2
};

class TowerPriceDisplay : public DisplayInterface
{
public:
    TowerPriceDisplay();
    ~TowerPriceDisplay();
    virtual std::vector< Drawable* > drawables();
    virtual void handle(Event& event);
    virtual void init(Color& clearColor);
    virtual bool pollHandler(Handler& handler);
    virtual bool update(float time);
    void updateText(float firePrice, float waterPrice, float earthPrice, float airPrice, float money, int running, int inBase);
private:
    Text *mFirePriceText;
    Text *mWaterPriceText;
    Text *mEarthPriceText;
    Text *mAirPriceText;
    Font *mFont;
    bool mUpdate;
};

#endif // TOWERPRICEDISPLAY_H
