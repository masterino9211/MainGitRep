#include "MenuElement.h"
#include "SceneInterface.h"
#include "Handler.h"
#include "AudioPlayer.h"
#include <sstream>
#include <string>
#include "Functor.h"

MenuElement::MenuElement(xml_node &node, Font &font,  const RenderWindow *window)
    : mFont(&font)
    , mContent()
    , mArea()
    , mNormal()
    , mFocus()
    , mDisabledColor()
    , mPosition()
    , mSize()
    , mOutlineColor(Color::Black)
    , mOutlineThickness(1)
    , mIcon(nullptr)
    , mIconTexture(nullptr)
    , mText(nullptr)
    , mTextColor(Color::Black)
    , cWindow(window)
    , mCharacterSize(24)
    , mVisible(true)
    , mActions()
    , mUpdate(true)
    , mDisabled(false)
    , mCustom(0)
    , mKey()
{
    stringstream stream;
    string type  = node.attribute("type").as_string();
    if(type == "wide") {
        mType = Wide;
    } else if(type == "icon") {
        mType = Icon;
    } else if(type == "wide icon") {
        mType = WideIcon;
    }

    setActions(node);
    setSideEffects(node);
    setCustoms(node, mFont);
}

void MenuElement::setActions(xml_node &node)
{
    string actions = node.attribute("action").as_string();
    if(actions == "change") {
        string next = node.attribute("next").as_string();
        int nextScene;
        if(next == "choose") {
            nextScene = SceneKey::ChoiceMenu;
        } else if(next == "map1") {
            nextScene = SceneKey::Map1;
        } else if(next == "options") {
            nextScene = SceneKey::Options;
        } else if(next == "main menu") {
            nextScene = SceneKey::MainMenu;
        } else if(next == "GameOptions") {
            nextScene = SceneKey::GameOptions;
        }
        mActions.push_back(new ChangeScene(nextScene));

    } else if(actions == "quit") {
        mActions.push_back(new Quit);

    } else if(actions == "audio") {
        int manip = node.attribute("data").as_int();
        Functor *f = new AudioFunctor(manip);
        mActions.push_back(f);

    } else if (actions == "tower") {
        int tower = node.attribute("data").as_int();
        Functor *f = new TowerFunctor(tower);
        mActions.push_back(f);
    } else if (actions == "modify") {
        int modification = node.attribute("data").as_int();
        Functor *f = new ModificationFunctor(modification);
        mActions.push_back(f);
    } else if (actions == "send next wave") {
        Functor *f = new SendNextWaveFunctor();
        mActions.push_back(f);
    }



}

void MenuElement::setSideEffects(xml_node& node)
{
    int visibleCount = node.attribute("visible_count").as_int();

    stringstream str;
    str << node.attribute("visible").as_string();
    for(int i = 0; i < visibleCount; i++) {
        int visible;
        str >> visible;
        mActions.push_back(new VisibleFunctor(visible));
    }

    str.clear();

    int invisibleCount = node.attribute("invisible_count").as_int();

    str << node.attribute("invisible").as_string();
    for(int i = 0; i < invisibleCount; i++) {
        int invisible;
        str >> invisible;
        mActions.push_back(new InvisibleFunctor(invisible));
    }

}

void MenuElement::setCustoms(xml_node& node, Font *font)
{
    sscanf(node.attribute("position").as_string(), "%f%f", &mPosition.x, &mPosition.y);
    if(node.attribute("size")) {
        sscanf(node.attribute("size").as_string(), "%f%f", &mSize.x, &mSize.y);
    } else if(mType == Wide || mType == WideIcon) {
        mSize = Vector2f(200, 50);
    } else if(mType == Icon) {
        mSize = Vector2f(50, 50);
    }
    if(node.attribute("normal")) {
        sscanf(node.attribute("normal").as_string(), "%i%i%i", &mNormal.r, &mNormal.g, &mNormal.b);
    } else {
        mNormal = Color(225, 225, 225);
    }

    if(node.attribute("focus")) {
        sscanf(node.attribute("focus").as_string(), "%i%i%i", &mFocus.r, &mFocus.g, &mFocus.b);
    } else {
        mFocus = Color(245, 245, 245);
    }


    if(mType == Wide || mType == WideIcon) {
        mText = new Text;
        mText->setString(node.text().as_string());
        if(node.attribute("font")) {
            mFont = new Font;
            mFont->loadFromFile(node.attribute("font").as_string());
            mCustom += FONT;
        }
        if(node.attribute("charactersize")) {
            mCharacterSize = node.attribute("charactersize").as_int();
        } else {
            mCharacterSize = 24;
        }
        if(node.attribute("textcolor")) {
            sscanf(node.attribute("textcolor").as_string(), "%i %i %i", &mTextColor.r, &mTextColor.g, &mTextColor.b);
        } else {
            mTextColor = Color::Black;
        }
        mText->setColor(mTextColor);
        mText->setFont(*mFont);
        mText->setCharacterSize(mCharacterSize);
        mOutlineColor = Color::Black;
        mOutlineThickness = 1;
        mArea.setOutlineColor(mOutlineColor);
        mArea.setOutlineThickness(mOutlineThickness);
		
		FloatRect textBounds = mText->getLocalBounds();
		
        Vector2f textOrigin = mPosition;
        textOrigin.x += (mSize.x - textBounds.width) / 2;
        textOrigin.y += (mSize.y - textBounds.height) / 2;
        if(mType == WideIcon)
            textOrigin.x += 25;
        if(node.attribute("alignment")) {
            string alignment = node.attribute("alignment").as_string();
            if(alignment == "center") {
				;
            }else if(alignment == "left"){
				textOrigin.x = mPosition.x + 10;
				if(mType == WideIcon){
					textOrigin.x += 50;
				}
            }else if(alignment == "right"){
				textOrigin.x = mPosition.x + mSize.x - textBounds.width - 10;
            }
        }
        mText->setPosition(textOrigin);

    }
    if(mType == Icon || mType == WideIcon) {
        mIconTexture = new Texture;
        mIcon = new Sprite;
        mIconTexture->loadFromFile(node.attribute("texture").as_string());
        mIcon->setTexture(*mIconTexture);
        mIcon->setPosition(mPosition);

    }
    mArea.setFillColor(mNormal);
    mArea.setPosition(mPosition);
    mArea.setSize(mSize);

    if(node.attribute("setvisible")) {
        mVisible = node.attribute("setvisible").as_bool();
    }

    if(node.attribute("key")) {
        string code = node.attribute("key").as_string();
        if(code.length() == 1) {
            if(code[0] >= 'A' && code[0] <= 'Z') {
                mKey = (Keyboard::Key)(code[0] - 'A');
            } else if(code[0] >= '0' && code[0] <= '9') {
                mKey = (Keyboard::Key)(code[0] - '0' + 26);
            } else if(code[0] == ' ') {
                mKey = Keyboard::Space;
            }
        } else {
            if(code == "ESC") {
                mKey = Keyboard::Escape;
            } else if(code == "DELETE") {
                mKey = Keyboard::Delete;
            } else {
                mKey = Keyboard::Unknown;
            }
        }

    }

}

MenuElement::~MenuElement()
{
    if(mType == Wide || mType == WideIcon) {
        delete mText;
    }
    if(mType == WideIcon || mType == Icon) {
        delete mIcon;
        delete mIconTexture;
    }

    for(auto i : mActions) {
        delete i;
    }
    if(mCustom & FONT) {
        delete mFont;
    }
}

bool MenuElement::pollHandler(Handler &handler)
{
    if(!mHandlers.empty()) {
        handler = mHandlers.top();
        mHandlers.pop();


        return true;
    }
    return false;
}

void MenuElement::handle(Event &event)
{
    if(!mVisible || mDisabled)
        return;
    Handler handler;
    switch(event.type) {
    case Event::MouseButtonReleased:
        if(event.mouseButton.button != Mouse::Left)
            break;
        Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        if(mArea.getGlobalBounds().contains(mousePos)) {
            for(auto i : mActions) {
                mHandlers.push((*i)());
            }
        }
    }
}

bool MenuElement::update(float time)
{
    if(mDisabled) {
        mArea.setFillColor(mDisabledColor);
        return false;
    }
    Vector2i mousePos = Mouse::getPosition(*cWindow);
    if(mArea.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
        mArea.setFillColor(mFocus);

    } else {
        mArea.setFillColor(mNormal);
    }
    if(mUpdate) {
        mUpdate = false;
        return true;
    }
    return false;
}
vector<  Drawable *> MenuElement::drawables()
{
    if(!mVisible) {
        return vector<Drawable *>();
    }
    vector<Drawable *> drawBuffer;
    drawBuffer.push_back(&mArea);
    if(mType == Wide || mType == WideIcon) {
        drawBuffer.push_back(mText);
    }
    if(mType == Icon || mType == WideIcon)
        drawBuffer.push_back(mIcon);

    return drawBuffer;
}

void MenuElement::init(Color &clearColor)
{
    //nothing to do.
}

bool MenuElement::isDisabled()
{
    return mDisabled;
}

void MenuElement::setDisabled(bool disabled)
{
    if(mDisabled == disabled)
        return;
    mUpdate = true;
    mDisabled = disabled;
}

void MenuElement::setVisible(bool visible)
{
    if(mVisible == visible)
        return;
    mUpdate = true;
    mVisible = visible;
}





void MenuElement::tryKey(Keyboard::Key key)
{
    if(mVisible && key == mKey) {
        for(auto i : mActions) {
            mHandlers.push((*i)());
        }
    }
}


