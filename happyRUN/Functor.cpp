#include "Functor.h"

Handler Quit::operator()()
{
    Handler handler;
    handler.type = Handler::Closed;
    return handler;
}

ChangeScene::ChangeScene(int key)
    :mKey(key)
{
}


Handler ChangeScene::operator()()
{
    Handler handler;
    handler.type = Handler::ChangeScene;
    handler.data = mKey;
    return handler;
}
AudioFunctor::AudioFunctor(int data)
    :mData(data)
{

}
Handler AudioFunctor::operator()()
{
    Handler handler;
    handler.type = Handler::Audio;
    handler.data = mData;
    return handler;

}

DisableFunctor::DisableFunctor(int data)
    : mData(data)
{

}

Handler DisableFunctor::operator()()
{
    Handler handler;
    handler.type = Handler::DisableButton;
    handler.data = mData;
    return handler;
}

EnableFunctor::EnableFunctor(int data)
    : mData(data)
{

}

Handler EnableFunctor::operator()()
{
    Handler handler;
    handler.type = Handler::EnableButton;
    handler.data = mData;
    return handler;
}

InvisibleFunctor::InvisibleFunctor(int data)
    : mData(data)
{

}

Handler InvisibleFunctor::operator()()
{

    Handler handler;
    handler.type = Handler::InvisibleButton;
    handler.data = mData;
    return handler;
}

Handler VisibleFunctor::operator()()

{

    Handler handler;
    handler.type = Handler::VisibleButton;
    handler.data = mData;
    return handler;
}

VisibleFunctor::VisibleFunctor(int data)
    : mData(data)
{
}

Handler TowerFunctor::operator()()
{
    Handler handler;
    handler.type = Handler::AddTower;
    handler.data = mData;
    return handler;
}

TowerFunctor::TowerFunctor(int tower)
    : mData(tower)
{
}

ModificationFunctor::ModificationFunctor(int modification)
    : mData(modification)
{
}

Handler ModificationFunctor::operator()()
{
    Handler handler;
    handler.type = Handler::ModifyTower;
    handler.data = mData;
    return handler;
}

SendNextWaveFunctor::SendNextWaveFunctor()
{

}

Handler SendNextWaveFunctor::operator()()
{
    Handler handler;
    handler.type = Handler::SendNextWave;
    return handler;
}