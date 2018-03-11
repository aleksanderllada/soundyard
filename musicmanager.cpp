#include "musicmanager.h"

HGE *MusicManager::hge=NULL;
DWORD MusicManager::channel;
HSTREAM MusicManager::musicStream;
float MusicManager::fft[256];
int MusicManager::vol;
bool MusicManager::isPlaying;

void MusicManager::Init()
{
	hge=hgeCreate(HGE_VERSION);
	channel=0;
	musicStream=0;
	vol=0;
	isPlaying=false;
	for(int x=0; x<256; x++)
		fft[x]=0;
}

void MusicManager::SetMusic(string directory, int volume)
{
	if(isPlaying)
		MusicManager::Stop();

    //Load stream
    musicStream=hge->Stream_Load(directory.data());

    vol=volume;
}

void MusicManager::Analyze()
{
	if(!isPlaying)
		Play();

	int savedVol=vol;

	SetVolume(0);
	SetPos(0);

	float lenght=hge->Channel_GetLength(channel);

	//Algorithm of instrument detection
	for(float scan=0; scan<lenght; scan+=0.25)
	{
		hge->Channel_SetPos(channel, scan);
		DoFastFourierTransform();
	}

	SetVolume(savedVol);
	Stop();
}

void MusicManager::Play()
{
	if(!hge->Channel_IsPlaying(channel))
	{
		channel=hge->Stream_Play(musicStream, true, vol);
		isPlaying=true;
	}
}

void MusicManager::Stop()
{
	if(hge->Channel_IsPlaying(channel))
	{
		hge->Channel_Stop(channel);
		isPlaying=false;
	}
}

void MusicManager::SetVolume(int volume)
{
	vol=volume;
	hge->Channel_SetVolume(channel, vol);
}

void MusicManager::SetPos(float fSeconds)
{
	if(isPlaying)
		hge->Channel_SetPos(channel, fSeconds);
}

void MusicManager::DoFastFourierTransform()
{
	if(isPlaying)
		BASS_ChannelGetData(channel, fft, BASS_DATA_FFT256);
}

float MusicManager::GetMusicSpeed()
{
	if(isPlaying)
	{
		DoFastFourierTransform();

		float sum;
		sum=0;
		for(int x=0; x<256; x++)
		{
			sum+=fft[x]*2500;
		}
		sum/=256;
		sum/=5;
		if(sum==0)
			return 1;
		else
			return sum;
	}
	else
		return 1;
}

MusicManager::~MusicManager()
{
    hge->Release();
}
