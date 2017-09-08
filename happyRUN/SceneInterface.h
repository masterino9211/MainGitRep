#ifndef SCENEINTERFACE_H
#define SCENEINTERFACE_H

#include <SFML/Graphics.hpp>
#include "Handler.h"

using namespace std;
using namespace sf;



/**
 * Enum that holds keys to scenes.
 */
enum SceneKey {
    Tr1,
    Mad,
    Tr2,
    Matf,
    Tr3,
    Credits,
    MainMenu,
    Options,
    PauseMenu,
    GameScene,
    ChoiceMenu,
	GameOptions,
    Map1 = 1000000,
    This
};



class NodeInterface {
public:
    virtual ~NodeInterface() {};
    /**
     * Pure virtual function.
     * Used for initiating scene data.
     * Clear color is passed by reference.
     */
    virtual void init( Color &clearColor) = 0;
    /**
     * Pure virtual function.
     * Returns vectors used for drawing in game.
     */
    virtual  vector< Drawable *> drawables() = 0;
    /**
     * Pure virtual function.
     * Updates scene in regard of time.
     */
    virtual bool update(float time) = 0;
    /**
     * Pure virtual function.
     * Event is passed from game class and proccessed in scene.
     */
    virtual void handle( Event &event) = 0;
    /**
     * Pure virtual function.
     * if there is handler that should be passed to game, returns true.
     * Handlers should be put to priority queue.
     */
    virtual bool pollHandler(Handler &handler) = 0;
};

/**
 * Interface for scenes.
 * There is no difference between SceneInterface and NodeInteface.
 * Only reason for separated classes is to force mWindow in Game class to display
 * only Scenes, otherwise, it would be possible make button be scene for itself.
 */
class SceneInterface : public NodeInterface {
public:
    virtual ~SceneInterface() {};
//     virtual void init( Color &clearColor) = 0;
//     virtual  vector< Drawable *> drawables() = 0;
//     virtual bool update(float time) = 0;
//     virtual void handle( Event &event) = 0;
//     virtual bool pollHandler(Handler &handler) = 0;
};

#endif // SCENEINTERFACE_H
