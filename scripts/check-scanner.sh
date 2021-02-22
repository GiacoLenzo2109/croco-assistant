#!/bin/bash
if [ $(id -Gn "$USER" |grep -c "scanner") == "0" ] ; then
echo "disabled"
elif [ $(id -Gn "$USER" |grep -c "scanner") == "1" ] ; then
echo "enabled"
fi
