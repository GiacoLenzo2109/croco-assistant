#ifndef CROCOASSISTANT_H
#define CROCOASSISTANT_H

#include <QMainWindow>
#include <QMessageBox>
#include <QProcess>

QT_BEGIN_NAMESPACE
namespace Ui { class CrocoAssistant; }
QT_END_NAMESPACE

struct Result {
    int exitCode;
    QString output;
};

class CrocoAssistant : public QMainWindow
{
    Q_OBJECT

protected:
    QProcess *proc;

public:
    explicit CrocoAssistant(QWidget *parent = 0);
    ~CrocoAssistant();

    Result runCmd(QString cmd);
    QString getVersion(QString name);

    QString version;
    QString output;

    void setup();

public slots:
    void setConnections();
    void disconnectAll();


private slots:

    void check_status();

    void on_pushButton_reflector_clicked();

    void on_pushButton_sysup_clicked();

    void on_pushButton_orphans_clicked();

    void on_pushButton_clrcache_clicked();

    void on_pushButton_reinstall_clicked();

    void on_pushButton_dblck_clicked();

    void on_pushButton_editrepo_clicked();

    void on_pushButton_clrlogs_clicked();

    void on_pushButton_clicked();

    void on_checkBox_guest_clicked(bool checked);

    void on_checkBox_adguard_clicked(bool checked);

    void on_checkBox_printer_clicked(bool checked);

    void on_checkBox_cups_clicked(bool checked);

    void on_checkBox_scanning_clicked(bool checked);

    void on_checkBox_usbipp_clicked(bool checked);

    void on_checkBox_saned_clicked(bool checked);

    void on_checkBox_samba_clicked(bool checked);

    void on_checkBox_smb_clicked(bool checked);

    void on_checkBox_sambashare_clicked(bool checked);

    void on_checkBox_nmb_clicked(bool checked);

    void on_checkBox_firewalld_clicked(bool checked);

    void on_checkBox_firewalldservice_clicked(bool checked);

    void on_checkBox_ufw_clicked(bool checked);

    void on_checkBox_ufwservice_clicked(bool checked);

    void on_checkBox_fcitx_clicked(bool checked);

    void on_checkBox_ibus_clicked(bool checked);

    void on_checkBox_asian_clicked(bool checked);

    void on_checkBox_lptrce_clicked(bool checked);

    void on_checkBox_evdevrce_clicked(bool checked);

    void on_checkBox_virtmanager_clicked(bool checked);

    void on_checkBox_libvirtd_clicked(bool checked);

    void on_checkBox_libvirtgrp_clicked(bool checked);

    void on_checkBox_virtualbox_clicked(bool checked);

    void on_checkBox_vboxusers_clicked(bool checked);

    void on_checkBox_hidpi_clicked(bool checked);

    void on_checkBox_gdm_clicked(bool checked);

    void on_checkBoxFstrim_clicked(bool checked);

    void on_checkBox_Scrub_clicked(bool checked);

    void on_pushButton_balance_clicked();

    void on_toolButton_diskRefresh_clicked();

    void on_checkBox_modemservice_clicked(bool checked);

    void on_checkBox_gpsd_clicked(bool checked);

    void on_checkBox_bluetooth_clicked(bool checked);

    void on_checkBox_bluetoothservice_clicked(bool checked);

    void on_checkBox_bluetoothauto_clicked(bool checked);

    void on_checkBox_pulsebluetoothauto_clicked(bool checked);

    void on_checkBox_gstreamer_clicked(bool checked);

    void on_checkBox_network_clicked(bool checked);

    void on_checkBox_networkservice_clicked(bool checked);

    void on_checkBox_connman_clicked(bool checked);

    void on_checkBox_connmanservice_clicked(bool checked);

    void on_checkBox_modemmanager_clicked(bool checked);

    void on_checkBox_ofono_clicked(bool checked);

    void on_checkBox_neard_clicked(bool checked);

    void on_checkBox_hblock_clicked(bool checked);

    void on_checkBox_fcitx5_clicked(bool checked);

    void on_checkBox_alsa_clicked(bool checked);

    void on_checkBox_jack_clicked(bool checked);

    void on_checkBox_pipewire_clicked(bool checked);

    void on_checkBox_lp_clicked(bool checked);

    void on_checkBox_cupsgrp_clicked(bool checked);

    void on_checkBox_video_clicked(bool checked);

    void on_checkBox_realtime_clicked(bool checked);

    void on_checkBox_pulseaudio_clicked(bool checked);

    void on_checkBox_performancetweaks_clicked(bool checked);

    void on_checkBox_sysgrp_clicked(bool checked);

    void on_checkBox_scannergrp_clicked(bool checked);

private:
    Ui::CrocoAssistant *ui;
};
#endif // CROCOASSISTANT_H
