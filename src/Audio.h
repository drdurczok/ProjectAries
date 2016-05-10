#ifndef AUDIO_H
#define AUDIO_H

#include <alsa/asoundlib.h>
#include <festival/festival.h>

class Audio
{
	public:
		Audio();

		void recordAudio(int len);
		void playback();
		void festival(std::string speakString);
};

#endif
