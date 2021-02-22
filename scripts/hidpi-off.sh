#!/usr/bin/env bash
# Who are you anyways
YOU=$(who | awk '{print $1}')


# Apply KDE DPI through system settings
if [ "`which kwriteconfig5`" ]; then
sudo -Hiu $YOU kwriteconfig5 --file ~/.config/kcmfonts --group "General" --key "forceFontDPI" "96" ;
sudo -Hiu $YOU kwriteconfig5 --file ~/.config/kdeglobals --group "KScreen" --key "ScaleFactor" "1" ;
sudo -Hiu $YOU kwriteconfig5 --file ~/.config/kcminputrc --group "Mouse" --key "cursorSize" "24" ;
fi

# HIDPI SETTINGS
rm -rf /etc/profile.d/hidpi.sh

# Apply SDDM DPI
rm -rf /etc/sddm.conf.d/hidpi.conf


# And where are your firefox and thunderbird profiles?
TBPRO=$(find ~/.thunderbird/ -name "*.default" -print)
FFPRO=$(find ~/.mozilla/firefox -name "*.default" -print)
MPPP=$(printf 'user_pref("layout.css.devPixelsPerPx", "'"$FV"'");')

# Thunderbird
if [ "`which thunderbird`" ]; then
sudo -Hiu $YOU sed -i -e "/$MPPP/d" $TBPRO/user.js ;
rm -rf $TBPRO/user.js
fi

# Firefox
if [ "`which firefox`" ]; then
sudo -Hiu $YOU sed -i -e "/$MPPP/d" $FFPRO/user.js ;
rm -rf $FFPRO/user.js
fi

# Chromium
if [ "`which chromium`" ]; then
rm -rf /home/$YOU/.config/chromium-flags.conf
fi


exit
