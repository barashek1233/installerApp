#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDebug>

#include "loger.h"
#include "config.h"
#include "worker.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Config *config_window;

    Worker *worker_A;
    Worker *worker_B;
    Worker *worker_C;
    Worker *worker_D;

    QString path_archive = "";
    QString path_script = "";

    QString path_config = "";
    QString export_path_config = "";

    QStringList role_list;
    QStringList config_name_list;

    QString install_password = "";

    QString master_files = "";
    QString slave_files = "";

    QString current_IP_A = "";
    QString current_IP_B = "";
    QString current_IP_C = "";
    QString current_IP_D = "";

    QString current_Role_A = "";
    QString current_Role_B = "";
    QString current_Role_C = "";
    QString current_Role_D = "";

    bool current_CycleInstallFlag_A = false;
    bool current_CycleInstallFlag_B = false;
    bool current_CycleInstallFlag_C = false;
    bool current_CycleInstallFlag_D = false;

private slots:
    void start_Worker(PortNames port_name);
    void stop_Worker(PortNames port_name);

    void finished_Worker(PortNames port_name, bool finish_one);

    void import_Config();
    void export_Config();

    void update_ArchivePathLabel(QString path);
    void update_ScriptPathLabel(QString path);

    void update_MasterFiles(QString path);
    void update_SlaveFiles(QString path);

    void update_InstallPassword();

    void update_PortIPs();
    void update_PortRoles();
    void update_PortCycleInstall();

    void update_Roles();
    /// @brief Обновление и добавление всех доступных имен кофига в mainwindow
    void update_Config_Name();
    void update_IPs(PortNames port_name, QString ip);

    void clear_SameRole(PortNames port_name);

};
#endif // MAINWINDOW_H
