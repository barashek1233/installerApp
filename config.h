#ifndef CONFIG_H
#define CONFIG_H

#include <QDialog>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <QStandardPaths>

#include "loger.h"
#include "parser.h"

enum PortNames
{
    Port_A,
    Port_B,
    Port_C,
    Port_D
};

namespace Ui {
class Config;
}

class Config : public QDialog
{
    Q_OBJECT

public:
    explicit Config(QWidget *parent = nullptr);
    ~Config();

    bool readConfigFile();

    QString get_ScriptPath();
    QString get_ArchivePath();

    QString get_MasterFiles();
    QString get_SlaveFiles();

    QString get_InstallPassword();

    QString get_PortIP(PortNames port_name);
    QString get_PortRole(PortNames port_name);
    bool get_PortCycleInstall(PortNames port_name);

    QStringList get_Roles();
    QStringList get_config_name();

    QString get_RoleWaitIP(QString role);

signals:
    void scriptPath_updated(QString path);
    void archivePath_updated(QString path);

    void portIPs_updated();
    void portRoles_updated();
    void portCycleInstalls_updated();

    void rolesList_updated();
    void ipList_updated();

    void masterFiles_updated(QString path);
    void slaveFiles_updated(QString path);

    void installPassword_updated();

    void parse_Started();
    void parse_Finished();

public slots:
    void parse_Archive();
    void import_Config(QString path);
    void export_Config(QString path);
    void set_MainPath(QString path);

private slots:
    void update_AfterParse();

    void set_ConfigPath(QString path);

    void set_ArchivePath(bool ch);
    void set_ScriptPath(bool ch);

    void set_MasterFiles(bool ch);
    void set_SlaveFiles(bool ch);

    bool saveEditConfigFile();
    void cancelEditConfigFile();

    void change_InstallPassword(QString password);

    void change_PortIP(PortNames port_name, QString new_ip);
    void change_PortRole(PortNames port_name, QString new_role);
    void change_PortCycleInstall(PortNames port_name, bool new_check);

    void clear_SameRole(PortNames port_name);

private:
    void update_SettingsValues();

    void create_NewConfigFile();

    Ui::Config *ui;

    QJsonObject     config_data;
    QJsonObject     config_data_sample;  //  Для именования конфигов
    QJsonDocument   config_doc;
    QFile           config_file;
    QString         config_path;

    QJsonValue      install_script_path;
    QJsonValue      install_archive_path;

    QJsonValue      master_files;
    QJsonValue      slave_files;

    QJsonValue      install_password;

    QJsonArray      DHCP_IP_List;
    QJsonArray      Roles;
    QJsonArray      Config_Names;
    QJsonObject     Roles_IP_List;

    QJsonArray      StartIPs;
    QJsonArray      StartRoles;
    QJsonArray      StartCycleInstallValue;

    Parser parser;
};

#endif // CONFIG_H
