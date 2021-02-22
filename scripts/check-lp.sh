#!/bin/bash
if [ $(id -Gn "$USER" |grep -c "lp") == "0" ] ; then
echo "disabled"
elif [ $(id -Gn "$USER" |grep -c "lp") == "1" ] ; then
echo "enabled"
fi
