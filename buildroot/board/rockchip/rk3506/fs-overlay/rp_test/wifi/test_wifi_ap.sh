#/bin/bash

echo =================================
echo WIFI AP model test
echo =================================

board=`cat /proc/device-tree/model`
password="12345678"

echo "hotspot name: $board"
echo "password: 12345678"

killall dnsmasq
killall dhdpcd

#use wlan1 creat AP
ifconfig wlan0 up
iw phy0 interface add wlan1 type managed
ifconfig wlan1 up
create_ap -w 2  wlan1 eth0 ${board} ${password} --no-virt
