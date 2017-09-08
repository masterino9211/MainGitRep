#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <map>
#include "Timer.h"
#include "AudioPlayer.h"
#include "SceneInterface.h"
#include <string>


using namespace sf;
using namespace std;

/**
 * Main class of game.
 */
class Game {
public:
    /**
     * Game class constructor.
     * Default values are width = 800, height = 600, title = "happyRUN".
     */
    Game(unsigned width = 800, unsigned height = 600,  string title = "happyRUN");
    /**
     * Destructor
     */
    ~Game();
    /**
     * Central method for running game.
     */
    void run();
protected:
private:
    /**
     * Handling output of scenes.
     */
    void handle(Handler &handler);
    /*
     * Drawing sf::Drawables passed by scenes.
     */
    void draw();
    /*
     * Scenes data initialization.
     */
    void init();
    /*
     * Most of program goes here.
     */
    void loop();
    /*
     * Saves data if there is something to save, then closes window, afterward destructor is called.
     */
    void close();
    RenderWindow mWindow; /**< RenderWindow member. Everything is drawn here.*/
    Timer mTimer; /**< Timer member. All synchronizing is done by this timer*/
    AudioPlayer mAudio; /**< Only playing music. Sound effects are handled by scenes */
    map<int, SceneInterface *> mScenes; /**< All scenes are stored here */
    SceneInterface *mCurrent; /**< Pointer to currently showed scene*/
    SceneKey mCurrentSceneKey;
    vector< Drawable *> mDrawBuffer; /**< sf::Drawables  used in draw*/
    Color mClearColor; /**< Clear color for current scene*/


};

#endif
