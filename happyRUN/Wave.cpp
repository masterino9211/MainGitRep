#include "Wave.h"

#include "Creep.h"
#include "Layout.h"
#include "SimpleField.h"

Wave::Wave(xml_node &node, const Layout *layout)
    : mReward()
    , mPoints()
    , mCreeps()
    , mRunningCreeps()
{
    iluminati.loadFromFile("media/maps/iluminati.png");
    germ.loadFromFile("media/maps/germ.png");
    devil.loadFromFile("media/maps/devil.png");
    swarmling.loadFromFile("media/maps/swarmling.png");

    Vector2i source = layout->getSource();
    for(xml_node_iterator i = node.begin(); i != node.end(); i++) {
        Texture *t = nullptr;
        string type = i->attribute("type").as_string();
        if(type == "germ") {
            t = &germ;
        } else if(type == "iluminati") {
            t = &iluminati;
        } else if(type == "devil") {
            t = &devil;
        } else if(type == "swarmling") {
            t = &swarmling;
        }
        mCreeps.push_front(new Creep(*i, layout, Vector2f(source.y * 40, source.x * 40), t));

    }
}

Wave::~Wave()
{
    for(auto i : mCreeps) {
        delete i;
    }
    for(auto i : mRunningCreeps) {
        delete i;
    }
}

bool Wave::pollHandler(Handler &handler)
{
    if(mHandlers.empty())
        return false;
    handler = mHandlers.top();
    mHandlers.pop();
    return true;
}

void Wave::handle(Event &event)
{

}

bool Wave::update(float time)
{
    bool updated = false;
    int i1 = 0;
    int j1 = 0;
    if(mCreeps.empty() && mRunningCreeps.empty()) {
        Handler handler;
        handler.type = Handler::LevelOver;
        mHandlers.push(handler);
        return true;
    }
    float bounty = 0.f;
    int lostLives = 0;
    forward_list<Creep*> newRunningCreeps;
    for(forward_list<Creep*>::iterator i = mRunningCreeps.begin(); i != mRunningCreeps.end(); ++i) {
        updated |= (*i)->update(time);
        if((*i)->isNotAlive()) {
			bounty += (*i)->getBounty();
            delete *i;
            updated = true;
        } else if(((*i)->hasPassed())) {
			lostLives++;
            delete *i;
            updated = true;
        } else {
            i1++;
            newRunningCreeps.push_front(*i);
        }
    }

    mRunningCreeps = newRunningCreeps;

    forward_list<Creep*> newCreeps;

    for(auto i : mCreeps) {
        updated |= i->update(time);
        if(i->isOut()) {
            i->init();
            mRunningCreeps.push_front(i);
            i1++;
        } else {
            newCreeps.push_front(i);
            j1++;
        }
    }
    mNumRunningCreeps = i1;
    mNumCreeps = j1;
    mRunningCreeps.sort(creepComparison);
    mCreeps = newCreeps;

	
	if(bounty > 0){
		Handler handler;
		handler.type = Handler::Bounty;
		handler.money = bounty;
		mHandlers.push(handler);
	}
	
	if(lostLives > 0){
		Handler handler;
		handler.type = Handler::LostLives;
		handler.data = lostLives;
		mHandlers.push(handler);
	}
	
	
    return updated;
}

vector<  Drawable *> Wave::drawables()
{
    if(mCreeps.empty() && mRunningCreeps.empty()) {
        return vector<Drawable*>();
    }
    vector<Drawable *> drawings;

    for(auto i : mRunningCreeps) {
        drawings.push_back(i->drawing());
    }

    for(auto i : mRunningCreeps) {
        drawings.push_back(i->healthBar());
    }
    return drawings;
}

void Wave::init(Color &clearColor)
{

}

void Wave::updateBluePrint()
{
    for(auto i : mRunningCreeps) {
        i->updateBluePrint();
    }
    for(auto i : mCreeps) {
        i->updateBluePrint();
    }
}

bool Wave::tryBluePrint(BluePrint& p) const
{

    int j = 0;
    for(auto i : mRunningCreeps) {
        if(!i->tryBluePrint(p))
            return false;
        j++;
    }
    return true;
}

forward_list< Creep* >::iterator Wave::begin()
{
    return mRunningCreeps.begin();
}

forward_list< Creep* >::iterator Wave::end()
{
    return mRunningCreeps.end();
}

void Wave::creepsLeft(int& running, int& inBase)
{
    running = mNumRunningCreeps;
    inBase = mNumCreeps;
}

