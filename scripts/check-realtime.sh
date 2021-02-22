#!/bin/bash
if [ $(id -Gn "$USER" |grep -c "realtime") == "0" ] ; then
echo "disabled"
elif [ $(id -Gn "$USER" |grep -c "realtime") == "1" ] ; then
echo "enabled"
fi
