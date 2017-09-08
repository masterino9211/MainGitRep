#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "SceneInterface.h"
#include "Handler.h"
#include <queue>
#include "pugixml.hpp"
#include "DisplayInterface.h"


#include "TowerPriceDisplay.h"
#include "UpgradeDisplay.h"

using namespace std;
using namespace sf;
using namespace pugi;

class Wave;
class Layout;
class Menu;
class UpgradeDisplay;
class TowerPriceDisplay;

class Map: public SceneInterface
{
public:
    Map(string filePath, const RenderWindow* window);
    virtual vector< Drawable* > drawables();
    virtual void handle(Event& event);
    virtual void init(Color& clearColor);
    virtual bool pollHandler(Handler& handler);
    virtual bool update(float time);
    virtual ~Map();
private:
    const RenderWindow *cWindow;
	string cFilePath;
    Layout* mLayout;
	Menu *mMenu;
    vector<Wave*> mWaves;
	Wave* mCurrent;
    int mWaveIndex;
	priority_queue<Handler> mHandlers;
	bool mPlaying;
	float mMoney;
	float mFirePrice;
	float mWaterPrice;
	float mEarthPrice;
	float mAirPrice;
	int mLives;
	Text *mLivesText;
	Text *mMoneyText;
	Text mCreepsLeftText;
	Font *mFont;
	DisplayInterface *mCurrentDisplay;
	TowerPriceDisplay mTowerDisplay;
	UpgradeDisplay mUpgradeDisplay;
	bool mUpdate;
	bool mWait;
	

};

#endif // MAP_H
