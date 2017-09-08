#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <SFML/Audio/Music.hpp>
#include <vector>

using std::vector;
using std::string;
using sf::Music;
/**
 * Enum for manipulating Audiio player.
 * Values from 0 to 100 are used for volume.
 *
 */
enum AudioManipulator {
    Mute = 101, /**< Mutes*/
    Up = 102, /**< Increases volume by 10.*/
    Down = 103, /**< Decreases volume by 10.*/
    Stop = 104, /**< Stoping music.*/
    Pause = 105, /**< Pausing music.*/
    Play = 106, /**< Playing music, if music is paused it will unpose, or, if it is stopped it plays from beginning.*/
    Toggle = 107 /**< Combination of Play and Pause.*/
};


/**
 * Main class for playing music.
 * Sound effects are not played in here.
 */
class AudioPlayer {
public:
    /** Constructor */
    AudioPlayer(string path = "media/audio/music/");
    /** Current status of player. */
    bool isPlaying();
    /**
     * Only this method can be used for manipulating player.
     */
    void manipulate(int manipulator);
    /**
     * Get current volume.
     */
    int getVolume();
    /**
     * Play next song.
     */
    void playNext();
protected:
private:
    vector<string> mPlayList; /**< Music playlist.*/
    int mCurrent; /**< Index of currently played song.*/
    Music mPlayer; /**< sf::Music member*/
    int mVolume; /**< Current volume*/
    bool mMuted; /**< Muted member*/
};

#endif // AUDIOPLAYER_H
