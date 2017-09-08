#include "AudioPlayer.h"
#include "pugixml.hpp"

#include <iostream>
#include <fstream>


using std::ifstream;
using pugi::xml_document;
using pugi::xml_node;

AudioPlayer::AudioPlayer(string path)
    : mPlayList()
    , mPlayer()
    , mMuted(false)
    , mVolume(60)
    , mCurrent(-1)
{

    xml_document doc;
    ifstream playListSource;
    playListSource.open(path + "playlist.xml");

    doc.load(playListSource);


    xml_node playList = doc.first_child();

    for(xml_node i = playList.first_child(); i; i = i.next_sibling()) {
        mPlayList.push_back(path + i.text().as_string());
    }

    mPlayer.openFromFile(mPlayList[0]);
    mPlayer.setVolume(mVolume);
}

bool AudioPlayer::isPlaying()
{
    return mPlayer.getStatus() == Music::Playing;
}

void AudioPlayer::manipulate(int manipulator)
{
    if(manipulator <= 100) {
        mPlayer.setVolume(manipulator);
        mVolume = manipulator;
        return;
    }
    switch(manipulator) {
    case AudioManipulator::Mute:
        if(mMuted) {
            mMuted = false;
            mPlayer.setVolume(mVolume);
        } else {
            mMuted = true;
            mPlayer.setVolume(false);
        }
        break;
    case AudioManipulator::Down:
        mVolume -= 10;
        if(mVolume < 0) //if volume is lower then 0, then it should be corrected to 0.
            mVolume = 0;
        mPlayer.setVolume(mVolume);
        break;
    case AudioManipulator::Up:
        mVolume += 10;
        if(mVolume > 100) // if volume is more then 100, then it should be corrected to 100.
            mVolume = 100;
        mPlayer.setVolume(mVolume);
        break;
    case AudioManipulator::Pause:
        if(mPlayer.getStatus() == Music::Playing)
            mPlayer.pause();
        break;
    case AudioManipulator::Stop:
        if(mPlayer.getStatus() == Music::Playing)
            mPlayer.stop();
        break;
    case AudioManipulator::Play:
        if(mPlayer.getStatus() != Music::Playing)
            mPlayer.play();
        break;
    case AudioManipulator::Toggle:
        if(mPlayer.getStatus() == Music::Playing) {
            mPlayer.pause();
            break;
        } else if(mPlayer.getStatus() == Music::Paused || mPlayer.getStatus() == Music::Stopped) {
            mPlayer.play();
            break;
        }
    default:
        break;
    }
}

int AudioPlayer::getVolume()
{
    return mVolume;
}



void AudioPlayer::playNext()
{
    if(mPlayer.getStatus() != Music::Stopped)
        return;

    mCurrent++;
    mCurrent %= mPlayList.size();

    mPlayer.openFromFile(mPlayList[mCurrent]);
    mPlayer.play();
}
