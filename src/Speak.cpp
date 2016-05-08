#include "Speak.h"

Speak::Speak()
{
  espeak_Initialize(AUDIO_OUTPUT_PLAYBACK, 0, NULL, 0);
  
}

Speak::~Speak()
{
  espeak_Terminate();
}

void Speak::lang(const char *lang)
{
  espeak_SetVoiceByName(lang);
}

void Speak::speak(char *word)
{
  espeak_Synth((char*)word, strlen(word)+1, 0, POS_CHARACTER, 0, espeakCHARS_AUTO, NULL, NULL);
  espeak_Synchronize();
}

void Speak::setRate(int value)
{
  espeak_SetParameter(espeakRATE, value, 0);
}

void Speak::setVoices(unsigned char gender,unsigned char age)
{
  espeak_VOICE *voice_spec=espeak_GetCurrentVoice();
  voice_spec->gender=gender;
  voice_spec->age = age;
  espeak_SetVoiceByProperties(voice_spec);
}
