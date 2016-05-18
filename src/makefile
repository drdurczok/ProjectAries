OBJS = main.o Listen.o Audio.o OperationBase.o Time.o
CC = g++ -std=c++0x
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
LDFLAGS = -I/usr/local/include/sphinxbase -I/usr/local/include/pocketsphinx -I./festival/src/include -I./speech_tools/ -L./festival/src/lib -L./speech_tools 

aries : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o aries -lasound -lFestival -lestools -lestbase -leststring `pkg-config --cflags --libs pocketsphinx sphinxbase`

main.o: main.cpp Listen.h Audio.h OperationBase.h Time.h
	$(CC) $(CFLAGS) $(LDFLAGS) main.cpp 

Listen.o: Listen.h Listen.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) Listen.cpp -DMODELDIR=\"`pkg-config --variable=modeldir pocketsphinx`\"     

Audio.o: Audio.h Audio.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) Audio.cpp

OperationBase.o: OperationBase.h OperationBase.cpp
	$(CC) $(CFLAGS) OperationBase.cpp

Time.o: Time.h Time.cpp
	$(CC) $(CFLAGS) Time.cpp
