#include <alsa/asoundlib.h>
#include <festival/festival.h>
#include <fstream>  
#include "Listen.h"
#include "OperationBase.h"
#include "Time.h"


std::string decode();
std::string action(std::string);
void recordAudio(int);
void festival(std::string);


Time timeX;

std::map<std::string, OperationBase> myFunc = 		//{key, {pointer to object, member function}}
	{ 		
		{"time", {&timeX,(ClassProc)&Time::curTime}},
		{"day",{&timeX,(ClassProc)&Time::curDay}},
		{"date",{&timeX,(ClassProc)&Time::curDate}}
	};


int main()
{

  std::string outputString;
  std::string speakString;

  while(outputString != "shutdown")
  {
   outputString = decode(); 

   speakString = action(outputString);

   festival(speakString);
  }

  std::cout << "Thank you, and goodbye" << std::endl;

	/*
	 *  The above sequance is very basic and linear. Ideas to increase the responsiveness of the program
	 *  is to create a thread that is always checking for new raw files and creates new threads appropriately
	 *  to carry out the various commands.
	 *
	 *  Also to minimize processor usage, have to device enter a "sleep mode" during times of low use, such as
	 *  during sleeping or school hours, or have it only begin recording after a specific gesture.
   *
	 */


	return 0;
}


std::string decode()
{
  bool key = 0;

  std::string er = "error";

  Listen listen;

	std::string fileLoc = "audio.raw"; 	//this is the location of the file we will be comparing against our langauge model

	std::string outputString;  //holds the decoded string

	if(listen.init()>0)
	{
		std::cerr<<"error on init"<<std::endl;
		return er;
	}

  recordAudio(2000000);

	std::string keyword;

  listen.setKeyphrase();

  keyword = listen.rawToString(fileLoc.c_str());

  listen.unsetKeyphrase();

  if (keyword == "aries")
    {
      recordAudio(5000000);
      outputString = listen.rawToString(fileLoc.c_str());   //process the .raw file and store the string
      remove ("audio.raw");
    }

  remove ("audio.raw");

  return outputString;
}


std::string action(std::string key) 
{ 
  std::string speakString;

  if ( myFunc.find(key) == myFunc.end() ) {
  speakString = "ERROR: Key not found";
  } else {
  speakString = myFunc.find(key)->second.execute(); 
  }

  return speakString;
}

void recordAudio(int len) 
{
  std::ofstream outfile ("audio.raw",std::ofstream::binary);

  long loops;
  int rc;
  int size;
  snd_pcm_t *handle;
  snd_pcm_hw_params_t *params;
  unsigned int val;
  int dir;
  snd_pcm_uframes_t frames;
  char *buffer;

  /* Open PCM device for recording (capture). */
  rc = snd_pcm_open(&handle, "default", SND_PCM_STREAM_CAPTURE, 0);
  if (rc < 0) 
  {
    fprintf(stderr, "unable to open pcm device: %s\n", snd_strerror(rc));
    exit(1);
  }



  /* Allocate a hardware parameters object. */
  snd_pcm_hw_params_alloca(&params);

  /* Fill it in with default values. */
  snd_pcm_hw_params_any(handle, params);



  /* Set the desired hardware parameters. */

  /* Interleaved mode */
  snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);

  /* Signed 16-bit little-endian format */
  snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S16_LE);

  /* Single channel (monoaural) */
  snd_pcm_hw_params_set_channels(handle, params, 2);

  /* 44100 bits/second sampling rate (CD quality) */
  val = 8000;
  snd_pcm_hw_params_set_rate_near(handle, params, &val, &dir);

  /* Set period size to 32 frames. */
  frames = 256;
  snd_pcm_hw_params_set_period_size_near(handle, params, &frames, &dir);

  /* Write the parameters to the driver */
  rc = snd_pcm_hw_params(handle, params);
  if (rc < 0) 
  {
    fprintf(stderr, "unable to set hw parameters: %s\n", snd_strerror(rc));
    exit(1);
  }



  /* Use a buffer large enough to hold one period */
  snd_pcm_hw_params_get_period_size(params, &frames, &dir);
  size = frames * 4; /* 2 bytes/sample, 2 channels */
  buffer = (char *) malloc(size);

  /* We want to loop for 5 seconds */
  snd_pcm_hw_params_get_period_time(params, &val, &dir);
  loops = len / val;

  /*file written to */
  FILE *audio;
  audio = fopen("audio.raw", "a");

  double bytes;

  std::cout << "Recording Audio..." << std::endl;

  while (loops > 0) {
    loops--;
    rc = snd_pcm_readi(handle, buffer, frames);
    if (rc == -EPIPE) 
    {
      /* EPIPE means overrun */
      fprintf(stderr, "overrun occurred\n");
      snd_pcm_prepare(handle);
    } else if (rc < 0) {
      fprintf(stderr, "error from read: %s\n", snd_strerror(rc));
    } else if (rc != (int)frames) {
      fprintf(stderr, "short read, read %d frames\n", rc);
    }

    outfile.write(buffer, size);      
  }

  snd_pcm_drain(handle);
  snd_pcm_close(handle);
  free(buffer);
}

void festival(std::string speakString)
{
    EST_Wave wave;
    int heap_size = 210000;  // default scheme heap size
    int load_init_files = 1; // we want the festival init files loaded

    festival_initialize(load_init_files,heap_size);

    // Say some text;
    festival_say_text(speakString.c_str());

    festival_wait_for_spooler();
}
