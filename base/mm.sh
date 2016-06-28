#!/bin/sh
port=$1
make clean
make 
sudo ./base "$port"
