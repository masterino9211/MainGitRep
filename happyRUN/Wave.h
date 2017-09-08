#ifndef WAVE_H
#define WAVE_H

#include "SceneInterface.h"
#include "pugixml.hpp"
#include <array>
#include <forward_list>
#include <queue>

using namespace std;
using namespace sf;
using namespace pugi;

class Layout;
class Creep;
class SimpleField;

using BluePrint = array< array<SimpleField, 15>, 15>;

class Wave : public NodeInterface
{
public:
    Wave(xml_node &node, const Layout *layout);
    ~Wave();
    virtual bool pollHandler(Handler& handler);
    virtual void handle( Event& event);
    virtual bool update(float time);
    virtual  vector<  Drawable*> drawables();
    virtual void init( Color& clearColor);
	void updateBluePrint();
	bool tryBluePrint(BluePrint &p) const;
	forward_list<Creep*>::iterator begin();
	forward_list<Creep*>::iterator end();
	void creepsLeft(int& running, int &inBase);
private:
	int mNumRunningCreeps;
	int mNumCreeps;
	forward_list<Creep*> mRunningCreeps;
    forward_list<Creep*> mCreeps;
    int mReward;
    double mPoints;
	Texture iluminati;
	Texture germ;
	Texture devil;
	Texture swarmling;
	priority_queue<Handler> mHandlers;
};


#endif // WAVE_H
