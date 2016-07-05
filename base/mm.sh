#!/bin/sh
port=$1
frame_count=$2
make clean
make 
sudo ./base "$port" "$frame_count"
