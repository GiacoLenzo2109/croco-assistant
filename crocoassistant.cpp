#include "crocoassistant.h"
#include "ui_crocoassistant.h"

CrocoAssistant::crocoAssistant(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::crocoAssistant)
{
    ui->setupUi(this);
    setup();
    check_status();
    on_toolButton_diskRefresh_clicked();
    //check_status_qwickaccess();
    //check_status_control();
}

CrocoAssistant::~crocoAssistant()
{
    delete ui;
}

// Util function for getting bash command output and error code
Result CrocoAssistant::runCmd(QString cmd)
{
    QEventLoop loop;
    proc = new QProcess(this);
    proc->setReadChannelMode(QProcess::MergedChannels);
    connect(proc, SIGNAL(finished(int)), &loop, SLOT(quit()));
    proc->start("/bin/bash", QStringList() << "-c" << cmd);
    loop.exec();
    disconnectAll();
    Result result = {proc->exitCode(), proc->readAll().trimmed()};
    delete proc;
    return result;
}

// disconnect all connections
void CrocoAssistant::disconnectAll()
{
    disconnect(proc, SIGNAL(started()), 0, 0);
    disconnect(proc, SIGNAL(finished(int)), 0, 0);
}

// set proc and timer connections
void CrocoAssistant::setConnections()
{
    connect(proc, SIGNAL(started()), SLOT(procStart()));
    connect(proc, SIGNAL(finished(int)), SLOT(procDone(int)));
}

// setup versious items first time program runs
void CrocoAssistant::setup()
{
    this->setWindowTitle(tr("Croco Assistant"));
    QString gdm = runCmd("pacman -Qq gdm").output;
    if (system("[ -f /usr/sbin/gdm ]") != 0) {
        ui->groupBox_gdm->hide();
    }
    //this->adjustSize();

}

void CrocoAssistant::check_status()
{
    QProcess proc;

    proc.start("pacman -Qq gstreamer-meta");
    proc.waitForFinished();
        QString gstreamer=proc.readAllStandardOutput();
        gstreamer = gstreamer.trimmed();

    if (gstreamer == "gstreamer-meta"){
        ui->checkBox_gstreamer->setChecked(true);
    }
    else
    {
        ui->checkBox_gstreamer->setChecked(false);
    }

    proc.start("/bin/bash", QStringList()<< "/usr/share/croco/scripts/check-video.sh");
    proc.waitForFinished();
    QString video=proc.readAllStandardOutput();
    video = video.trimmed();
    if (video == "enabled"){
             ui->checkBox_video->setChecked(true);
    }
    else
    {
             ui->checkBox_video->setChecked(false);
    }

    proc.start("pacman -Qq systemd-guest-user");
    proc.waitForFinished();
        QString guest=proc.readAllStandardOutput();
        guest = guest.trimmed();
       // qDebug()<< guest;
    if (guest == "systemd-guest-user"){
        ui->checkBox_guest->setChecked(true);
    }
    else
    {
        ui->checkBox_guest->setChecked(false);
    }

    proc.start("/bin/bash", QStringList()<< "/usr/share/croco/scripts/check-adguard.sh");
    proc.waitForFinished();
        QString adguard=proc.readAllStandardOutput();
        adguard = adguard.trimmed();
        //qDebug()<< adguard;
        if (adguard == "enabled"){
            ui->checkBox_adguard->setChecked(true);
        }
        else
        {
            ui->checkBox_adguard->setChecked(false);
        }

        proc.start("/bin/bash", QStringList()<< "/usr/share/croco/scripts/check-hblock.sh");
        proc.waitForFinished();
            QString hblock=proc.readAllStandardOutput();
            hblock = hblock.trimmed();

            if (hblock == "enabled"){
                ui->checkBox_hblock->setChecked(true);
            }
            else
            {
                ui->checkBox_hblock->setChecked(false);
            }

        proc.start("pacman -Qq printer-support");
        proc.waitForFinished();
            QString printer=proc.readAllStandardOutput();
            printer = printer.trimmed();
           // qDebug()<< printer;
        if (printer == "printer-support"){
            ui->checkBox_printer->setChecked(true);
        }
        else
        {
            ui->checkBox_printer->setChecked(false);
        }

        proc.start("/bin/bash", QStringList()<< "/usr/share/croco/scripts/check-cups.sh");
        proc.waitForFinished();
        QString cups=proc.readAllStandardOutput();
        cups = cups.trimmed();
        //qDebug()<< sambashare;
        if (cups == "enabled"){
                 ui->checkBox_cupsgrp->setChecked(true);
        }
        else
        {
                 ui->checkBox_cupsgrp->setChecked(false);
        }
        
        proc.start("/bin/bash", QStringList()<< "/usr/share/croco/scripts/check-sys.sh");
        proc.waitForFinished();
        QString sys=proc.readAllStandardOutput();
        sys = sys.trimmed();
        //qDebug()<< sambashare;
        if (sys == "enabled"){
                 ui->checkBox_sysgrp->setChecked(true);
        }
        else
        {
                 ui->checkBox_sysgrp->setChecked(false);
        }

        proc.start("systemctl", QStringList()<< "is-enabled" << "cups.socket" << "--no-ask-password");
        proc.waitForFinished();
            QString cupsstatus=proc.readAllStandardOutput();
            cupsstatus = cupsstatus.trimmed();
            if (cupsstatus == "enabled"){
                ui->checkBox_cups->setChecked(true);
            }
            else
            {
                ui->checkBox_cups->setChecked(false);
            }

            proc.start("pacman -Qq scanner-support");
            proc.waitForFinished();
                QString scanner=proc.readAllStandardOutput();
                scanner = scanner.trimmed();
              //  qDebug()<< scanner;
            if (scanner == "scanner-support"){
                ui->checkBox_scanning->setChecked(true);
            }
            else
            {
                ui->checkBox_scanning->setChecked(false);
            }


            proc.start("systemctl", QStringList()<< "is-enabled" << "ipp-usb" << "--no-ask-password");
            proc.waitForFinished();
                QString usbipp=proc.readAllStandardOutput();
                usbipp = usbipp.trimmed();
                if (usbipp == "enabled"){
                ui->checkBox_usbipp->setChecked(true);
            }
            else
            {
                ui->checkBox_usbipp->setChecked(false);
            }

            proc.start("systemctl", QStringList()<< "is-enabled" << "saned.socket" << "--no-ask-password");
            proc.waitForFinished();
                QString saned=proc.readAllStandardOutput();
                saned = saned.trimmed();
                if (saned == "enabled"){
                ui->checkBox_saned->setChecked(true);
            }
            else
            {
                ui->checkBox_saned->setChecked(false);
            }
            
        proc.start("/bin/bash", QStringList()<< "/usr/share/croco/scripts/check-scanner.sh");
        proc.waitForFinished();
        QString scannergrp=proc.readAllStandardOutput();
        scannergrp = scannergrp.trimmed();
        //qDebug()<< sambashare;
        if (scannergrp == "enabled"){
                 ui->checkBox_scannergrp->setChecked(true);
        }
        else
        {
                 ui->checkBox_scannergrp->setChecked(false);
        }


            proc.start("pacman -Qq samba-support");
            proc.waitForFinished();
                 QString samba=proc.readAllStandardOutput();
                    samba = samba.trimmed();
                  //  qDebug()<< samba;
            if (samba == "samba-support"){
                    ui->checkBox_samba->setChecked(true);
            }
            else
              {
                    ui->checkBox_samba->setChecked(false);
              }


            proc.start("/bin/bash", QStringList()<< "/usr/share/croco/scripts/check-sambashare.sh");
            proc.waitForFinished();
            QString sambashare=proc.readAllStandardOutput();
            sambashare = sambashare.trimmed();
            //qDebug()<< sambashare;
            if (sambashare == "enabled"){
                     ui->checkBox_sambashare->setChecked(true);
            }
            else
            {
                     ui->checkBox_sambashare->setChecked(false);
            }

            proc.start("systemctl", QStringList()<< "is-enabled" << "smb" << "--no-ask-password");
            proc.waitForFinished();
            QString smbstatus=proc.readAllStandardOutput();
            smbstatus = smbstatus.trimmed();
            if (smbstatus == "enabled"){
                            ui->checkBox_smb->setChecked(true);
            }
            else
            {
                            ui->checkBox_smb->setChecked(false);
            }

            proc.start("systemctl", QStringList()<< "is-enabled" << "nmb" << "--no-ask-password");
            proc.waitForFinished();
            QString nmbstatus=proc.readAllStandardOutput();
            nmbstatus = nmbstatus.trimmed();
            if (nmbstatus == "enabled"){
                                ui->checkBox_nmb->setChecked(true);
            }
             else
            {
                                ui->checkBox_nmb->setChecked(false);
            }

            proc.start("pacman -Qq firewalld");
            proc.waitForFinished();
                QString firewalld=proc.readAllStandardOutput();
                firewalld = firewalld.trimmed();
            if (firewalld == "firewalld"){
                ui->checkBox_firewalld->setChecked(true);
            }
            else
            {
                ui->checkBox_firewalld->setChecked(false);
            }

            proc.start("systemctl", QStringList()<< "is-enabled" << "firewalld" << "--no-ask-password");
            proc.waitForFinished();
            QString firewalldstatus=proc.readAllStandardOutput();
            firewalldstatus = firewalldstatus.trimmed();
            if (firewalldstatus == "enabled"){
                                ui->checkBox_firewalldservice->setChecked(true);
            }
             else
            {
                                ui->checkBox_firewalldservice->setChecked(false);
            }

            proc.start("pacman -Qq ufw");
            proc.waitForFinished();
            QString ufw=proc.readAllStandardOutput();
            ufw = ufw.trimmed();
            if (ufw == "ufw"){
                            ui->checkBox_ufw->setChecked(true);
            }
            else
            {
                            ui->checkBox_ufw->setChecked(false);
            }

            proc.start("systemctl", QStringList()<< "is-enabled" << "ufw" << "--no-ask-password");
            proc.waitForFinished();
            QString ufwstatus=proc.readAllStandardOutput();
            ufwstatus = ufwstatus.trimmed();
            if (ufwstatus == "enabled"){
                                            ui->checkBox_ufwservice->setChecked(true);
            }
             else
            {
                                            ui->checkBox_ufwservice->setChecked(false);
            }


            proc.start("pacman -Qq fcitx-input-support");
            proc.waitForFinished();
                QString fcitx=proc.readAllStandardOutput();
                fcitx = fcitx.trimmed();
            if (fcitx == "fcitx-input-support"){
                ui->checkBox_fcitx->setChecked(true);
            }
            else
            {
                ui->checkBox_fcitx->setChecked(false);
            }

            proc.start("pacman -Qq fcitx5-input-support");
            proc.waitForFinished();
                QString fcitx5=proc.readAllStandardOutput();
                fcitx5 = fcitx5.trimmed();
            if (fcitx5 == "fcitx5-input-support"){
                ui->checkBox_fcitx5->setChecked(true);
            }
            else
            {
                ui->checkBox_fcitx5->setChecked(false);
            }

            proc.start("pacman -Qq ibus-input-support");
            proc.waitForFinished();
                QString ibus=proc.readAllStandardOutput();
                ibus = ibus.trimmed();
            if (ibus == "ibus-input-support"){
                ui->checkBox_ibus->setChecked(true);
            }
            else
            {
                ui->checkBox_ibus->setChecked(false);
            }
            proc.start("pacman -Qq asian-fonts");
            proc.waitForFinished();
                QString asian=proc.readAllStandardOutput();
                asian = asian.trimmed();
            if (asian == "asian-fonts"){
                ui->checkBox_asian->setChecked(true);
            }
            else
            {
                ui->checkBox_asian->setChecked(false);
            }

            proc.start("pacman -Qq evdev-right-click-emulation");
            proc.waitForFinished();
                QString lptrce=proc.readAllStandardOutput();
                lptrce = lptrce.trimmed();
            if (lptrce == "evdev-right-click-emulation"){
                ui->checkBox_lptrce->setChecked(true);
            }
            else
            {
                ui->checkBox_lptrce->setChecked(false);
            }
            proc.start("systemctl", QStringList()<< "is-enabled" << "evdev-rce" << "--no-ask-password");
            proc.waitForFinished();
                QString evdevrce=proc.readAllStandardOutput();
                evdevrce = evdevrce.trimmed();
                if (evdevrce == "enabled"){
                    ui->checkBox_evdevrce->setChecked(true);
                }
                else
                {
                    ui->checkBox_evdevrce->setChecked(false);
                }

                proc.start("pacman -Qq virt-manager-meta");
                                proc.waitForFinished();
                                     QString virtmanager=proc.readAllStandardOutput();
                                        virtmanager = virtmanager.trimmed();
                                      //  qDebug()<< virtmanager;
                                if (virtmanager == "virt-manager-meta"){
                                        ui->checkBox_virtmanager->setChecked(true);
                                }
                                else
                                  {
                                        ui->checkBox_virtmanager->setChecked(false);
                                  }


                                proc.start("/bin/bash", QStringList()<< "/usr/share/croco/scripts/check-libvirt.sh");
                                proc.waitForFinished();
                                QString libvirtgrp=proc.readAllStandardOutput();
                                libvirtgrp = libvirtgrp.trimmed();
                                //qDebug()<< libvirt;
                                if (libvirtgrp == "enabled"){
                                         ui->checkBox_libvirtgrp->setChecked(true);
                                }
                                else
                                {
                                         ui->checkBox_libvirtgrp->setChecked(false);
                                }

                                proc.start("systemctl", QStringList()<< "is-enabled" << "libvirtd" << "--no-ask-password");
                                proc.waitForFinished();
                                QString libvirtdstatus=proc.readAllStandardOutput();
                                libvirtdstatus = libvirtdstatus.trimmed();
                                if (libvirtdstatus == "enabled"){
                                                ui->checkBox_libvirtd->setChecked(true);
                                }
                                else
                                {
                                                ui->checkBox_libvirtd->setChecked(false);
                                }

                                proc.start("pacman -Qq virtualbox-meta");
                                                               proc.waitForFinished();
                                                                    QString virtualbox=proc.readAllStandardOutput();
                                                                       virtualbox = virtualbox.trimmed();
                                                                     //  qDebug()<< virtualbox;
                                                               if (virtualbox == "virtualbox-meta"){
                                                                       ui->checkBox_virtualbox->setChecked(true);
                                                               }
                                                               else
                                                                 {
                                                                       ui->checkBox_virtualbox->setChecked(false);
                                                                 }


                                                               proc.start("/bin/bash", QStringList()<< "/usr/share/croco/scripts/check-vboxusers.sh");
                                                               proc.waitForFinished();
                                                               QString vboxusers=proc.readAllStandardOutput();
                                                               vboxusers = vboxusers.trimmed();
                                                               //qDebug()<< libvirt;
                                                               if (vboxusers == "enabled"){
                                                                        ui->checkBox_vboxusers->setChecked(true);
                                                               }
                                                               else
                                                               {
                                                                        ui->checkBox_vboxusers->setChecked(false);
                                                               }


      /*  proc.start("/bin/bash", QStringList()<< "/usr/share/croco/scripts/check-hidpi.sh");
        proc.waitForFinished();
            QString hidpi=proc.readAllStandardOutput();
            hidpi = hidpi.trimmed();
            //qDebug()<< hidpi;
            if (hidpi == "enabled"){
                ui->checkBox_hidpi->setChecked(true);
            }
            else
            {
                ui->checkBox_hidpi->setChecked(false);
            }

    */

                proc.start("/bin/bash", QStringList()<< "/usr/share/croco/scripts/check-gdmwayland.sh");
                proc.waitForFinished();
                    QString gdmwayland=proc.readAllStandardOutput();
                    gdmwayland = gdmwayland.trimmed();
                    //qDebug()<< gdmwayland;
                    if (gdmwayland == "enabled"){
                        ui->checkBox_gdm->setChecked(true);
                    }
                    else
                    {
                        ui->checkBox_gdm->setChecked(false);
                    }


                    proc.start("systemctl", QStringList()<< "is-enabled" << "fstrim.timer" << "--no-ask-password");
                    proc.waitForFinished();
                    QString fstrimstatus=proc.readAllStandardOutput();
                    fstrimstatus = fstrimstatus.trimmed();
                    if (fstrimstatus == "enabled"){
                        ui->checkBoxFstrim->setChecked(true);
                    }
                    else
                    {
                        ui->checkBoxFstrim->setChecked(false);
                    }

                    proc.start("systemctl", QStringList()<< "is-enabled" << "btrfs-scrub@-.timer" << "--no-ask-password");
                    proc.waitForFinished();
                        QString scrubstatus=proc.readAllStandardOutput();
                        scrubstatus = scrubstatus.trimmed();
                        if (scrubstatus == "enabled"){
                            ui->checkBox_Scrub->setChecked(true);
                        }
                        else
                        {
                            ui->checkBox_Scrub->setChecked(false);
                        }


        proc.start("systemctl", QStringList()<< "is-enabled" << "ModemManager" << "--no-ask-password");
        proc.waitForFinished();
        QString modemservice=proc.readAllStandardOutput();
        modemservice = modemservice.trimmed();
        if (modemservice == "enabled"){
            ui->checkBox_modemmanager->setChecked(true);
        }
        else
        {
            ui->checkBox_modemmanager->setChecked(false);
        }

        proc.start("systemctl", QStringList()<< "is-enabled" << "gpsd" << "--no-ask-password");
        proc.waitForFinished();
        QString gpsd=proc.readAllStandardOutput();
        gpsd = gpsd.trimmed();
        if (gpsd == "enabled"){
            ui->checkBox_gpsd->setChecked(true);
        }
        else
        {
            ui->checkBox_gpsd->setChecked(false);
        }

        proc.start("systemctl", QStringList()<< "is-enabled" << "ofono" << "--no-ask-password");
        proc.waitForFinished();
        QString ofono=proc.readAllStandardOutput();
        ofono = ofono.trimmed();
        if (ofono == "enabled"){
            ui->checkBox_ofono->setChecked(true);
        }
        else
        {
            ui->checkBox_ofono->setChecked(false);
        }

        proc.start("systemctl", QStringList()<< "is-enabled" << "neard" << "--no-ask-password");
        proc.waitForFinished();
        QString neard=proc.readAllStandardOutput();
        neard = neard.trimmed();
        if (neard == "enabled"){
            ui->checkBox_neard->setChecked(true);
        }
        else
        {
            ui->checkBox_neard->setChecked(false);
        }

        proc.start("pacman -Qq networkmanager-support");
        proc.waitForFinished();
             QString network=proc.readAllStandardOutput();
                network = network.trimmed();

        if (network == "networkmanager-support")
        {
                ui->checkBox_network->setChecked(true);
        }
        else
        {
                ui->checkBox_network->setChecked(false);
        }

        proc.start("systemctl", QStringList()<< "is-enabled" << "NetworkManager" << "--no-ask-password");
        proc.waitForFinished();
        QString networkservice=proc.readAllStandardOutput();
        networkservice = networkservice.trimmed();
        if (networkservice == "enabled"){
            ui->checkBox_networkservice->setChecked(true);
        }
        else
        {
            ui->checkBox_networkservice->setChecked(false);
        }

        proc.start("pacman -Qq connman-support");
        proc.waitForFinished();
             QString connman=proc.readAllStandardOutput();
                connman = connman.trimmed();

        if (connman == "connman-support")
        {
                ui->checkBox_connman->setChecked(true);
        }
        else
        {
                ui->checkBox_connman->setChecked(false);
        }

        proc.start("systemctl", QStringList()<< "is-enabled" << "connman" << "--no-ask-password");
        proc.waitForFinished();
        QString connmanservice=proc.readAllStandardOutput();
        connmanservice = connmanservice.trimmed();
        if (connmanservice == "enabled"){
            ui->checkBox_connmanservice->setChecked(true);
        }
        else
        {
            ui->checkBox_connmanservice->setChecked(false);
        }
        proc.start("pacman -Qq bluetooth-support");
        proc.waitForFinished();
             QString bluetooth=proc.readAllStandardOutput();
                bluetooth = bluetooth.trimmed();
              //  qDebug()<< bluetooth;
        if (bluetooth == "bluetooth-support")
        {
                ui->checkBox_bluetooth->setChecked(true);
        }
        else
        {
                ui->checkBox_bluetooth->setChecked(false);
        }

        proc.start("systemctl", QStringList()<< "is-enabled" << "bluetooth" << "--no-ask-password");
        proc.waitForFinished();
        QString bluetoothservice=proc.readAllStandardOutput();
        bluetoothservice = bluetoothservice.trimmed();
        if (bluetoothservice == "enabled"){
            ui->checkBox_bluetoothservice->setChecked(true);
        }
        else
        {
            ui->checkBox_bluetoothservice->setChecked(false);
        }

        proc.start("systemctl", QStringList()<< "is-enabled" << "bluetooth-autoconnect" << "--no-ask-password");
        proc.waitForFinished();
        QString bluetoothauto=proc.readAllStandardOutput();
        bluetoothauto = bluetoothauto.trimmed();
        if (bluetoothauto == "enabled"){
            ui->checkBox_bluetoothauto->setChecked(true);
        }
        else
        {
            ui->checkBox_bluetoothauto->setChecked(false);
        }

        proc.start("systemctl", QStringList()<< "is-enabled" << "pulseaudio-bluetooth-autoconnect" << "--user" << "--no-ask-password");
        proc.waitForFinished();
        QString pulsebluetoothauto=proc.readAllStandardOutput();
        pulsebluetoothauto = pulsebluetoothauto.trimmed();
        if (pulsebluetoothauto == "enabled"){
            ui->checkBox_pulsebluetoothauto->setChecked(true);
        }
        else
        {
            ui->checkBox_pulsebluetoothauto->setChecked(false);
        }

        proc.start("/bin/bash", QStringList()<< "/usr/share/croco/scripts/check-lp.sh");
        proc.waitForFinished();
        QString lp=proc.readAllStandardOutput();
        lp = lp.trimmed();
        if (lp == "enabled"){
                 ui->checkBox_lp->setChecked(true);
        }
        else
        {
                 ui->checkBox_lp->setChecked(false);
        }

        proc.start("pacman -Qq alsa-support");
        proc.waitForFinished();
            QString alsa=proc.readAllStandardOutput();
            alsa = alsa.trimmed();
           // qDebug()<< alsa;
        if (alsa == "alsa-support"){
            ui->checkBox_alsa->setChecked(true);
        }
        else
        {
            ui->checkBox_alsa->setChecked(false);
        }

        proc.start("pacman -Qq jack-support");
        proc.waitForFinished();
            QString jack=proc.readAllStandardOutput();
            jack = jack.trimmed();
           // qDebug()<< jack;
        if (jack == "jack-support"){
            ui->checkBox_jack->setChecked(true);
        }
        else
        {
            ui->checkBox_jack->setChecked(false);
        }

        proc.start("pacman -Qq pulseaudio-support");
        proc.waitForFinished();
            QString pulseaudio=proc.readAllStandardOutput();
            pulseaudio = pulseaudio.trimmed();
           // qDebug()<< pulseaudio;
        if (pulseaudio == "pulseaudio-support"){
            ui->checkBox_pulseaudio->setChecked(true);
        }
        else
        {
            ui->checkBox_pulseaudio->setChecked(false);
        }

        proc.start("pacman -Qq pipewire-support");
        proc.waitForFinished();
            QString pipewire=proc.readAllStandardOutput();
            pipewire = pipewire.trimmed();
           // qDebug()<< pipewire;
        if (pipewire == "pipewire-support"){
            ui->checkBox_pipewire->setChecked(true);
        }
        else
        {
            ui->checkBox_pipewire->setChecked(false);
        }

        proc.start("pacman -Qq performance-tweaks");
        proc.waitForFinished();
            QString performancetweaks=proc.readAllStandardOutput();
            performancetweaks = performancetweaks.trimmed();
           // qDebug()<< performancetweaks
        if (performancetweaks == "performance-tweaks"){
            ui->checkBox_performancetweaks->setChecked(true);
        }
        else
        {
            ui->checkBox_pipewire->setChecked(false);
        }

        proc.start("/bin/bash", QStringList()<< "/usr/share/croco/scripts/check-realtime.sh");
        proc.waitForFinished();
        QString realtime=proc.readAllStandardOutput();
        realtime = realtime.trimmed();
        if (realtime == "enabled"){
                 ui->checkBox_realtime->setChecked(true);
        }
        else
        {
                 ui->checkBox_realtime->setChecked(false);
        }

}
/*######################################################################################
 *                                  Maintenance tab                                    *
######################################################################################*/

void CrocoAssistant::on_pushButton_reflector_clicked()
{
    this->hide();
        system("reflector-simple");
        this->show();
}

void CrocoAssistant::on_pushButton_sysup_clicked()
{
    this->hide();
        system("alacritty --command pkexec pacman -Syuu --noconfirm");
        this->show();
}

void CrocoAssistant::on_pushButton_orphans_clicked()
{
    this->hide();
        system("alacritty --command pkexec pacman -Rns $(pacman -Qtdq)");
        this->show();
}

void CrocoAssistant::on_pushButton_clrcache_clicked()
{
    this->hide();
        system("alacritty --command pkexec paccache -ruk 0");
        this->show();
}

void CrocoAssistant::on_pushButton_reinstall_clicked()
{
    this->hide();
        system("alacritty --command pkexec pacman -S $(pacman -Qnq)");
        this->show();
}

void CrocoAssistant::on_pushButton_dblck_clicked()
{
    this->hide();
        system("alacritty --command pkexec rm /var/lib/pacman/db.lck");
        this->show();
}

void CrocoAssistant::on_pushButton_editrepo_clicked()
{
    this->hide();
        system("pace");
        this->show();
}

void CrocoAssistant::on_pushButton_clrlogs_clicked()
{
    QProcess proc;
                proc.start("/bin/bash", QStringList()<< "/usr/share/croco/scripts/clear-cache.sh");
                proc.waitForFinished();
}

void CrocoAssistant::on_pushButton_clicked()
{
    system("cp -rf /etc/skel/. ~/");
}

/*######################################################################################
 *                                    BTRFS tab                                        *
######################################################################################*/






void CrocoAssistant::on_checkBoxFstrim_clicked(bool checked)
{
    if (checked)
       {
          system("systemctl enable --now fstrim.timer ");
       }
       else
       {
          system("systemctl disable --now fstrim.timer");
       }
       check_status();
       check_status();
}

void CrocoAssistant::on_checkBox_Scrub_clicked(bool checked)
{
    if (checked)
        {
           system("systemctl enable --now btrfs-scrub@-.timer ");
        }
        else
        {
           system("systemctl disable --now btrfs-scrub@-.timer");
        }
        check_status();
        check_status();
}

void CrocoAssistant::on_pushButton_balance_clicked()
{
    this->hide();
        system("alacritty --command pkexec btrfs balance start / --full-balance --verbose");
        this->show();
}

void CrocoAssistant::on_toolButton_diskRefresh_clicked()
{
    QProcess process;
        process.start("btrfs filesystem usage / ");
        process.waitForReadyRead();
        ui->textEdit->setText(process.readAll());
        process.waitForFinished();
}

/*######################################################################################
 *                           Settings tab                                              *
######################################################################################*/

void CrocoAssistant::on_checkBox_guest_clicked(bool checked)
{
    if (checked)
        {
            system("pamac-installer systemd-guest-user ");
        }
        else
        {
            system("pamac-installer --remove systemd-guest-user ");
        }
        check_status();
        check_status();
}

void CrocoAssistant::on_checkBox_adguard_clicked(bool checked)
{
    if (checked)
    {
        QProcess proc;
                proc.start("pkexec", QStringList()<< "/bin/bash" << "/usr/share/croco/scripts/adguard-on.sh");
                proc.waitForFinished();
    }
    else
    {
        QProcess proc;
                proc.start("pkexec", QStringList()<< "/bin/bash" << "/usr/share/croco/scripts/adguard-off.sh");
                proc.waitForFinished();
    }
    check_status();
    check_status();
}

void CrocoAssistant::on_checkBox_printer_clicked(bool checked)
{
    if (checked)
    {
        system("pamac-installer printer-support ");
    }
    else
    {
        system("pamac-installer --remove printer-support ");
    }
    check_status();
    check_status();
}

void CrocoAssistant::on_checkBox_cups_clicked(bool checked)
{
    if (checked)
    {
       system("systemctl enable --now cups.socket --now");
    }
    else
    {
       system("systemctl disable --now cups.socket");
    }
    check_status();
    check_status();
}

void CrocoAssistant::on_checkBox_scanning_clicked(bool checked)
{
    if (checked)
    {
        system("pamac-installer scanner-support ");
    }
    else
    {
        system("pamac-installer --remove scanner-support ");
    }
    check_status();
    check_status();
}

void CrocoAssistant::on_checkBox_usbipp_clicked(bool checked)
{
    if (checked)
    {
       system("systemctl enable --now ipp-usb ");
    }
    else
    {
       system("systemctl disable --now ipp-usb");
    }
    check_status();
    check_status();
}

void CrocoAssistant::on_checkBox_saned_clicked(bool checked)
{
    if (checked)
    {
       system("systemctl enable --now saned.socket");
    }
    else
    {
       system("systemctl disable --now saned.socket");
    }
    check_status();
    check_status();
}

void CrocoAssistant::on_checkBox_samba_clicked(bool checked)
{
    if (checked)
    {
        system("pamac-installer samba-support ");
    }
    else
    {
        system("pamac-installer --remove samba-support  ");
    }
    check_status();
    check_status();
}

void CrocoAssistant::on_checkBox_sambashare_clicked(bool checked)
{
    if (checked)
    {
       system("pkexec gpasswd sambashare -a $USER");
    }
    else
    {
       system("pkexec gpasswd sambashare -d $USER");
    }
    check_status();
    check_status();
}

void CrocoAssistant::on_checkBox_smb_clicked(bool checked)
{
    if (checked)
    {
       system("systemctl enable --now smb");
    }
    else
    {
       system("systemctl disable --now smb");
    }
    check_status();
    check_status();
}

void CrocoAssistant::on_checkBox_nmb_clicked(bool checked)
{
    if (checked)
    {
       system("systemctl enable --now nmb");
    }
    else
    {
       system("systemctl disable --now nmb");
    }
    check_status();
    check_status();
}

void CrocoAssistant::on_checkBox_firewalld_clicked(bool checked)
{
    if (checked)
    {
        system("pamac-installer firewalld python-pyqt5 ");
    }
    else
    {
        system("pamac-installer --remove firewalld python-pyqt5 ");
    }
    check_status();
    check_status();
}

void CrocoAssistant::on_checkBox_firewalldservice_clicked(bool checked)
{
    if (checked)
    {
       system("systemctl enable --now firewalld");
    }
    else
    {
       system("systemctl disable --now firewalld");
    }
    check_status();
    check_status();
}

void CrocoAssistant::on_checkBox_ufw_clicked(bool checked)
{
    if (checked)
    {
        system("pamac-installer gufw ");
    }
    else
    {
        system("pamac-installer --remove gufw  ");
    }
    check_status();
    check_status();
}

void CrocoAssistant::on_checkBox_ufwservice_clicked(bool checked)
{
    if (checked)
    {
       system("systemctl enable --now ufw");
    }
    else
    {
       system("systemctl disable --now ufw");
    }
    check_status();
    check_status();
}

void CrocoAssistant::on_checkBox_fcitx_clicked(bool checked)
{
    if (checked)
    {
        system("pamac-installer fcitx-input-support ");
    }
    else
    {
        system("pamac-installer --remove fcitx-input-support ");
    }
    check_status();
    check_status();
}

void CrocoAssistant::on_checkBox_fcitx5_clicked(bool checked)
{
    if (checked)
    {
        system("pamac-installer fcitx5-input-support ");
    }
    else
    {
        system("pamac-installer --remove fcitx5-input-support ");
    }
    check_status();
    check_status();
}

void CrocoAssistant::on_checkBox_ibus_clicked(bool checked)
{
    if (checked)
    {
        system("pamac-installer ibus-input-support ");
    }
    else
    {
        system("pamac-installer --remove ibus-input-support ");
    }
    check_status();
    check_status();
}

void CrocoAssistant::on_checkBox_asian_clicked(bool checked)
{
    if (checked)
    {
        system("pamac-installer asian-fonts ");
    }
    else
    {
        system("pamac-installer --remove asian-fonts ");
    }
    check_status();
    check_status();
}

void CrocoAssistant::on_checkBox_lptrce_clicked(bool checked)
{
    if (checked)
    {
        system("pamac-installer evdev-right-click-emulation ");
    }
    else
    {
        system("pamac-installer --remove evdev-right-click-emulation ");
    }
    check_status();
    check_status();
}

void CrocoAssistant::on_checkBox_evdevrce_clicked(bool checked)
{
    if (checked)
    {
       system("systemctl enable --now evdev-rce");
    }
    else
    {
       system("systemctl disable --now evdec-rce");
    }
    check_status();
    check_status();
}

void CrocoAssistant::on_checkBox_virtmanager_clicked(bool checked)
{
    if (checked)
    {
        system("pamac-installer virt-manager-meta ");
    }
    else
    {
        system("pamac-installer --remove virt-manager-meta ");
    }
    check_status();
    check_status();
}

void CrocoAssistant::on_checkBox_libvirtd_clicked(bool checked)
{
    if (checked)
    {
       system("systemctl enable --now libvirtd");
    }
    else
    {
       system("systemctl disable --now libvirtd");
    }
    check_status();
    check_status();
}

void CrocoAssistant::on_checkBox_libvirtgrp_clicked(bool checked)
{
    if (checked)
    {
       system("pkexec gpasswd libvirt -a $USER");
    }
    else
    {
       system("pkexec gpasswd libvirt -d $USER");
    }
    check_status();
    check_status();

}

void CrocoAssistant::on_checkBox_virtualbox_clicked(bool checked)
{
    if (checked)
    {
        system("pamac-installer virtualbox-meta ");
    }
    else
    {
        system("pamac-installer --remove virtualbox-meta ");
    }
    check_status();
    check_status();
}

void CrocoAssistant::on_checkBox_vboxusers_clicked(bool checked)
{
    if (checked)
    {
       system("pkexec gpasswd vboxusers -a $USER");
    }
    else
    {
       system("pkexec gpasswd vboxusers -d $USER");
    }
    check_status();
    check_status();
}

void CrocoAssistant::on_checkBox_hidpi_clicked(bool checked)
{
    if (checked)
    {
        system("alacritty --command pkexec env DISPLAY=$DISPLAY XAUTHORITY=$XAUTHORITY /usr/share/croco/scripts/hidpi-on.sh");
        system("notify-send -i 'croco' 'Hidpi-on' 'Changes made.Reboot system for changes to take effect to take effect'");
    }
    else
    {
        system("alacritty --command pkexec env DISPLAY=$DISPLAY XAUTHORITY=$XAUTHORITY /usr/share/croco/scripts/hidpi-off.sh");
        system("notify-send -i 'croco' 'Hidpi-off' 'Changes made.Reboot system for changes to take effect to take effect'");
    }
    check_status();
    check_status();
}

void CrocoAssistant::on_checkBox_gdm_clicked(bool checked)
{
    if (checked)
    {
        QProcess proc;
                proc.start("pkexec", QStringList()<< "/bin/bash" << "/usr/share/croco/scripts/gdmwayland-on.sh");
                proc.waitForFinished();
    }
    else
    {
        QProcess proc;
                proc.start("pkexec", QStringList()<< "/bin/bash" << "/usr/share/croco/scripts/gdmwayland-off.sh");
                proc.waitForFinished();
    }
    check_status();
    check_status();
}

void CrocoAssistant::on_checkBox_modemservice_clicked(bool checked)
{
    if (checked)
    {
       system("systemctl enable --now ModemManager");
    }
    else
    {
       system("systemctl disable --now ModemManager");
    }
    check_status();
    check_status();
}

void CrocoAssistant::on_checkBox_gpsd_clicked(bool checked)
{
    if (checked)
    {
       system("systemctl enable --now gpsd");
    }
    else
    {
       system("systemctl disable --now gpsd");
    }
    check_status();
    check_status();
}

void CrocoAssistant::on_checkBox_bluetooth_clicked(bool checked)
{
    if (checked)
    {
        system("pamac-installer bluetooth-support ");
    }
    else
    {
        system("pamac-installer --remove bluetooth-support ");
    }
    check_status();
    check_status();

}

void CrocoAssistant::on_checkBox_bluetoothservice_clicked(bool checked)
{
    if (checked)
    {
       system("systemctl enable --now bluetooth");
    }
    else
    {
       system("systemctl disable --now bluetooth");
    }
    check_status();
    check_status();
}

void CrocoAssistant::on_checkBox_bluetoothauto_clicked(bool checked)
{
    if (checked)
    {
       system("systemctl enable --now bluetooth-autoconnect ");
    }
    else
    {
       system("systemctl disable --now bluetooth-autoconnect");
    }
    check_status();
    check_status();
}

void CrocoAssistant::on_checkBox_pulsebluetoothauto_clicked(bool checked)
{
    if (checked)
    {
       system("systemctl enable pulseaudio-bluetooth-autoconnect --user --now");
    }
    else
    {
       system("systemctl disable pulseaudio-bluetooth-autoconnect --user");
    }
    check_status();
    check_status();
}



void CrocoAssistant::on_checkBox_gstreamer_clicked(bool checked)
{
    if (checked)
    {
        system("pamac-installer gstreamer-meta ");
    }
    else
    {
        system("pamac-installer --remove gstreamer-meta ");
    }
    check_status();
    check_status();
}

void CrocoAssistant::on_checkBox_network_clicked(bool checked)
{
    if (checked)
    {
        system("pamac-installer networkmanager-support ");
    }
    else
    {
        system("pamac-installer --remove networkmanager-support ");
    }
    check_status();
    check_status();
}

void CrocoAssistant::on_checkBox_networkservice_clicked(bool checked)
{
    if (checked)
    {
       system("systemctl enable --now --force NetworkManager");
    }
    else
    {
       system("systemctl disable --now NetworkManager");
    }
    check_status();
    check_status();
}

void CrocoAssistant::on_checkBox_connman_clicked(bool checked)
{
    if (checked)
    {
        system("pamac-installer connman-support ");
    }
    else
    {
        system("pamac-installer --remove connman-support ");
    }
    check_status();
    check_status();
}

void CrocoAssistant::on_checkBox_connmanservice_clicked(bool checked)
{
    if (checked)
    {
       system("systemctl enable --force --now connman ");
    }
    else
    {
       system("systemctl disable connman");
    }
    check_status();
    check_status();
}

void CrocoAssistant::on_checkBox_modemmanager_clicked(bool checked)
{
    if (checked)
    {
       system("systemctl enable --force --now ModemManager");
    }
    else
    {
       system("systemctl disable --now ModenManager");
    }
    check_status();
    check_status();
}

void CrocoAssistant::on_checkBox_ofono_clicked(bool checked)
{
    if (checked)
    {
       system("systemctl enable --force --now ofono");
    }
    else
    {
       system("systemctl disable --now ofono");
    }
    check_status();
    check_status();
}

void CrocoAssistant::on_checkBox_neard_clicked(bool checked)
{
    if (checked)
    {
       system("systemctl enable --force --now neard");
    }
    else
    {
       system("systemctl disable --now neard");
    }
    check_status();
    check_status();
}


void CrocoAssistant::on_checkBox_hblock_clicked(bool checked)
{
    if (checked)
    {
        QProcess proc;
                proc.start("/bin/bash", QStringList()<< "/usr/share/croco/scripts/hblock-on.sh");
                proc.waitForFinished();
    }
    else
    {
        QProcess proc;
                proc.start("pkexec", QStringList()<< "hblock -S none && rm -f /etc/hosts.noad");
                proc.waitForFinished();
    }
    check_status();
    check_status();
}

void CrocoAssistant::on_checkBox_alsa_clicked(bool checked)
{
    if (checked)
    {
        system("pamac-installer alsa-support ");
    }
    else
    {
        system("pamac-installer --remove alsa-support ");
    }
    check_status();
    check_status();
}

void CrocoAssistant::on_checkBox_jack_clicked(bool checked)
{
    if (checked)
    {
        system("pamac-installer jack-support ");
    }
    else
    {
        system("pamac-installer --remove jack-support ");
    }
    check_status();
    check_status();
}

void CrocoAssistant::on_checkBox_pulseaudio_clicked(bool checked)
{
    if (checked)
    {
        system("pamac-installer pulseaudio-support ");
    }
    else
    {
        system("pamac-installer --remove pulseaudio-support ");
    }
    check_status();
    check_status();
}

void CrocoAssistant::on_checkBox_pipewire_clicked(bool checked)
{
    if (checked)
    {
        system("pamac-installer pipewire-support ");
    }
    else
    {
        system("pamac-installer --remove pipewire-support ");
    }
    check_status();
    check_status();
}

void CrocoAssistant::on_checkBox_lp_clicked(bool checked)
{
    if (checked)
    {
       system("pkexec gpasswd lp -a $USER");
    }
    else
    {
       system("pkexec gpasswd lp -d $USER");
    }
    check_status();
    check_status();
}

void CrocoAssistant::on_checkBox_cupsgrp_clicked(bool checked)
{
    if (checked)
    {
       system("pkexec gpasswd cups -a $USER");
    }
    else
    {
       system("pkexec gpasswd cups -d $USER");
    }
    check_status();
    check_status();
}

void CrocoAssistant::on_checkBox_video_clicked(bool checked)
{
    if (checked)
    {
       system("pkexec gpasswd video -a $USER");
    }
    else
    {
       system("pkexec gpasswd video -d $USER");
    }
    check_status();
    check_status();
}

void CrocoAssistant::on_checkBox_realtime_clicked(bool checked)
{
    if (checked)
    {
       system("pkexec gpasswd realtime -a $USER");
    }
    else
    {
       system("pkexec gpasswd realtime -d $USER");
    }
    check_status();
    check_status();
}



void CrocoAssistant::on_checkBox_performancetweaks_clicked(bool checked)
{
    if (checked)
    {
        system("pamac-installer performance-tweaks ");
    }
    else
    {
        system("pamac-installer --remove performance-tweaks ");
    }
    check_status();
    check_status();
}


void CrocoAssistant::on_checkBox_sysgrp_clicked(bool checked)
{
    if (checked)
    {
       system("pkexec gpasswd sys -a $USER");
    }
    else
    {
       system("pkexec gpasswd sys -d $USER");
    }
    check_status();
    check_status();
}

void CrocoAssistant::on_checkBox_scannergrp_clicked(bool checked)
{
    if (checked)
    {
       system("pkexec gpasswd scanner -a $USER");
    }
    else
    {
       system("pkexec gpasswd scanner -d $USER");
    }
    check_status();
    check_status();
}
