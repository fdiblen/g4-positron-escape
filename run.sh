#!/bin/bash

job_folder=$1

# make sure that the data folder exists
mkdir -p $(pwd)/${job_folder}/data

# run the application in Docker container
docker run --net="host" --rm -ti \
	-v $HOME/.Xauthority:/root/.Xauthority \
	-v /tmp/.X11-unix:/tmp/.X11-unix \
	-e DISPLAY=$DISPLAY -e HOSTNAME=gentoo_docker \
	-v $(pwd)/${job_folder}/sources:/home/sources \
	-v $(pwd)/${job_folder}/data:/home/data \
	fdiblen/gentoo:hep-app-positron 

