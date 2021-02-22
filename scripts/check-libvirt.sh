#!/bin/bash
if [ $(id -Gn "$USER" |grep -c "libvirt") == "0" ] ; then
echo "disabled"
elif [ $(id -Gn "$USER" |grep -c "libvirt") == "1" ] ; then
echo "enabled"
fi
