#pragma once
class zCVideoPlayer
{
	///size 48 byte
    virtual ~zCVideoPlayer();                          // слот 0
    virtual bool OpenVideo(const char* file);          // слот 1
    virtual void CloseVideo();                         // слот 2
    virtual void PlayInit();                           // слот 3
    virtual void PlayFrame();                          // слот 4
    virtual void PlayDeinit();                         // слот 5
    virtual void Pause();                              // слот 6
    virtual void Unpause();                            // слот 7
    virtual void Stop();                               // слот 8
    virtual bool IsPlaying();                          // слот 9
    virtual void ToggleSound();                        // слот 10
    virtual void SetSoundVolume(float v);              // слот 11
    virtual void PlayGotoNextFrame();                  // слот 12
    virtual void PlayWaitNextFrame();                  // слот 13
};

