#!/bin/bash
if [ $(cat /etc/gdm/custom.conf | grep -A1 WaylandEnable | awk '/WaylandEnable/ { print $NF }') == "WaylandEnable=false" ] ; then
echo "disabled"
else
echo "enabled"
fi  
