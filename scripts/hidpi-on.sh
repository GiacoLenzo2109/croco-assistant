#!/bin/bash


function start
{
echo Welcome  to HiDpi script.
echo " "
echo "User = $YOU" 
echo " "
echo "Detected DPI of your screen :$DV"
echo " "
echo "1.Detected DPI :$DV is correct,set screen scaling to $DFV"
echo " "
echo "2.Manually enter DPI value"
echo " "
echo "3.Exit"
echo " "
read -p "Enter your choice : " CH
echo " "
}

function Set_Dpi {
# to get only number 
DPI=$(bc <<< "scale = 0;  $RV / 1")

# Generate a "fractional value" (FV) from a 96dpi default (ie: 120 = 1.25)
FV=$(bc <<< "scale = 2;  $DPI / 96")

# What cursor size you want?
Cursor=$(bc <<< "$FV * 24")

# Apply KDE DPI through system settings
if [ "`which kwriteconfig5`" ]; then
echo forceFontDPI: $DPI
sudo -Hiu $YOU kwriteconfig5 --file /home/$YOU/.config/kcmfonts --group "General" --key "forceFontDPI" "$DPI" ;
echo " "


echo ScaleFactor: $FV
sudo -Hiu $YOU kwriteconfig5 --file /home/$YOU/.config/kdeglobals --group "KScreen" --key "ScaleFactor" "$FV" ;
echo " "


echo cursorSize: $Cursor
sudo -Hiu $YOU kwriteconfig5 --file /home/$YOU/.config/kcminputrc --group "Mouse" --key "cursorSize" "$Cursor" ;
fi
echo " "


# HIDPI SETTINGS
echo /etc/profile.d/hidpi.sh
rm -rf /etc/profile.d/hidpi.sh
echo -e "#!/bin/bash \nexport XCURSOR_SIZE=$Cursor \nexport QT_AUTO_SCREEN_SCALE_FACTOR=0 \nexport GDK_SCALE=$FV \nexport QT_SCALE_FACTOR=$FV \nexport ELM_SCALE=$FV" | tee -a /etc/profile.d/hidpi.sh
chmod +x /etc/profile.d/hidpi.sh
echo " "


# Apply SDDM DPI
echo /etc/sddm.conf.d/hidpi.conf 
rm -rf /etc/sddm.conf.d/hidpi.conf
FDPI=$(cat /home/$YOU/.config/kcmfonts | grep forceFontDPI | awk -F"=" '{print $2}')
echo -e '[X11]\nServerArguments=-nolisten tcp -dpi '"$DPI"'\nEnableHiDPI=true' | tee -a /etc/sddm.conf.d/hidpi.conf ;
echo " "


# And where are your firefox and thunderbird profiles?
FFPRO=$(find /home/$YOU/.mozilla/firefox -name "*.default" -print)
TBPRO=$(find /home/$YOU/.thunderbird/ -name "*.default" -print)
MPPP=$(printf 'user_pref("layout.css.devPixelsPerPx", "'"$FV"'");')


# Firefox
echo $FFPRO
echo $MPPP
if [ "`which firefox`" ]; then
sudo -Hiu $YOU sed -i -e "/$MPPP/d" $FFPRO/user.js ;
sudo -Hiu $YOU touch -a $FFPRO/user.js ;
#sudo -Hiu $YOU sed -i -e '$a\' $FFPRO/user.js ;
sudo -Hiu $YOU printf "$MPPP" >> $FFPRO/user.js ;
fi
echo " "

# Thunderbird
echo $TBPRO
echo $MPPP
if [ "`which thunderbird`" ]; then
sudo -Hiu $YOU sed -i -e "/$MPPP/d" $TBPRO/user.js ;
sudo -Hiu $YOU touch -a $TBPRO/user.js ;
#sudo -Hiu $YOU sed -i -e '$a\' $TBPRO/user.js ;
sudo -Hiu $YOU printf "$MPPP" >> $TBPRO/user.js ;
fi
echo " "

# Chromium
if [ "`which chromium`" ]; then
echo /home/$YOU/.config/chromium-flags.conf
rm -rf /home/$YOU/.config/chromium-flags.conf
sudo -Hiu $YOU echo -e "--force-device-scale-factor=$FV" | tee -a /home/$YOU/.config/chromium-flags.conf ;
fi
echo " "
sleep 10
exit
}


# Who are you anyways
YOU=$(who | awk 'NR==1{print $1}')

# And what do you want?
#RV=$(xrdb -query | grep dpi | grep -o '[^Xft.dpi:]\+$')
DV=$(xdpyinfo | grep dots | grep -o -P '.{0,4}x' | sed 's/x//g')
#xdpy=$(sudo -Hiu $YOU /bin/sh -c 'DISPLAY=:0 xdpyinfo | grep dots')
DFV=$(bc <<< "scale = 2;  $DV / 96")

start

if [ $CH == "1" ]; then
RV=$DV
echo " "

 Set_Dpi


elif [ $CH == "2" ]; then

# And what do you want?
 read -p "Enter Your Screen DPI: "  RV
 echo " "
 if [ $RV -lt "96" ]; then
 echo value lower than 96 is not accepted 
else
Set_Dpi
 fi
 
 elif [ $CH == "3" ]; then 
exit

else
echo "Sorry Not a valid choice,please try again"
sleep 5
fi



