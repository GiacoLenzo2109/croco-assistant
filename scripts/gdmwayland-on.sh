#!/bin/bash
if [[ -e /etc/gdm/custom.conf ]]; then
	sed -i -e 's|.*WaylandEnable=false|#WaylandEnable=false|g' /etc/gdm/custom.conf
fi 

cp /etc/environment /etc/environment.bak

echo "QT_QPA_PLATFORM=wayland
_JAVA_AWT_WM_NONREPARENTING=1
MOZ_ENABLE_WAYLAND=1 
XDG_SESSION_TYPE=wayland
EDITOR=/usr/bin/micro
BROWSER=firefox
TERM=alacritty
MAIL=geary
QT_QPA_PLATFORMTHEME=qt5ct" >> /etc/environment
