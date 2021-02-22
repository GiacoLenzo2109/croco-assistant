#!/bin/bash
if [ $(cat /etc/resolv.conf | grep -A1 nameserver | awk '/nameserver/ { print $NF }') == "176.103.130.130" ] ; then
echo "enabled"
else
echo "disabled"
fi 
