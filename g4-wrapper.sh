#!/bin/bash

usage() { echo "Usage: $0 [-e] [-c] [-m <macro name>]" 1>&2; exit 1; }

compile() {
    source /etc/profile
    cd /home/positronEscape
    mkdir build && cd build
    cmake ..
    make -j4
}

run(){
   compile
   time=$(date +%H_%M__%d_%m__%Y)
   source /etc/profile
   cd /home/positronEscape/build/
   for file in $(ls /home/sources/*.mac)
   do
       baseName=$(basename ${file})
       ./positronEscape $file && mv *.root /home/data/${time}_${baseName}.root
       sleep 10s
   done
}


while getopts ":e:c:m:" o; do
    case "${o}" in
        e)
            e=${OPTARG}
	    # not used
            #((e == 45 || e == 90)) || usage
	    echo "Events: " $e
            ;;
        c)
	    compile
            ;;
        m)
            m=${OPTARG}
	    echo "Running macro: " $m
            ;;
        *)
            usage
            ;;
    esac
done
shift $((OPTIND-1))

echo "Current directory: " $(pwd)
echo "Running macro: " ${m}
echo
run
