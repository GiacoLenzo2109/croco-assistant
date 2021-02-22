#!/bin/bash
if [ $(id -Gn "$USER" |grep -c "sys") == "0" ] ; then
echo "disabled"
elif [ $(id -Gn "$USER" |grep -c "sys") == "1" ] ; then
echo "enabled"
fi
