#include "worker.h"

Worker::Worker(QObject *parent, int id) : QThread{parent}
{
    worker_id = id;
    if (open_env_file()) {
        qInfo(log_Worker()) << "env file error: " << path_for_build_directory;  //  - > path_for_build_directory = path_directory
    }
    str_worker_id = QString::number(worker_id);
    mac_script_path = path_for_build_directory + QString("mac_script.sh");
    // mac_script_path = "/Users/polzovatel/work/aqsi_proj/TerminalInstallerApp/installerAppForMac_0.1/installerApp/build/mac_script.sh";
    mac_address_file_path = path_for_build_directory + QString("mac_address_") + str_worker_id + QString(".txt");
    // mac_address_file_path = QString("/Users/polzovatel/work/aqsi_proj/TerminalInstallerApp/installerAppForMac_0.1/installerApp/build/mac_address_") + str_worker_id + QString(".txt");
    old_mac_address = "";
    new_mac_address = "";

    qInfo(log_Worker()) << "id:" << worker_id << ":" << "Create worker";

    current_IP = "";
    MAC_address = "";
    current_Role = "";
    current_CycleInstallFlag = false;

    script_path = "";
    archive_path = "";
    workflow_path = "";
    main_path = QDir::currentPath();

    miscdir = "";
    password = "";

    progress_status = 0;

    qInfo(log_Worker()) << "id:" << worker_id << ":" << "Create installer process";
    installer = new QProcess(this);
    qInfo(log_Worker()) << "id:" << worker_id << ":" << "Create ping process";
    ping = new QProcess(this);

    term = false;

    connect(installer, &QProcess::readyReadStandardOutput, this, &Worker::read_InstallerOutput);
    connect(installer, &QProcess::readyReadStandardError, this, &Worker::read_InstallerError);

    connect(installer, &QProcess::readyReadStandardOutput, this, &Worker::iterate_Progress);
    connect(installer, &QProcess::readyReadStandardError, this, &Worker::iterate_Progress);
}

Worker::~Worker()
{
    disconnect(installer, &QProcess::readyReadStandardOutput, this, &Worker::read_InstallerOutput);
    disconnect(installer, &QProcess::readyReadStandardError, this, &Worker::read_InstallerError);

    disconnect(installer, &QProcess::readyReadStandardOutput, this, &Worker::iterate_Progress);
    disconnect(installer, &QProcess::readyReadStandardError, this, &Worker::iterate_Progress);

    delete installer;
    delete ping;
}

void Worker::run()
{
    progress_status = 0;
    emit ProgressChanged(progress_status);

    term = false;

    int err = check_Parameters();
    if(err != 0)
    {
        qCritical(log_Worker()) << "id:" << worker_id << ":" << "Stop thread with error code " << err;
        term = true;
        emit FullInstall_finished();
        return;
    }
    arguments.clear();
    arguments << "--ip=" + current_IP;
    // arguments << "--role=" + current_Role.toLower();
    trimming_the_path_to_the_file();
    arguments << "--pkg=" + archive_path;
    // arguments << "--miscdir=" + miscdir;
    if(password != "") arguments << "--password=" + password;

    qDebug(log_Worker()) << "id:" << worker_id << ":" << "Set dir " << workflow_path;
    bool ch_dir_error = QDir::setCurrent(workflow_path);

    if(!ch_dir_error)
    {
        qCritical(log_Worker()) << "id:" << worker_id << ":" << "Crash installer process, can't change dir!";
        term = true;
        emit FullInstall_finished();
        return;
    }

    do
    {
        pre_ping();

        emit OneInstall_started();

        qInfo(log_Worker()) << "id:" << worker_id << ":" << "Current dir: " << QDir::currentPath();
        qInfo(log_Worker()) << "id:" << worker_id << ":" << "Run install script " << script_path << "with args: " << arguments;
        qDebug(log_Worker()) << "id:" << worker_id << ":" << "Command: " << script_path + " " + arguments.join(" ");

        installer->execute("bash", (QStringList() << script_path) << arguments);
        installer->waitForFinished(600000);
        err = installer->exitStatus();

        qDebug(log_Worker()) << "id:" << worker_id << ":" << "Exit Status " << err;
        qDebug(log_Worker()) << "id:" << worker_id << ":" << "Exit Code " << installer->exitCode();
        qDebug(log_Worker()) << "id:" << worker_id << ":" << "Normal situation is Status = 0 Code = 0";

        if(err != QProcess::NormalExit)
        {
            qCritical(log_Worker()) << "id:" << worker_id << ":" << "Crash installer process";
            term = true;
            emit FullInstall_finished();

            qDebug(log_Worker()) << "id:" << worker_id << ":" << "Set dir " << main_path;
            QDir::setCurrent(main_path);
            return;
        }
        if(installer->exitCode() != 0)
        {
            qCritical(log_Worker()) << "id:" << worker_id << ":" << "Exit code " << installer->exitCode();

            term = true;
            emit FullInstall_finished();

            qDebug(log_Worker()) << "id:" << worker_id << ":" << "Set dir " << main_path;
            QDir::setCurrent(main_path);
            return;
        }

        qInfo(log_Worker()) << "id:" << worker_id << ":" << "Install script finished";

#ifdef NDEBUG
        after_ping();
#endif

        emit OneInstall_finished();

        sleep(1);
    }
    while(current_CycleInstallFlag);

    old_mac_address = "";

    qInfo(log_Worker()) << "id:" << worker_id << ":" << "Full Install script finished";

    qDebug(log_Worker()) << "id:" << worker_id << ":" << "Set dir " << main_path;
    QDir::setCurrent(main_path);

    emit FullInstall_finished();
}

void Worker::stop()
{
    installer->kill();

    qInfo(log_Worker()) << "id:" << worker_id << ":" << "Install script terminated";

    qDebug(log_Worker()) << "id:" << worker_id << ":" << "Set dir " << main_path;
    QDir::setCurrent(main_path);

    term = true;

    this->terminate();
}

void Worker::read_InstallerOutput()
{
    qInfo(log_Worker()) << "id:" << worker_id << ":" << "Installer output: " << QString(installer->readAllStandardOutput());
}

void Worker::read_InstallerError()
{
    qInfo(log_Worker()) << "id:" << worker_id << ":" << "Installer error: " << QString(installer->readAllStandardError());
}

void Worker::iterate_Progress()
{
    progress_status++;
    if(progress_status > 100)
    {
        progress_status = 0;
    }

    emit ProgressChanged(progress_status);
}

void Worker::set_IP(QString ip)
{
    current_IP = ip;
}

void Worker::set_Role(QString role)
{
    current_Role = role;
}

void Worker::set_CycleInstallFlag(bool flag)
{
    current_CycleInstallFlag = flag;
}

void Worker::set_script_path(QString path)
{
    QStringList tmp = path.split("/");
    tmp.removeLast();
    workflow_path = tmp.join("/");
    script_path = "./" + path.split("/").last();

    qDebug() << "workflow: " << workflow_path;
    qDebug() << "script: " << script_path;
}

void Worker::set_archive_path(QString path)
{
    archive_path = path;
}

void Worker::set_miscdir(QString path)
{
    miscdir = path;
}

void Worker::set_password(QString password)
{
    this->password = password;
}

void Worker::set_WaitIP(QString ip)
{
    wait_IP = ip;
}

int Worker::check_Parameters()
{
    int return_value = 0;
    if(current_IP == "")
    {
        qCritical(log_Worker()) << "id:" << worker_id << ":" << "Ip adress isn't set!";
        return_value+=1;
    }
    if((current_Role == "") | (current_Role.toLower() == "none"))
    {
        qCritical(log_Worker()) << "id:" << worker_id << ":" << "Role isn't set!";
        return_value+=2;
    }
    if(current_CycleInstallFlag == false)
    {
        qInfo(log_Worker()) << "id:" << worker_id << ":" << "Cycle Install Flag is false";
    }
    if(script_path == "")
    {
        qCritical(log_Worker()) << "id:" << worker_id << ":" << "Script path isn't set!";
        return_value+=4;
    }
    if(archive_path == "")
    {
        qCritical(log_Worker()) << "id:" << worker_id << ":" << "Archive path isn't set!";
        return_value+=8;
    }
    if(miscdir == "")
    {
        qCritical(log_Worker()) << "id:" << worker_id << ":" << "Miscdir path isn't set!";
        return_value+=16;
    }
    if(password == "")
    {
        qWarning(log_Worker()) << "id:" << worker_id << ":" << "Password isn't set!";
    }
    return return_value;
}

void Worker::pre_ping()
{
    ping_args.clear();
    ping_args << "-c1" << "-W1" << current_IP;

    qInfo(log_Worker()) << "id:" << worker_id << ":" << "Pre ping " << current_IP;

    int i = 0;
    int result_MAC_address_comparison = 0;
    do
    {
        i = ping->execute("ping", ping_args);
        if (i == 0) {
            result_MAC_address_comparison = waiting_new_mac_address();
            if (result_MAC_address_comparison == 2) qInfo(log_Worker()) << "id:" << worker_id << ":" << " Waiting for a new MAC-address";
            else if (result_MAC_address_comparison == 1) qInfo(log_Worker()) << "id:" << worker_id << ":" << " pre_ping - Error reading file";
        }
        qInfo(log_Worker()) << "id:" << worker_id << ":" << "Try ping ";
        qInfo(log_Worker()) << "id:" << worker_id << ":" << "i = " << i << " result_MAC_address_comparison = " << result_MAC_address_comparison;
    }
    while (i != 0 || result_MAC_address_comparison != 0);
    qInfo(log_Worker()) << "id:" << worker_id << ":" << "End ping ";
}

void Worker::after_ping()
{
    ping_args.clear();
    ping_args << "-c1" << "-W1" << wait_IP;

    qInfo(log_Worker()) << "id:" << worker_id << ":" << "After ping " << current_IP;

    int i = 0;
    do
    {
        
        i = ping->execute("ping", ping_args);
        qInfo(log_Worker()) << "id:" << worker_id << ":" << "Try ping ";
    }
    while(i != 0);
    qInfo(log_Worker()) << "id:" << worker_id << ":" << "End ping ";
}

void Worker::trimming_the_path_to_the_file() {
    archive_path = QFileInfo(archive_path).fileName();
    qInfo(log_Worker()) << "id:" << worker_id << ":" << "The archive_path has been changed to:" << archive_path;
}

int Worker::waiting_new_mac_address() {
    
    installer->execute("bash", {mac_script_path, current_IP, QString::number(worker_id)});
    sleep(2);
    QFile file(mac_address_file_path);
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray data;
        data = file.readLine();
        new_mac_address = QString(data);
        file.close();
    } else {
        qDebug(log_Worker()) << "id:" << worker_id << ":" << "File: '" << mac_address_file_path << "' not open.";
        qDebug(log_Worker()) << "id:" << worker_id << ":" << "Error: " << file.error(); 
        return 1;
    }
    if (old_mac_address != new_mac_address) {
        old_mac_address = new_mac_address;
        qInfo(log_Worker()) << "id:" << worker_id << ":" << " New MAC address - " << new_mac_address;
        qInfo(log_Worker()) << "id:" << worker_id << ":" << " The new MAC-address is really new.";
        return 0;
    } else {
        qInfo(log_Worker()) << "id:" << worker_id << ":" << " New MAC address is not new- " << new_mac_address;
        return 2;
    }
}

int Worker::open_env_file(){
    QFile env_file("../env.txt");
    if (env_file.open(QIODevice::ReadOnly)) {
        QByteArray data_env_file;
        data_env_file = env_file.readLine();
        path_for_build_directory = QString(data_env_file);
        env_file.close();
        return 0;
    } else {
        return 1;
    }
}