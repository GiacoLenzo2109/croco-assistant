#!/bin/bash
chattr -i /etc/resolv.conf
cd /etc
cp -rf resolv.conf resolv.conf.bak
echo “Applying Adguard DNS servers…”
 sed -i -e "/nameserver*/d" /etc/resolv.conf ;
 sed -i '$a\' /etc/resolv.conf ;
 printf "nameserver 176.103.130.130" >> /etc/resolv.conf ;
#sed -i -e 's|nameserver|nameserver 176.103.130.130|g'  /etc/resolv.conf
echo “Prevent resolv.conf from being overwritten”
chattr +i /etc/resolv.conf

echo “Adblocking enabled!” 
notify-send -i "croco" 'Adguard on' 'Adblocking enabled!'
