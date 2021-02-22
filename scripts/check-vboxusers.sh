#!/bin/bash
if [ $(id -Gn "$USER" |grep -c "vboxusers") == "0" ] ; then
echo "disabled"
elif [ $(id -Gn "$USER" |grep -c "vboxusers") == "1" ] ; then
echo "enabled"
fi
