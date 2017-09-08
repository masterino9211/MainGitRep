#ifndef SPLASH_H
#define SPLASH_H

#include <vector>
#include <queue>
#include <SFML/Graphics.hpp>
#include "SceneInterface.h"
#include "Handler.h"
/**
 * Splash class.
 * Passed image appears and disappears.
 */
class Splash :  public SceneInterface {
public:
    /**
     * Constructor.
     */
    Splash( string imagePath,  Color background,  Time time, int next);
    //functions inherited from SceneInterface.
    virtual void handle( Event &event);
    virtual  vector<  Drawable * > drawables();
    virtual void init( Color &clearColor);
    virtual bool pollHandler(Handler &handler);
    virtual bool update(float time);
protected:
private:
    Image mImage; /**< Image used in splash.*/
    const  Color cBackground; /**< Background color of screen, which is also used for hiding image.*/
    const  string cImagePath; /**< Path to the image file.*/
    const float cTime; /**< Time in which image appears and disappears.*/
    const int cNext; /**< Key for scene after this.*/
    RectangleShape mCurtain; /**< Rectangle used for hiding image*/
    vector< Sprite> mSprites; /**< Sprites that use mTextures*/
    vector< Texture> mTextures; /**< Image is split to this textures.*/
    priority_queue<Handler> mHandlers; /**< Priority queue holding handlers.*/
};

#endif // SPLASH_H
