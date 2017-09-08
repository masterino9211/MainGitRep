#include "Map.h"
#include <string>

#include "Layout.h"
#include "Wave.h"
#include "Menu.h"
#include "Tower.h"

Map::Map(string filePath, const RenderWindow* window)
    : cWindow(window)
	, cFilePath(filePath)
    , mLayout(nullptr)
    , mMenu(nullptr)
    , mHandlers()
    , mWaveIndex(-1)
    , mPlaying(false)
    , mFirePrice(100)
    , mWaterPrice(100)
    , mEarthPrice(100)
    , mAirPrice(100)
    , mMoney(400)
    , mFont(nullptr)
	, mLives(20)
	, mLivesText()
    , mUpdate(true)
    , mMoneyText(nullptr)
    , mCurrentDisplay(nullptr)
{
    xml_document doc;
    doc.load_file(filePath.c_str());
    xml_node map = doc.first_child();
    xml_node layout = map.child("layout");
    mLayout = new Layout(layout, window);
    mMenu = new Menu("media/menu/SideMenu.xml", cWindow);
    xml_node waves = map.child("waves");
    for(xml_node_iterator i = waves.begin(); i != waves.end(); i++) {
        mWaves.push_back(new Wave(*i, dynamic_cast<const Layout*>(mLayout)));
    }
    mCurrent = nullptr;
    mLayout->setWave(mCurrent);
    mFont = new Font();
    mFont->loadFromFile("media/menu/akaDylanPlain.ttf");
    mMoneyText = new Text;
    mMoneyText->setCharacterSize(16);
    mMoneyText->setFont(*mFont);
    mMoneyText->setPosition(610, 60);
    mMoneyText->setString("MONEY:" + to_string((int)mMoney) + "$");
    mMoneyText->setColor(Color::Black);
    mCreepsLeftText.setCharacterSize(16);
    mCreepsLeftText.setColor(Color::Black);
    mCreepsLeftText.setPosition(610, 120);
    mCreepsLeftText.setFont(*mFont);
	
	
    mLivesText = new Text;
    mLivesText->setCharacterSize(16);
    mLivesText->setFont(*mFont);
    mLivesText->setPosition(610, 90);
    mLivesText->setString("LIVES:" + to_string(mLives));
    mLivesText->setColor(Color::Black);
	
}

Map::~Map()
{
    delete mLayout;
    for(auto i : mWaves) {
        delete i;
    }
    delete mFont;
    delete mMoneyText;
	delete mLivesText;
}


std::vector< Drawable* > Map::drawables()
{
    vector<Drawable*> buffer = mLayout->drawables();
    vector<Drawable*> menuBuffer = mMenu->drawables();
    vector<Drawable*> waveBuffer;
    if(mPlaying)
        waveBuffer = mCurrent->drawables();
    buffer.insert(buffer.end(), waveBuffer.begin(), waveBuffer.end());
    buffer.insert(buffer.end(), menuBuffer.begin(), menuBuffer.end());
    if(mCurrentDisplay != nullptr) {
        vector<Drawable*> displaybuffer = mCurrentDisplay->drawables();
        buffer.insert(buffer.end(), displaybuffer.begin(), displaybuffer.end());
    }
    buffer.push_back(mMoneyText);
    buffer.push_back(&mCreepsLeftText);
	buffer.push_back(mLivesText);
    return buffer;
}

void Map::handle(Event& event)
{
    Handler handler;
    switch(event.type) {
    case Event::Closed:
        handler.type = Handler::Closed;
        mHandlers.push(handler);
        break;
    case Event::MouseButtonReleased:
        if(event.mouseButton.x <= 600 && event.mouseButton.y <= 600) {
            mLayout->handle(event);
        } else {
            mMenu->handle(event);
        }
        break;
    case Event::KeyReleased:
        if(event.key.code >= sf::Keyboard::Left && event.key.code <= sf::Keyboard::Down)
            mLayout->handle(event);
        else
            mMenu->handle(event);
    default:
        break;
    }
}

void Map::init(Color& clearColor)
{
    clearColor = Color(225, 225, 225);
}

bool Map::pollHandler(Handler& handler)
{
    Handler h;
    while(mLayout->pollHandler(h)) {
        if(h.type == Handler::VisibleButton) {
            mMenu->setVisible(h.data);
        } else if(h.type == Handler::InvisibleButton) {
            mMenu->setInvisible(h.data);
        } else if(h.type == Handler::AddTower) {
            switch(h.data) {
            case Tower::Fire:
                mMoney -= mFirePrice;
                mMoneyText->setString("MONEY:" + to_string((int)mMoney) + "$");
                mFirePrice += 20;
                break;
            case Tower::Water:
                mMoney -= mWaterPrice;
                mMoneyText->setString("MONEY:" + to_string((int)mMoney) + "$");
                mWaterPrice += 20;
                break;
                break;
            case Tower::Earth:
                mMoney -= mEarthPrice;
                mMoneyText->setString("MONEY:" + to_string((int)mMoney) + "$");
                mEarthPrice += 20;
                break;
            case Tower::Air:
                mMoney -= mAirPrice;
                mMoneyText->setString("MONEY:" + to_string((int)mMoney) + "$");
                mAirPrice += 20;
                break;
                break;
            default:
                break;
            }
            mCurrentDisplay = &mUpgradeDisplay;
        } else if(h.type == Handler::SetDisplay) {
            switch(h.data) {
            case 0:
                mCurrentDisplay = nullptr;
                break;
            case 1:
                mCurrentDisplay = &mTowerDisplay;
                break;
            case 2:
                mCurrentDisplay = &mUpgradeDisplay;
            default:
                break;
            }
        } else if(h.type == Handler::Handler::TowerModified) {

            mUpgradeDisplay.updateText(*(dynamic_cast<Tower*>(h.tower)), mMoney);
        } else if(h.type == Handler::MoneySpent) {
            mMoney -= h.money;

//             mMoneyText->setString("money: " + to_string((int)mMoney));
        } else {
            mHandlers.push(h);
        }
    }
    bool dontUpdate = false;
    while(mMenu->pollHandler(h)) {
        if(h.type == Handler::AddTower) {

            switch(h.data) {
            case Tower::Fire:
                if(mMoney < mFirePrice) {
                    dontUpdate = true;
                }
                break;
            case Tower::Water:
                if(mMoney < mWaterPrice) {
                    dontUpdate = true;
                }
                break;
            case Tower::Earth:

                if(mMoney < mEarthPrice) {
                    dontUpdate = true;
                }
                break;
            case Tower::Air:
                if(mMoney < mAirPrice) {
                    dontUpdate = true;
                }
                break;
            default:
                break;
            }
            if(!dontUpdate) {
                mLayout->addTower(h.data);
                mWait = true;
            }
        } else if(h.type == Handler::ModifyTower) {
            mLayout->modifyTower(h.data, mMoney);
        } else if(h.type == Handler::SendNextWave && !mPlaying) {
            mWaveIndex++;
            mCurrent = mWaves[mWaveIndex];
            mLayout->setWave(mCurrent);
            mPlaying = true;
            Handler h1;
            h1.type = Handler::ResetLocalTime;
            mLayout->setWave(mWaves[mWaveIndex]);
            mHandlers.push(h1);
        } else {
            mHandlers.push(h);
        }
    }
    while(mPlaying && mCurrent->pollHandler(h)) {
        if(h.type == Handler::LevelOver) {
            mPlaying = false;
        }else if(h.type == Handler::Bounty){
			mMoney += h.money;
        }else if(h.type == Handler::LostLives){
			mLives -= h.data;
        }
    }

    if(mHandlers.empty())
        return false;
    handler = mHandlers.top();
    mHandlers.pop();
    return true;
}

bool Map::update(float time)
{
    int up = 0;
    up += mLayout->update(time);
    up += mMenu->update(time);
    if(mPlaying) {
        up += mCurrent->update(time);
    }

    int running, inBase;
    if(mCurrent != nullptr) {
        mCurrent->creepsLeft(running, inBase);
    } else {
        running = 0;
        inBase = 0;
    }
    int x, y;
    mMoneyText->setString("money: " + to_string((int)mMoney));
	
	if(mLives > 0){
		mLivesText->setColor(Color::Black);
	}else{
		mLives = 0;
		mLivesText->setColor(Color::Red);
		Handler handler;
		handler.type = Handler::ChangeScene;
		handler.data = SceneKey::MainMenu;
		mHandlers.push(handler);
	}
	
    mCreepsLeftText.setString("left: " + to_string(running) + "(" + to_string(inBase) + ")");
	mLivesText->setString("LIVES: " + to_string(mLives));
	
    if(mCurrentDisplay == &mTowerDisplay)
        mTowerDisplay.updateText(mFirePrice, mWaterPrice, mEarthPrice, mAirPrice, mMoney, x, y);
    else if(mCurrentDisplay == &mUpgradeDisplay)
        mUpgradeDisplay.updateText(mMoney);
    if(up == 0)
        return false;
    return up || mUpdate;
}


