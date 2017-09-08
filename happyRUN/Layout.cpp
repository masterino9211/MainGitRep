#include "Layout.h"
#include "EmptyField.h"
#include "WaterField.h"
#include "PathField.h"
#include "Tower.h"
#include "Wave.h"
#include "Creep.h"
Layout::Layout(pugi::xml_node& node, const sf::RenderWindow* window)
    : mHandlers()
    , EmptyTexture()
    , PathTexture()
    , WaterTexture()
    , FireTowerTexture()
    , WaterTowerTexture()
    , AirTowerTexture()
    , EarthTowerTexture()
    , mFocus(-1, -1)
    , mSource()
    , mDrain()
    , mFlagTexture1()
    , mFlagTexture2()
    , mFlag1()
    , mFlag2()
    , mRangeIndicator()
    , mMenuBackground()
    , mCurrentWave(nullptr)
	, mUpdate(true)
	, mFieldsForDeletion()
{
    EmptyTexture.loadFromFile("media/maps/empty.png");
    WaterTexture.loadFromFile("media/maps/water.png");
    PathTexture.loadFromFile("media/maps/path.png");

    FireTowerTexture.loadFromFile("media/maps/firetower.png");
    WaterTowerTexture.loadFromFile("media/maps/watertower.png");
    EarthTowerTexture.loadFromFile("media/maps/earthtower.png");
    AirTowerTexture.loadFromFile("media/maps/airtower.png");

    mMenuBackground.setFillColor(Color(225, 225, 225));
    mMenuBackground.setPosition(601, 0);
    mMenuBackground.setSize(Vector2f(199, 600));
    int i1 = 0, j1 = 0;
    for(xml_node_iterator i = node.begin(); i != node.end(); i++) {
        for(xml_node_iterator j = i->begin(); j != i->end(); j++) {
            switch(j->attribute("type").as_int()) {
            case FieldType::Empty:
                mFields[i1][j1] = new EmptyField(*j, i1, j1, EmptyTexture);
                break;
            case FieldType::Water:
                mFields[i1][j1] = new WaterField(i1, j1, WaterTexture);
                break;
            case FieldType::Path:
                mFields[i1][j1] = new PathField(i1, j1, PathTexture);
                break;
            default:
                break;
            }
            j1++;
        }
        i1++;
        j1 = 0;
    }
    sscanf(node.attribute("source").as_string(), "%i%i", &mSource.x, &mSource.y);
    sscanf(node.attribute("drain").as_string(), "%i%i", &mDrain.x, &mDrain.y);
    mFlagTexture1.loadFromFile("media/maps/flag1.png");
    mFlagTexture2.loadFromFile("media/maps/flag2.png");
    mFlag1.setTexture(mFlagTexture1);
    mFlag2.setTexture(mFlagTexture2);
    mFlag1.setPosition( mSource.y * 40, mSource.x * 40);
    mFlag2.setPosition(mDrain.y * 40, mDrain.x * 40);
    mRangeIndicator.setFillColor(Color(255, 255, 255, 30));
    mRangeIndicator.setOutlineColor(Color(0, 0, 0, 100));
    mRangeIndicator.setRadius(100);
    mRangeIndicator.setPosition(1000, 1000);
}

vector<Drawable*> Layout::drawables()
{
    vector<Drawable*> buffer;
    for(int i = 0; i < 15; i++)
        for(int j = 0; j < 15; j++) {
            buffer.push_back(mFields[i][j]->drawing());
        }
    buffer.push_back(&mFlag1);
    buffer.push_back(&mFlag2);
    buffer.push_back(&mRangeIndicator);
    buffer.push_back(&mMenuBackground);
    for(auto i : mTowers) {
        buffer.push_back(i.second->rechargeBar());
    }
    
    if(!mFieldsForDeletion.empty() && mCurrentWave != nullptr){
		mCurrentWave->updateBluePrint();
    }
    for(auto i : mFieldsForDeletion){
		delete i;
    }
    mFieldsForDeletion.clear();
    
    return buffer;
}

Layout::~Layout()
{
    for(int i = 0; i < 15; i++)
        for(int j = 0; j < 15; j++)
            delete mFields[i][j];

}


void Layout::handle(sf::Event& event)
{
    int reaction;
    Handler handler;
    switch(event.type) {
    case Event::MouseButtonReleased:
        if(event.mouseButton.button != Mouse::Left)
            break;
        if(mFocus.x != -1) {
            mFields[mFocus.x][mFocus.y]->unreact();
        }
        mFocus.x = event.mouseButton.y / 40;
        mFocus.y = event.mouseButton.x / 40;
        reaction = mFields[mFocus.x][mFocus.y]->react();
        handler.type = Handler::SetDisplay;
        handler.data = reaction;
        mHandlers.push(handler);
        break;
    case Event::KeyReleased:
        if(mFocus.x != -1) {
            mFields[mFocus.x][mFocus.y]->unreact();

        }
        switch(event.key.code) {
        case Keyboard::Up:
            if(mFocus.x > 0)
                mFocus.x--;
            break;
        case Keyboard::Down:
            if(mFocus.x < 14)
                mFocus.x++;
            break;
        case Keyboard::Left:
            if(mFocus.y > 0)
                mFocus.y--;
            break;
        case Keyboard::Right:
            if(mFocus.y < 14)
                mFocus.y++;
            break;
        default:
            break;
        }
        if(mFocus.x == -1)
            mFocus.x = 0;
        if(mFocus.y == -1)
            mFocus.y = 0;
        reaction = mFields[mFocus.x][mFocus.y]->react();
        handler.type = Handler::SetDisplay;
        handler.data = reaction;
        mHandlers.push(handler);
        break;
    default:
        break;
    }
}

void Layout::init(sf::Color& clearColor)
{

}

bool Layout::pollHandler(Handler& handler)
{
    for(int i = 0; i < 15; i++) {
        for(int j = 0; j < 15; j++) {
            Handler h;
            while(mFields[i][j]->pollHandler(h)) {
                if(h.type == Handler::RangeIndicator) {
                    mRangeIndicator.setRadius(h.rangeData[0]);
                    mRangeIndicator.setPosition(h.rangeData[1], h.rangeData[2]);
                }
                else {
                    mHandlers.push(h);
                }
            }
        }
    }
    if(mHandlers.empty())
        return false;
    handler = mHandlers.top();
    mHandlers.pop();
    return true;
}

bool Layout::update(float time)
{
	int updated = 0;
    for(int i = 0; i < 15; i++) {
        for(int j = 0; j < 15; j++) {
            updated += mFields[i][j]->update(time);
        }
    }

    for(auto i : mTowers) {
        i.second->fire(mCurrentWave);
    }
    if(mUpdate){
		mUpdate = false;
		return true;
    }
    return updated > 0;
}
BluePrint Layout::bluePrint() const
{
    BluePrint p;
    for(int i = 0; i < 15; i++) {
        for(int j = 0; j < 15; j++) {
            p[i][j].passable = mFields[i][j]->passable();
            p[i][j].visited = false;
            p[i][j].weight = -1;
        }
    }

    return p;
}

BluePrint Layout::calculate() const
{
    BluePrint p = bluePrint();

    travel(mDrain.x, mDrain.y, 0, p);
	
    return p;
}

void Layout::travel(int x, int y, int weight, BluePrint& p) const
{
    if(x >= 15 || x < 0 || y >= 15 || y < 0)
        return;
    if(!p[x][y].passable) {
        return;
    }
    if(p[x][y].visited && p[x][y].weight != -1 && p[x][y].weight <= weight) {
        return;
    }
    if(!p[x][y].visited && p[x][y].passable) {
        p[x][y].visited = true;
        p[x][y].weight = weight;
        weight++;
    }
    if(p[x][y].visited && p[x][y].weight != -1 && p[x][y].weight > weight) {
        p[x][y].weight = weight;
        weight++;
    }
    travel(x - 1, y, weight, p);
    travel(x, y - 1, weight, p);
    travel(x, y + 1, weight, p);
    travel(x + 1, y, weight, p);
}

BluePrint Layout::getBluePrint() const
{
    return calculate();
}

Vector2i Layout::getDrain() const
{
    return mDrain;
}

Vector2i Layout::getSource() const
{
    return mSource;
}

void Layout::addTower(int tower)
{

	
    if(tower != Tower::Delete) {
        BluePrint p = bluePrint();
        p[mFocus.x][mFocus.y].passable = false;
        if(!potentialBuild(p)) {
            return;
        }

        if(mCurrentWave != nullptr && !mCurrentWave->tryBluePrint(p)) {
            return;
        }
    } else {
        mTowers.erase(15 * mFocus.x + mFocus.y);
    }

    mFieldsForDeletion.push_front(mFields[mFocus.x][mFocus.y]);
	
    xml_node x;
    TowerInterface* t = nullptr;
    switch(tower) {
    case Tower::Air:
        t = new Tower(AirTowerTexture, Color::White);
        break;
    case Tower::Fire:
        t = new Tower(FireTowerTexture, Color::Red);
        break;
    case Tower::Earth:
        t = new Tower(EarthTowerTexture, Color(100, 100, 0));
        break;
    case Tower::Water:
        t = new Tower(WaterTowerTexture, Color::Blue);
        break;
    case Tower::Delete:
        mFields[mFocus.x][mFocus.y] = new EmptyField(x, mFocus.x, mFocus.y, EmptyTexture);
		mTowers.erase(mFocus.x * 15 + mFocus.y);
        break;
	default:
		break;
    }

    if(t != nullptr) {
		t->setPosition(mFocus.x, mFocus.y);
        mFields[mFocus.x][mFocus.y] = t;
        mTowers.insert(pair<int, Tower*>(15*mFocus.x + mFocus.y, dynamic_cast<Tower*>(mFields[mFocus.x][mFocus.y])));
    }
    mFields[mFocus.x][mFocus.y]->react();
    Handler handler;
    handler.type = Handler::AddTower;
    handler.data = tower;
    mHandlers.push(handler);
	mUpdate = true;
}

bool Layout::potentialBuild(BluePrint& p)
{
    for(int i = 0; i < 15; i++)
        for(int j = 0; j < 15; j++) {
            p[i][j].visited = false;
            p[i][j].weight = -1;
        }
    travel(mDrain.x, mDrain.y, 0, p);
    if(p[mSource.x][mSource.y].weight == -1)
        return false;
    return true;
}

void Layout::setWave(Wave* wave)
{
    mCurrentWave = wave;
    for(auto i : mTowers) {
        i.second->reset();
    }
}

void Layout::modifyTower(int modification, float money)
{
    mTowers[15 * mFocus.x + mFocus.y]->modify(modification, money);
}
