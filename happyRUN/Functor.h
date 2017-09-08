#ifndef FUNCTOR_H
#define FUNCTOR_H

#include "Handler.h"

class Functor
{
public:
    virtual ~Functor() {};
    virtual Handler operator()() = 0;
};

class Quit : public Functor
{
public:
    virtual Handler operator()();
};

class ChangeScene : public Functor
{
public:
    ChangeScene(int key);
    virtual Handler operator()();
private:
    int mKey;
};
class AudioFunctor: public Functor
{
public:
    AudioFunctor(int data);
    virtual Handler operator()();
private:
    int mData;
};

class DisableFunctor: public Functor
{
public:
    DisableFunctor(int data);
    virtual Handler operator()();
private:
    int mData;
};

class EnableFunctor: public Functor
{
public:
    EnableFunctor(int data);
    virtual Handler operator()();
private:
    int mData;
};

class VisibleFunctor: public Functor
{
public:
    VisibleFunctor(int data);
    virtual Handler operator()();
private:
    int mData;
};

class InvisibleFunctor: public Functor
{
public:
    InvisibleFunctor(int data);
    virtual Handler operator()();
private:
    int mData;
};

class TowerFunctor: public Functor
{
public:
    TowerFunctor(int tower);
    virtual Handler operator()();
private:
    int mData;
};

class ModificationFunctor: public Functor
{
public:
    ModificationFunctor(int modification);
    virtual Handler operator()();
private:
    int mData;
};

class SendNextWaveFunctor: public Functor
{
public:
    SendNextWaveFunctor();
    virtual Handler operator()();

};

#endif // FUNCTOR_H
