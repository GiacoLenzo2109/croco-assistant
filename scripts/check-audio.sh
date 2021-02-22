#!/bin/bash
if [ $(id -Gn "$USER" |grep -c "audio") == "0" ] ; then
echo "disabled"
elif [ $(id -Gn "$USER" |grep -c "audio") == "1" ] ; then
echo "enabled"
fi
