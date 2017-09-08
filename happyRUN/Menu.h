#ifndef MENU_H
#define MENU_H

#include <queue>
#include "SceneInterface.h"
#include "MenuElement.h"


using namespace std;
using namespace sf;


typedef map<int, MenuElement*> ElementMap;
typedef pair<int, MenuElement*> ElementPair;

class Menu : public SceneInterface
{
public:
    Menu(string filePath, const RenderWindow* window);
    ~Menu();
    virtual bool pollHandler(Handler& handler);
    virtual void handle( Event& event);
    virtual bool update(float time);
    virtual  vector<  Drawable*> drawables();
    virtual void init( Color& clearColor);
	void setVisible(int id);
	void setInvisible(int id);
private:
	ElementMap mElements;
    Color mBackground;
    Font mFont;
    priority_queue<Handler> mHandlers;
};

#endif // MENU_H
