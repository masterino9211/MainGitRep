#include "Game.h"
#include "Splash.h"
#include "Transitional.h"
#include "Menu.h"
#include "Map.h"



Game::Game(unsigned width, unsigned height, string title)
    : mWindow(VideoMode(width, height, 32), title, Style::Close)
    , mTimer()
    , mAudio()
    , mDrawBuffer()
    , mClearColor(Color::Black)
    , mScenes()
    , mCurrentSceneKey(SceneKey::Tr1)
{
    //positioning window.
    Vector2i position(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height);
    position.x -= width;
    position.y -= height;
    position /= 2;

    mWindow.setPosition(position);
//     mAudio.manipulate(AudioManipulator::Play);
}


Game::~Game()
{

    //releasing dynamic data members.
    for(map<int, SceneInterface *>::iterator i = mScenes.begin(); i != mScenes.end(); i++) {
        if(i->second != nullptr) {
            delete i->second;
        }
    }
}


void Game::run()
{
	init();
    loop();
}



void Game::loop()
{

    //first scene is chosen and initiated.
    mCurrent = mScenes[mCurrentSceneKey];
    mCurrent->init(mClearColor);
    //variable for storing local time.
    float local;
    //window is closed when close event is passed via sf::RenderWindow::pollEvent(sf::Event& event).
    mDrawBuffer = mCurrent->drawables();
    while(mWindow.isOpen()) {
        if(!mTimer.update(local)) {
            continue;
        }
        mWindow.clear(mClearColor);
        Event event;
        //Events are proccessed by current scene.
        while(mWindow.pollEvent(event)) {
            mCurrent->handle(event);
        }
        Handler handler;
        if(mCurrent->update(local))
            mDrawBuffer = mCurrent->drawables();
        //Handler class is equivalent to sf::Event.
        //It is proccessed in similar manner as sf::Event.
        while(mCurrent->pollHandler(handler))
            handle(handler);
        //At the end of every iteration through loop, drawings are drawn and displayed.
        draw();
        mWindow.display();
    }
}

void Game::draw()
{
	int j = 0;
	for(auto i : mDrawBuffer){
			mWindow.draw(*i);
			j++;
    }
}

void Game::init()
{
    mScenes.insert(pair<int, SceneInterface*>(SceneKey::Map1, new Map("media/maps/map.xml", dynamic_cast<const RenderWindow *>(&mWindow))));
    mScenes.insert(pair<int, SceneInterface *>(SceneKey::Tr1, new Transitional(Color::Black, Color::Black, seconds(1), SceneKey::Mad)));
    mScenes.insert(pair<int, SceneInterface *>(SceneKey::Tr2, new Transitional(Color::Black, Color::White, seconds(1), SceneKey::Matf)));
    mScenes.insert(pair<int, SceneInterface *>(SceneKey::Tr3, new Transitional(Color::White, Color(225, 225, 225), seconds(1), SceneKey::MainMenu)));
    mScenes.insert(pair<int, SceneInterface *>(SceneKey::Mad, new Splash("media/splash/MAD++ logo.png", Color::Black, seconds(4), SceneKey::Tr2)));
    mScenes.insert(pair<int, SceneInterface *>(SceneKey::Matf, new Splash("media/splash/matf logo.png", Color::White, seconds(4), SceneKey::Tr3)));
    mScenes.insert(pair<int, SceneInterface *>(SceneKey::MainMenu, new Menu("media/menu/Menu.xml", dynamic_cast<const RenderWindow *>(&mWindow))));
    mScenes.insert(pair<int, SceneInterface *>(SceneKey::Options, new Menu("media/menu/options.xml", dynamic_cast<const RenderWindow *>(&mWindow))));
    mScenes.insert(pair<int, SceneInterface*>(SceneKey::GameOptions, new Menu("media/menu/GameOptions.xml", dynamic_cast<const RenderWindow*>(&mWindow))));

}


void Game::handle(Handler &handler)
{
    SceneKey tmp;

    switch(handler.type) {
    case Handler::ChangeScene:
        mCurrent = mScenes[handler.data];
        mCurrentSceneKey = (SceneKey)handler.data;
        mCurrent->init(mClearColor);
        mDrawBuffer = mCurrent->drawables();
        mTimer.resetLocal();
        break;
    case Handler::ChangeClearColor:
        mClearColor = handler.color;
        break;
	case Handler::ResetLocalTime:
		mTimer.resetLocal();
		break;
    case Handler::Closed:
        close();
        break;
    case Handler::Destroy:
        if(handler.data == SceneKey::This) {
            delete mScenes[mCurrentSceneKey];
            mScenes.erase(mCurrentSceneKey);
        } else {
            delete mScenes[handler.data];
            mScenes[handler.data] = nullptr;
            mScenes.erase(handler.data);
        }
        break;
    case Handler::ChangeSceneAndDestroy:
        tmp = (SceneKey)handler.data;
        handler.type = Handler::Destroy;
        handler.data = SceneKey::This;
        handle(handler);
        handler.data = tmp;
        handler.type = Handler::ChangeScene;
        handle(handler);
        break;
    case Handler::Audio:
        mAudio.manipulate(handler.data);
        break;
	default:
		break;
    }

}

void Game::close()
{
    mWindow.close();
    //TODO
}


