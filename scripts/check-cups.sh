#!/bin/bash
if [ $(id -Gn "$USER" |grep -c "cups") == "0" ] ; then
echo "disabled"
elif [ $(id -Gn "$USER" |grep -c "cups") == "1" ] ; then
echo "enabled"
fi
