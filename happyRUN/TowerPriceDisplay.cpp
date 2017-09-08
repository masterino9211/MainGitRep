#include "TowerPriceDisplay.h"


TowerPriceDisplay::TowerPriceDisplay()
    : mFirePriceText(nullptr)
    , mWaterPriceText(nullptr)
    , mEarthPriceText(nullptr)
    , mAirPriceText(nullptr)
    , mFont(nullptr)
    , mUpdate(true)
{
    mFirePriceText = new Text;
    mWaterPriceText = new Text;
    mEarthPriceText = new Text;
    mAirPriceText = new Text;
    mFont = new Font;
    mFont->loadFromFile("media/menu/akaDylanPlain.ttf");
    mFirePriceText->setFont(*mFont);
    mWaterPriceText->setFont(*mFont);
    mEarthPriceText->setFont(*mFont);
    mAirPriceText->setFont(*mFont);
    mFirePriceText->setCharacterSize(12);
    mWaterPriceText->setCharacterSize(12);
    mEarthPriceText->setCharacterSize(12);
    mAirPriceText->setCharacterSize(12);
}

TowerPriceDisplay::~TowerPriceDisplay()
{
    delete mAirPriceText;
    delete mFirePriceText;
    delete mWaterPriceText;
    delete mEarthPriceText;
    delete mFont;
}



std::vector< Drawable* > TowerPriceDisplay::drawables()
{
    vector<Drawable*> buffer;
    buffer.push_back(mAirPriceText);
    buffer.push_back(mWaterPriceText);
    buffer.push_back(mFirePriceText);
    buffer.push_back(mEarthPriceText);
    return buffer;
}

void TowerPriceDisplay::handle(Event& event)
{

}

void TowerPriceDisplay::init(Color& clearColor)
{

}

bool TowerPriceDisplay::pollHandler(Handler& handler)
{
    return false;
}

void TowerPriceDisplay::updateText(float firePrice, float waterPrice, float earthPrice, float airPrice, float money, int running, int inBase)
{
    FloatRect bounds;
    mFirePriceText->setString(to_string((int)(firePrice)) + "$");
    mWaterPriceText->setString(to_string((int)(waterPrice)) + "$");
    mEarthPriceText->setString(to_string((int)(earthPrice)) + "$");
    mAirPriceText->setString(to_string((int)(airPrice)) + "$");
    bounds = mFirePriceText->getLocalBounds();
    mFirePriceText->setPosition(790 - bounds.width, 350 + bounds.height / 2);
    bounds = mWaterPriceText->getLocalBounds();
    mWaterPriceText->setPosition(790 - bounds.width, 400 + bounds.height / 2);
    bounds = mEarthPriceText->getLocalBounds();
    mEarthPriceText->setPosition(790 - bounds.width, 500 + bounds.height / 2);
    bounds = mAirPriceText->getLocalBounds();
    mAirPriceText->setPosition(790 - bounds.width, 450 + bounds.height / 2);

    if(money >= firePrice) {
        mFirePriceText->setColor(Color::Black);
    } else {
        mFirePriceText->setColor(Color::Red);
    }
    if(money >= waterPrice) {
        mWaterPriceText->setColor(Color::Black);
    } else {
        mWaterPriceText->setColor(Color::Red);
    }
    if(money >= earthPrice) {
        mEarthPriceText->setColor(Color::Black);
    } else {
        mEarthPriceText->setColor(Color::Red);
    }
    if(money >= airPrice) {
        mAirPriceText->setColor(Color::Black);
    } else {
        mAirPriceText->setColor(Color::Red);
    }
}



bool TowerPriceDisplay::update(float time)
{
    if(mUpdate) {
        mUpdate = false;
        return true;
    }
    return false;
}
