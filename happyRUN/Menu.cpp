#include "Menu.h"
#include "pugixml.hpp"
#include <sstream>

using namespace pugi;


Menu::Menu(string filePath,  const RenderWindow *window)
    : mElements()
    , mBackground()
    , mFont()
{

    xml_document doc;
    doc.load_file(filePath.c_str());


    xml_node menu = doc.first_child();

    mFont.loadFromFile(menu.attribute("font").as_string());
    for(xml_node_iterator i = menu.begin(); i != menu.end(); i++){
		int num = i->attribute("num").as_int();
		mElements.insert(ElementPair(num, new MenuElement(*i, mFont, window)));
    }

    stringstream stream;
    int x;
    stream << menu.attribute("background").as_string();
    stream >> x;
    mBackground.r = (unsigned char)x;
    stream >> x;
    mBackground.g = (unsigned char)x;
    stream >> x;
    mBackground.b = (unsigned char)x;
}

Menu::~Menu()
{
    for(auto i : mElements) {
        delete i.second;
    }
}

bool Menu::pollHandler(Handler &handler)
{
    Handler h;
    for(auto i : mElements) {
        while(i.second->pollHandler(h)) {
			if(h.type == Handler::VisibleButton){
				mElements[h.data]->setVisible(true);
			}else if(h.type == Handler::InvisibleButton){
				mElements[h.data]->setVisible(false);
			}else{
				mHandlers.push(h);
			}
        }
    }

    if(mHandlers.empty()) {
        return false;
    } else {
        handler = mHandlers.top();
        mHandlers.pop();
        return true;
    }

}

void Menu::handle(Event &event)
{
    Handler h;
    switch(event.type) {
    case Event::Closed:
        h.type = Handler::Closed;
        mHandlers.push(h);
        break;
    case Event::MouseButtonReleased:
        for(auto i : mElements) {
            i.second->handle(event);
        }
        break;
	case Event::KeyReleased:
		for(auto i : mElements){
			i.second->tryKey(event.key.code);
		}
		break;
	default:
		break;
    }
}

bool Menu::update(float time)
{
    int update = 0;
    for(auto i : mElements) {
        if(i.second->update(time)) {
            update++;
        }
    }

    if(update) {
        return true;
    } else {
        return false;
    }
}

vector<  Drawable *> Menu::drawables()
{
    vector<Drawable *> drawings;
    for(auto i : mElements) {
        vector<Drawable*> elementDrawings = i.second->drawables();
        drawings.insert(drawings.end(), elementDrawings.begin(), elementDrawings.end());
    }
    return drawings;
}

void Menu::init(Color &clearColor)
{
    clearColor = mBackground;
}

void Menu::setVisible(int id){
	mElements[id]->setVisible(true);
}

void Menu::setInvisible(int id)
{
	mElements[id]->setVisible(false);
}
