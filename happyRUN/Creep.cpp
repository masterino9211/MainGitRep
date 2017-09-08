#include "Creep.h"



#include "Algorithm.h"
#include "Bezier.h"
#include "Layout.h"
#include "SimpleField.h"
// type='germ' time='1.0' speed='1.0' health='100' bounty='20' points='1000'

Creep::Creep(xml_node& node, const Layout* layout, Vector2f position, Texture* texture)
    : mTexture(texture)
    , mSprite(nullptr)
    , mPosition(position)
    , cLayout(layout)
    , mBezier(nullptr)
    , mStarted(false)
    , mHealth(0)
    , mHealthBar()
    , mAlive(true)
    , mUpdate(true)
    , mPassed(false)
    , mOut(false)
    , mStop1(-1, -1)
    , mStop2(-1, -1)
	, mBounty()
{
    string type = node.attribute("type").as_string();
    mSprite = new Sprite;
    if(type == "swarmling") {
        mSize = Vector2f(10, 10);
    } else {
        mSize = Vector2f(20, 20);
    }
    mPosition.x += 20;
    mPosition.y += 20;
    mSprite->setTexture(*mTexture);
    mSprite->setPosition(mPosition);
    mSprite->setOrigin(mSize.x / 2, mSize.y / 2);
    mSpeed = node.attribute("speed").as_float();
    mBluePrint = cLayout->getBluePrint();
    mHealth = node.attribute("health").as_float();
    mTime = node.attribute("time").as_float();
    mCurrentHealth = mHealth;
    mHealthBar.setSize(Vector2f(10, 3));
    mHealthBar.setFillColor(Color::Green);
    mHealthBar.setOutlineColor(Color::Black);
    mHealthBar.setOutlineThickness(1);
	
	mBounty = node.attribute("bounty").as_float();
}

Drawable* Creep::drawing()
{
    return mSprite;
}

bool Creep::update(float time)
{
    if(time >= mTime) {
        mOut = true;
    } else {
        return false;
    }
    mPosition.x = round(mPosition.x);
    mPosition.y = round(mPosition.y);
    float health = mCurrentHealth / mHealth;
    mHealthBar.setSize(Vector2f(10.f * health, 3));
    mHealthBar.setFillColor(Color((unsigned char)(255.f * (1 - health)), (unsigned char)(255.f * health), 0));
    if(!mStarted) {
        mRelativeTime = time;
        if(mBezier != nullptr)
            delete mBezier;
        findBezier();
        mStarted = true;
        Vector2i field = currentField();
        if(mBluePrint[field.x][field.y].weight == 0) {
            mSprite->setPosition(1000, 1000);
            mHealthBar.setPosition(1000, 1000);
            mPassed = true;
        }
        return true;
    }
    float arg = time - mRelativeTime;
    arg *= mSpeed;
    mPosition = mBezier->position(arg);
    mSprite->setRotation(0);
    mSprite->setPosition(mPosition);
    mHealthBar.setPosition(mPosition.x - 5.f, mPosition.y - 15.f);
    mSprite->setRotation(mBezier->angle(arg));
    if(mCurrentHealth <= 0) {
        mAlive = false;
        mSprite->setPosition(1000, 1000);
        mHealthBar.setPosition(1000, 1000);
    }


    if(arg >= 0.6) {
        mStarted = false;
    }
    if(mUpdate) {
        mUpdate = false;
        return true;
    }
    if(mAlive)
        return true;

    return false;
}

Creep::~Creep()
{
    if(mBezier != nullptr)
        delete mBezier;
    delete mSprite;
}

Vector2i Creep::currentField() const
{
    Vector2i ret;
    ret.x = mPosition.y / 40;
    ret.y = mPosition.x / 40;
    return ret;
}
void Creep::findBezier()
{
    Vector2i field = currentField();
    stops(field, mStop1, mStop2);
    if(field.x - mStop2.x == 0 || field.y - mStop2.y == 0) {
        mStop2.x = -1;
        mBezier = new Bezier(mPosition, center(mStop1));
    } else {
        mBezier = new Bezier(mPosition, center(mStop1), center(mStop2));
    }
}

Vector2f Creep::center(Vector2i field)
{
    Vector2f f;
    f.x = field.y * 40;
    f.y = field.x * 40;
    f.x += 20;
    f.y += 20;
    return f;
}


void Creep::stops(Vector2i& field, Vector2i& next, Vector2i& next2)
{

//     field = currentField();
//     array<Vector2i, 9> neighbours;
//     for(int i = 0; i < 8; i++)
//         neighbours[i] = field;
// 
// 
//     neighbours[0].x -=2;
//     neighbours[1].x -= 1;
//     neighbours[1].y -= 1;
//     neighbours[2].y -=2;
//     neighbours[3].x -= 1;
//     neighbours[3].y += 1;
//     neighbours[4].x +=2;
//     neighbours[5].x += 1;
//     neighbours[5].y += 1;
//     neighbours[6].y +=2;
//     neighbours[7].x += 1;
//     neighbours[7].y -= 1;
//     neighbours[8] = field;
//     int min = 8;
//     for(int i = 0; i < 8; i++) {
// 		if(neighbours[i].x < 0 || neighbours[i].x > 14 || neighbours[i].y < 0 || neighbours[i].y > 14)
// 			continue;
//         if(mBluePrint[neighbours[i].x][neighbours[i].y].weight != -1 &&
//                 mBluePrint[neighbours[i].x][neighbours[i].y].weight < mBluePrint[neighbours[min].x][neighbours[min].y].weight )
//             min = i;
//     }
// 
//     next2 = neighbours[min];
// 
//     next.x = (field.x + next2.x) / 2;
//     next.y = (field.y + next2.y) / 2;
//     

    
    field = currentField();
    Vector2i left, right, up, down;
    left = right = up = down = field;
    left.y--;
    right.y++;
    up.x--;
    down.x++;

    if(left.y < 0 || !mBluePrint[left.x][left.y].passable)
        left = Vector2i(-1, -1);
    if(right.y > 14 || !mBluePrint[right.x][right.y].passable)
        right = Vector2i(-1, -1);
    if(up.x < 0 || !mBluePrint[up.x][up.y].passable)
        up = Vector2i(-1, -1);
    if(down.x > 14 || !mBluePrint[down.x][down.y].passable)
        down = Vector2i(-1, -1);

    next = field;
    if(left.y != -1 && mBluePrint[left.x][left.y] < mBluePrint[next.x][next.y])
        next = left;
    if(up.y != -1 && mBluePrint[up.x][up.y] < mBluePrint[next.x][next.y])
        next = up;
    if(right.y != -1 && mBluePrint[right.x][right.y] < mBluePrint[next.x][next.y])
        next = right;
    if(down.y != -1 && mBluePrint[down.x][down.y] < mBluePrint[next.x][next.y])
        next = down;


    left = right = up = down = next;
    next2 = next;
    left.y--;
    right.y++;
    up.x--;
    down.y--;

    if(left.y < 0 || !mBluePrint[left.x][left.y].passable)
        left = Vector2i(-1, -1);
    if(right.y > 14 || !mBluePrint[right.x][right.y].passable)
        right = Vector2i(-1, -1);
    if(up.x < 0 || !mBluePrint[up.x][up.y].passable)
        up = Vector2i(-1, -1);
    if(down.x > 14 || !mBluePrint[down.x][down.y].passable)
        down = Vector2i(-1, -1);


    if(left.y != -1 && mBluePrint[left.x][left.y] < mBluePrint[next2.x][next2.y])
        next2 = left;
    if(up.y != -1 && mBluePrint[up.x][up.y] < mBluePrint[next2.x][next2.y])
        next2 = up;
    if(right.y != -1 && mBluePrint[right.x][right.y] < mBluePrint[next2.x][next2.y])
        next2 = right;
    if(down.y != -1 && mBluePrint[down.x][down.y] < mBluePrint[next2.x][next2.y])
        next2 = down;


}

Drawable* Creep::healthBar()
{
    return &mHealthBar;
}

void Creep::updateBluePrint()
{
    mBluePrint = cLayout->getBluePrint();
    mRelativeTime = mTime;
// 	if(mBezier != nullptr)
// 		delete mBezier;
//     findBezier();
}

bool Creep::tryBluePrint(BluePrint& p) const
{
    Vector2i position = currentField();
    if(p[position.x][position.y].weight == -1 ||
            p[mStop1.x][mStop1.y].weight == -1 || (mStop2.x != -1 && p[mStop2.x][mStop2.y].weight != -1))
        return false;
    return true;
}

bool Creep::isOut()
{
    return mOut;
}

Vector2f Creep::getPosition()
{
    return mPosition;
}

int Creep::getWeight()
{
    Vector2i position;
    return mBluePrint[position.x][position.y].weight;
}



bool Creep::isNotAliveOrPassed()
{
    return !mAlive || mPassed;
}

bool creepComparison(Creep* c1, Creep* c2)
{
    return c2->getWeight() < c1->getWeight();
}


void Creep::hit(float power)
{
    if(!mAlive)
        return;
    mCurrentHealth -= power;
}

void Creep::init()
{
}

bool Creep::hasPassed()
{
	return mPassed;
}

bool Creep::isNotAlive()
{
	return !mAlive;
}

float Creep::getBounty()
{
	return mBounty;
}

