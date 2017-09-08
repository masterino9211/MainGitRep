#ifndef CREEP_H
#define CREEP_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <array>
#include "pugixml.hpp"
#include "SimpleField.h"

// type='germ' time='1.0' speed='1.0' health='100' bounty='20' points='1000'


using std::array;
using sf::Texture;
using sf::Vector2f;
using sf::Vector2i;
using sf::Drawable;
using sf::Sprite;
using sf::Texture;
using sf::RectangleShape;
using pugi::xml_node;

class Layout;
class Bezier;

using BluePrint = array<array< SimpleField, 15> , 15>;

class Creep
{
public:

    enum Type {
        Germ,
        Illuminati,
        Swarmling,
        Devil
    };

    Creep( xml_node &node, const Layout *layout,  Vector2f position, Texture *texture);
    ~Creep();
    bool update(float time);
    Drawable* drawing();
    Drawable* healthBar();
    void updateBluePrint();
    bool tryBluePrint(BluePrint &p) const;
    bool isOut();
    Vector2f getPosition();
    int getWeight();
    bool isNotAliveOrPassed();
    void hit(float power);
	void init();
	bool hasPassed();
	bool isNotAlive();
	float getBounty();
private:
    void stops(Vector2i &field, Vector2i &next, Vector2i &next2);
    Vector2f center(Vector2i field);
    void findBezier();
    Vector2i currentField() const;
    float mRelativeTime;
    float mSpeed;
    float mTime;
    Vector2f mSize;
    Vector2f mPosition;
    Texture *mTexture;
    Sprite *mSprite;
    const Layout *cLayout;
    Bezier *mBezier;
    BluePrint mBluePrint;
    bool mStarted;
    float mHealth;
    float mCurrentHealth;
    RectangleShape mHealthBar;
    bool mAlive;
    bool mPassed;
    bool mUpdate;
    bool mOut;
	Vector2i mStop1;
	Vector2i mStop2;
	float mBounty;
};

bool creepComparison(Creep *c1, Creep *c2);

#endif // CREEP_H
