#!/bin/bash

SFML=`dpkg -l | grep sfml | wc -l`

if [ $SFML -gt 0 ]
then
  echo "SFML already installed"
else
  echo "Installing SFML"
  apt-get install libsfml-dev
fi

COMPILER=`dpkg -l | grep g++ | wc -l`

if [ $COMPILER -gt 0 ]
then
  echo "g++ already installed"
else
  echo "Installing g++"
  apt-get install g++
fi

CMAKE=`dpkg -l | grep cmake | wc -l`

if [ $CMAKE -gt 0 ]
then
  echo "cmake already installed"
else
  echo "Installing cmake"
  apt-get install cmake
fi
