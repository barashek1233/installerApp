#ifndef WORKER_H
#define WORKER_H

#include <QThread>
#include <QProcess>
#include <QDebug>
#include <QDir>

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

    int check_Parameters();
    void pre_ping();
    void after_ping();

    QString     current_IP;
    QString     current_Role;
    bool        current_CycleInstallFlag;

    QString     wait_IP;

    QString     script_path;
    QString     archive_path;
    QString     workflow_path;
    QString     main_path;

    QString     miscdir;
    QString     password;

    QProcess    *installer;
    QStringList arguments;

    QProcess    *ping;
    QStringList ping_args;

    int         progress_status;
};

#endif // WORKER_H
