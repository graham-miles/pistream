#!/bin/sh
host=$1
port=$2
make clean
make 
sudo ./logi_loader logi_camera_test.bit
sudo ./test_logi_cam "$host" "$port"
