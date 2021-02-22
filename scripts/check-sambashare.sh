#!/bin/bash
if [ $(id -Gn "$USER" |grep -c "sambashare") == "0" ] ; then
echo "disabled"
elif [ $(id -Gn "$USER" |grep -c "sambashare") == "1" ] ; then
echo "enabled"
fi
