#ifndef WORKER_H
#define WORKER_H

#include <QThread>
#include <QProcess>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QFшle>
#include <QByteArray>

#include "loger.h"

class Worker : public QThread
{
    Q_OBJECT

public:
    explicit Worker(QObject *parent = nullptr, int id = 0);
    ~Worker();

    void run();

    void set_IP(QString ip);
    void set_Role(QString role);
    void set_CycleInstallFlag(bool flag);
    void set_script_path(QString path);
    void set_archive_path(QString path);
    void set_miscdir(QString path);
    void set_password(QString password);
    void set_WaitIP(QString ip);

    bool term;

signals:
    void OneInstall_started();
    void OneInstall_finished();
    void FullInstall_finished();

    void ProgressChanged(int status);

public slots:
    void stop();

private slots:
    void read_InstallerOutput();
    void read_InstallerError();
    void iterate_Progress();

private:
    int worker_id;
    void trimming_the_path_to_the_file();
    int check_Parameters();
    void pre_ping();
    void after_ping();

    /// @brief запускает скрипт получения мак адреса устрйоства по ip воркера, проверяет что MAC-адрес текущего устрйоства не равен MAC-адресу предыдущего устройства устройства, стиот после завершения цикла установки присвоит переменной хранящей старый MAC-адрес путую строку
    /// @returns 0 - OK; 1 - ошибка чтения файла; 2 - MAC-адрес текущего устройства совпадает с MAC-адресом предыдущего устройства в данном процессе;
    int waiting_new_mac_address();

    QString str_worker_id;
    QString mac_file_path;
    QString mac_address_file_path;
    QString old_mac_address;
    QString new_mac_address;
    QString mac_script_path;

    QString     current_IP;
    QString     MAC_address;
    QString     current_Role;
    bool        current_CycleInstallFlag;

    QString     wait_IP;

    QString     script_path;
    QString     archive_path;
    QString     workflow_path;
    QString     main_path;

    QString     miscdir;
    QString     password;

    QProcess    *check_mac_address;
    QProcess    *installer;
    QStringList arguments;

    QProcess    *ping;
    QStringList ping_args;

    int         progress_status;
};

#endif // WORKER_H
