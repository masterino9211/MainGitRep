#ifndef LAYOUT_H
#define LAYOUT_H
#include "SceneInterface.h"
#include "pugixml.hpp"
#include "FieldInterface.h"
#include "SimpleField.h"
#include "TowerInterface.h"
#include "Tower.h"
#include <queue>
#include <forward_list>

class Wave;
class Tower;
using namespace std;
using namespace sf;
using namespace pugi;

using Matrix = array< array<FieldInterface*, 15>, 15>;
using BluePrint = array< array<SimpleField, 15>, 15>;


class Layout : public NodeInterface
{
public:
    Layout(xml_node &node, const RenderWindow* window);
    virtual vector< Drawable* > drawables();
    virtual void handle(Event& event);
    virtual void init(Color& clearColor);
    virtual bool pollHandler(Handler& handler);
    virtual bool update(float time);
    virtual ~Layout();
	Vector2i getSource() const;
	Vector2i getDrain() const;
	BluePrint getBluePrint() const;
	void addTower(int tower);
	void setWave(Wave *wave);
	void modifyTower(int modification, float money);
private:
	forward_list<FieldInterface*> mFieldsForDeletion;
	bool mWait;
    BluePrint bluePrint() const;
	CircleShape mRangeIndicator;
	BluePrint calculate() const;
	bool potentialBuild(BluePrint &p);
	void travel(int x, int y, int weight, BluePrint &p) const;
    Matrix mFields;
	map<int, Tower*> mTowers;
	Wave* mCurrentWave;
    priority_queue<Handler> mHandlers;
    Texture EmptyTexture;
    Texture WaterTexture;
	Texture PathTexture;
	Texture FireTowerTexture;
	Texture WaterTowerTexture;
	Texture AirTowerTexture;
	Texture EarthTowerTexture;
    Vector2i mFocus;
    Vector2i mSource;
    Vector2i mDrain;
    Texture mFlagTexture1;
    Texture mFlagTexture2;
    Sprite mFlag1;
    Sprite mFlag2;
	RectangleShape mMenuBackground;
	bool mUpdate;
};

#endif // LAYOUT_H
