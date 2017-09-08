#ifndef TRANSITIONAL_H
#define TRANSITIONAL_H

#include <SFML/Graphics.hpp>
#include <queue>
#include <vector>
#include "SceneInterface.h"
#include "Handler.h"
/**
 * Transitional class.
 * Can be used between two scenes, if there must be pause between two scenes,
 * or if scenes have different background colors.
 */
class Transitional :  public SceneInterface {
public:
    /**
     * Constructor
     */
    Transitional( Color start,  Color end,  Time time, int next);
    //Methods from SceneInterface
    virtual  vector<  Drawable * > drawables();
    virtual void handle( Event &event);
    virtual void init( Color &clearColor);
    virtual bool pollHandler(Handler &handler);
    virtual bool update(float time);
private:
    const  Color cStart; /**< Starting color.*/
    const  Color cEnd; /**< Ending color*/
    const float cTime; /**< Time in which transition is made.*/
    const int cNext; /**< Key for next scene.*/
    //Color components are handled separatly (as floats).
    const float r; /**< Red component of current color*/
    const float g; /**< Green component of current color*/
    const float b; /**< Blue component of current color*/
    const float a; /**< Opacity component of current color*/
    Color mCurrent; /**< Current background color.*/
    priority_queue<Handler> mHandlers; /**< Priority queue holding handlers.*/
};

#endif // TRANSITIONAL_H
