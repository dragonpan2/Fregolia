#include "Sounds.h"

gameSounds::gameSounds()
{
    mVolumeMusiques = 0.5;
    mVolumeSons = 0.5;

    if(Mix_OpenAudio(22005, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0)
    {
        std::cout << "Erreur d'initialisation de SDL_Mixer: " << Mix_GetError() <<std::endl;
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "MixAudioError", "Erreur dans Mix_OpenAudio.", NULL);
    }

    Mix_VolumeMusic(MIX_MAX_VOLUME * mVolumeMusiques);
    Mix_AllocateChannels(32);
}

gameSounds::~gameSounds()
{
    for(unsigned int i = 0; i < mListeSons.size(); i++)
    {
         Mix_FreeChunk(mListeSons[i]);
    }
    for(unsigned int i = 0; i < mListeMusiques.size(); i++)
    {
        Mix_FreeMusic(mListeMusiques[i]);
    }
    Mix_CloseAudio();
}

int gameSounds::addSon(std::string pFilePath)
{
    mListeSons.push_back(Mix_LoadWAV(pFilePath.c_str()));
    Mix_VolumeChunk(mListeSons[mListeSons.size() - 1], MIX_MAX_VOLUME * mVolumeSons);
    return mListeSons.size() - 1;
}

int gameSounds::addMusique(std::string pFilePath)
{
    mListeMusiques.push_back(Mix_LoadMUS(pFilePath.c_str()));
    return mListeSons.size() - 1;
}

void gameSounds::playSon(int pSon, int pRepeat)
{
    mNoChannels += 1;
    mChannels[mNoChannels] = pSon;
    Mix_PlayChannel(mNoChannels, mListeSons[pSon], pRepeat);
    mNoChannels -= 1;
    mChannels[mNoChannels] = -1;
}

void gameSounds::playMusique(int pMusique, int pRepeat)
{
    mMusiqueActuelle = mListeMusiques[pMusique];
    Mix_PlayMusic(mMusiqueActuelle, pRepeat);
}

void gameSounds::pauseSon(int pSon)
{
    for(int i = 0; i < 32; ++i)
        if(mChannels[i] == pSon)
            Mix_Pause(i);
}

void gameSounds::pauseMusique()
{
    Mix_PauseMusic();
}

void gameSounds::setVolumeMusiques(float pVolume)
{
    mVolumeMusiques = pVolume;
    Mix_VolumeMusic(MIX_MAX_VOLUME * pVolume);
}

void gameSounds::setVolumeSons(float pVolume)
{
    mVolumeSons = pVolume;
    for(unsigned int i = 0; i < mListeSons.size(); ++i)
        Mix_VolumeChunk(mListeSons[mListeSons.size() - 1], MIX_MAX_VOLUME * pVolume);
}


