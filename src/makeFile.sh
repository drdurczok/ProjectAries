#!/bin/bash


    "g++ -o outPut main.cpp Listen.cpp Listen.h \
    -DMODELDIR=\"`pkg-config --variable=modeldir pocketsphinx`\" \
    `pkg-config --cflags --libs pocketsphinx sphinxbase`"
