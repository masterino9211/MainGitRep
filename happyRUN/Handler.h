#ifndef HANDLER_H
#define HANDLER_H

#include <SFML/Graphics.hpp>

class Creep;
class TowerInterface;

using namespace std;
using namespace sf;

/**
 * Class based on sf::Event.
 * Similary to sf::Event, it has only public members, and no methods, except for operator <.
 * All data is stored in union.
 * It is dangerous to access data in union if it is not initialized.
 */
class Handler {
public:
    Handler();
    Handler& operator= (const Handler& handler);

    Handler(const Handler& handler);

    ~Handler();
    /**
     * Enum that holds handler types.
     * Values are based on priority which should be used in priority queue.
     */
    enum HandlerType {
        ChangeSceneAndDestroy = 1000, /**< Destroys current scene, then changes to next.*/
        Closed = 999, /**< Window is closed.*/
        ChangeScene = 998, /**< Changes to next Scene.*/
        Destroy = 800, /**< Destroys scene passed in data*/
        ChangeClearColor = 700, /**< Changes color of background*/
        Audio = 600,
        DisableButton = 900,
        EnableButton = 901,
        VisibleButton = 902,
        InvisibleButton = 903,
		AddTower = 850,
		ModifyTower = 501,
		SendNextWave = 502,
		RangeIndicator = 400,
		AddBullet = 499,
		ResetLocalTime = 900,
		LevelOver = 899,
		SetDisplay = 300,
		TowerModified = 301,
		MoneySpent = 302,
		LostLives = 303,
		Bounty = 304

    };
    HandlerType type; /**< Type of handler.*/
    union {
        int data; /**< Member for passing intergers.*/
        float money;
        Color color; /**< Member for passing colors.*/
        float rangeData[3];
		TowerInterface* tower;
    };
};
/**
 * Operator used for priority queue.
 */
bool operator< (const Handler h1, const Handler h2);

#endif // HANDLER_H
