#!/bin/sh
#install dependencies
echo Установка начинается, пожалуйста введите пароль для установки с правами root
sleep 5
sudo apt-get install mercurial and python3-dev and python3-setuptools and python3-numpy and python3-opengl and libav-tools and libsdl-image1.2-dev and libsdl-mixer1.2-dev and libsdl-ttf2.0-dev and libsmpeg-dev and libsdl1.2-dev and libportmidi-dev and libswscale-dev and libavformat-dev and libavcodec-dev and libtiff5-dev and libx11-6 and libx11-dev and fluid-soundfont-gm and timgm6mb-soundfont and xfonts-base and xfonts-100dpi and xfonts-75dpi and xfonts-cyrillic and fontconfig and fonts-freefont-ttf -y
echo
echo Подключаем репозиторий....
sleep 1
# Grab source
hg clone https://bitbucket.org/pygame/pygame
echo
echo Начинаем компиляцию
sleep 1
# Finally build and install
cd pygame
python3 setup.py build
sudo python3 setup.py install

