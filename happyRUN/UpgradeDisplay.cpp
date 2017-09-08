#include "UpgradeDisplay.h"
#include <string>

UpgradeDisplay::UpgradeDisplay()
: mRangePriceText(nullptr)
, mRangeText(nullptr)
, mRatePriceText(nullptr)
, mRateText(nullptr)
, mPowerPriceText(nullptr)
, mPowerText(nullptr)
, mSellText(nullptr)
, mFont(nullptr)
, mTower(nullptr)
{
	mFont = new Font;
	mFont->loadFromFile("media/menu/akaDylanPlain.ttf");
	mRangePriceText = new Text;
	mRangeText = new Text;
	mRatePriceText = new Text;
	mRateText = new Text;
	mPowerPriceText = new Text;
	mPowerText = new Text;
	mSellText = new Text;
	
	mRangePriceText->setFont(*mFont);
	mRangeText->setFont(*mFont);
	mRatePriceText->setFont(*mFont);
	mRateText->setFont(*mFont);
	mPowerPriceText->setFont(*mFont);
	mPowerText->setFont(*mFont);
	mSellText->setFont(*mFont);
	
	mRangePriceText->setCharacterSize(12);
	mRangeText->setCharacterSize(12);
	mRatePriceText->setCharacterSize(12);
	mRateText->setCharacterSize(12);
	mPowerPriceText->setCharacterSize(12);
	mPowerText->setCharacterSize(12);
	mSellText->setCharacterSize(12);
	
	mRangePriceText->setColor(Color::Black);
	mRangeText->setColor(Color::Black);
	mRatePriceText->setColor(Color::Black);
	mRateText->setColor(Color::Black);
	mPowerPriceText->setColor(Color::Black);
	mPowerText->setColor(Color::Black);
	mSellText->setColor(Color::Black);
	
	
	mRateText->setPosition(610, 200);
	mRangeText->setPosition(610, 250);
	mPowerText->setPosition(610, 300);
	
}

UpgradeDisplay::~UpgradeDisplay()
{
	delete mPowerPriceText;
	delete mPowerText;
	delete mRangePriceText;
	delete mRangeText;
	delete mRatePriceText;
	delete mRateText;
	delete mSellText;
	delete mFont;
}


std::vector< Drawable* > UpgradeDisplay::drawables()
{
	vector<Drawable*> buffer;
	buffer.push_back(mPowerPriceText);
	buffer.push_back(mPowerText);
	buffer.push_back(mRangePriceText);
	buffer.push_back(mRangeText);
	buffer.push_back(mRatePriceText);
	buffer.push_back(mRateText);
	buffer.push_back(mSellText);
	
	return buffer;
}


void UpgradeDisplay::handle(Event& event)
{

}

void UpgradeDisplay::init(Color& clearColor)
{

}

bool UpgradeDisplay::pollHandler(Handler& handler)
{
	return false;
}

bool UpgradeDisplay::update(float time)
{
	return false;
}


void UpgradeDisplay::updateText(Tower& tower, float money)
{
	mTower = &tower;
	printf("money %i\n", (int)money);
	FloatRect bounds;
	float rate, range, powerMin, powerMax, ratePrice, rangePrice, powerPrice, sellPrice;
	tower.getStats(rate, range, powerMin, powerMax, ratePrice, rangePrice, powerPrice, sellPrice);
	
	mRatePriceText->setString(to_string((int)ratePrice) + "$");
	mRangePriceText->setString(to_string((int)rangePrice) + "$");
	mPowerPriceText->setString(to_string((int)powerPrice) + "$");
	mSellText->setString(to_string((int)sellPrice) + "$");
	
	string rateString = to_string(rate);
	mRateText->setString("rate: " + rateString.substr(0, rateString.length() - 4));
	mRangeText->setString("range: " + to_string((int)range));
	mPowerText->setString("power: " + to_string((int)powerMin) + "-" + to_string((int)powerMax));
	
    bounds = mRatePriceText->getLocalBounds();
    mRatePriceText->setPosition(790 - bounds.width, 350 + bounds.height / 2);
    bounds = mRangePriceText->getLocalBounds();
    mRangePriceText->setPosition(790 - bounds.width, 400 + bounds.height / 2);
    bounds = mPowerPriceText->getLocalBounds();
    mPowerPriceText->setPosition(790 - bounds.width, 450 + bounds.height / 2);
    bounds = mSellText->getLocalBounds();
    mSellText->setPosition(790 - bounds.width, 500 + bounds.height / 2);

    
}

void UpgradeDisplay::updateText(float money)
{
	if(mTower != nullptr){
		updateText(*mTower, money);
	}
}
