#ifndef SOUNDS_H_INCLUDED
#define SOUNDS_H_INCLUDED

#include "externalIncludes.h"

class gameSounds
{
public:
    gameSounds();
    virtual ~gameSounds();

    virtual int addSon(std::string pFilePath);
    virtual int addMusique(std::string pFilePath);

    virtual void playSon(int pSon, int pRepeat);
    virtual void playMusique(int pMusique, int pRepeat);

    virtual void pauseSon(int pSon);
    virtual void pauseMusique();

    virtual void setVolumeMusiques(float pVolume);
    virtual void setVolumeSons(float pVolume);
private:
    std::vector<Mix_Music*> mListeMusiques;
    std::vector<Mix_Chunk*> mListeSons;

    Mix_Music* mMusiqueActuelle;

    float mVolumeMusiques;
    float mVolumeSons;

    int mChannels[32];
    int mNoChannels;

};



#endif // SOUNDS_H_INCLUDED
