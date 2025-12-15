#!/bin/bash

current_mode=`cat /sys/devices/platform/ff2b0000.usb2-phy/otg_mode`

if [ $current_mode == "otg" ];then
	echo "----------------change to host mode-------------------------"
	#host
	echo host > /sys/devices/platform/ff2b0000.usb2-phy/otg_mode
else
	echo "----------------change to device mode-------------------------"
	#device
	echo otg > /sys/devices/platform/ff2b0000.usb2-phy/otg_mode
fi
