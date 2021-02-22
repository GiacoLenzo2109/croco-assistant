#!/bin/bash
chattr -i /etc/resolv.conf
cd /etc

echo “Unlocking resolv.conf…”

cp -rf resolv.conf.bak resolv.conf
chattr -i /etc/resolv.conf
echo “Reboot to use stock DNS servers!” 
notify-send -i "croco" 'Adguard off' 'Reboot to use stock DNS servers!'
