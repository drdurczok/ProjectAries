#ifndef SPEAK_H
#define SPEAK_H

#include <string.h>
#include <stdlib.h>
#include "speak_lib.h"


class Speak
{
	public:
		Speak();
		~Speak();

	private:
		void lang(const char *lang);
		void speak(char *word);
		void setRate(int value);
		void setVoices(unsigned char gender,unsigned char age);
};


#endif