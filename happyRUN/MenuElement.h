#ifndef MENUELEMENT_H
#define MENUELEMENT_H

#include "SceneInterface.h"
#include "pugixml.hpp"
#include <queue>
#include <vector>

#define FONT 64
class Functor;
class Handler;
using namespace std;
using namespace sf;
using namespace pugi;




class MenuElement : public NodeInterface
{
public:

    enum MenuType {
        Wide,
        Icon,
        WideIcon
    };

    MenuElement(xml_node& node, Font& font,  const RenderWindow* window);
    ~MenuElement();
    virtual bool pollHandler(Handler& handler);
    virtual void handle(Event& event);
    virtual bool update(float time);
    virtual  vector<Drawable*> drawables();
    virtual void init(Color& clearColor);
    void setDisabled(bool disabled);
    bool isDisabled();
    void setVisible(bool visible);
    void tryKey(Keyboard::Key key);
private:
    void setCustoms(xml_node& node, Font* font);
    void setActions(xml_node& node);
    void setSideEffects(xml_node& node);
    int mCustom;
    vector<Functor*> mActions;
    const RenderWindow* cWindow;
    bool mUpdate;
    bool mVisible;
    int mNextScene;
    string mContent;
    RectangleShape mArea;
    Color mNormal;
    Color mFocus;
    Color mDisabledColor;
    Color mOutlineColor;
    Color mTextColor;
    unsigned int mOutlineThickness;
    bool mDisabled;
    Font* mFont;
    int mCharacterSize;
    Vector2f mPosition;
    Vector2f mSize;
    MenuType mType;
    Texture* mIconTexture;
    Sprite* mIcon;
    Text* mText;
    priority_queue<Handler> mHandlers;
    Keyboard::Key mKey;
};

#endif // MENUELEMENT_H
