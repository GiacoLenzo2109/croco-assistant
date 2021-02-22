#!/bin/bash
if [ $(id -Gn "$USER" |grep -c "video") == "0" ] ; then
echo "disabled"
elif [ $(id -Gn "$USER" |grep -c "video") == "1" ] ; then
echo "enabled"
fi
