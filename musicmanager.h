#pragma once
#pragma warning(disable:4200)
#ifndef MUSICMANAGER_H_INCLUDED
#define MUSICMANAGER_H_INCLUDED

#include "bass.h"
#include "hge.h"
#include <string>
#include <iostream>
#include <list>

using std::string;
using std::list;

enum InstrumentType
{
	FLOORTOM=0,
	PLATE,
	VOICE
};

struct InstrumentData
{
	float pos;
	InstrumentType type;
};


class MusicManager
{
private:
    static HGE *hge;
    static DWORD channel;
    static HSTREAM musicStream;
    static float fft[256];
	static int vol;
	static bool isPlaying;
	list<InstrumentData> Instruments;
public:
    ~MusicManager();
	static void Init();
    static void SetMusic(string directory, int volume);
	static void Analyze();
	static void Play();
	static void Stop();
	static void SetVolume(int volume);
	static void SetPos(float fSeconds);
	static void DoFastFourierTransform();
    static float GetMusicSpeed();
};

#endif // MUSICMANAGER_H_INCLUDED
