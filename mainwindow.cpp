#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    qInfo(log_Main()) << "Create MainWindow";

    ui->setupUi(this);

    config_window = new Config();

    // config_window->set_ProgramPath(QDir::currentPath());

    qInfo(log_Main()) << "Get saved config data";
    path_archive = config_window->get_ArchivePath();
    path_script = config_window->get_ScriptPath();

    update_ArchivePathLabel(path_archive);
    update_ScriptPathLabel(path_script);

    master_files = config_window->get_MasterFiles();
    slave_files = config_window->get_SlaveFiles();

    install_password = config_window->get_InstallPassword();

    update_Roles();
    update_Config_Name();  //   Добавить метод для обновления конфиг нейма по аналогии с update_Roles()
    update_PortRoles();
    update_PortIPs();
    update_PortCycleInstall();

    qInfo(log_Main()) << "Create Worker 0";
    worker_A = new Worker(this, Port_A);
    qInfo(log_Main()) << "Create Worker 1";
    worker_B = new Worker(this, Port_B);
    qInfo(log_Main()) << "Create Worker 2";
    worker_C = new Worker(this, Port_C);
    qInfo(log_Main()) << "Create Worker 3";
    worker_D = new Worker(this, Port_D);

    connect(ui->action_edit, &QAction::triggered, config_window, &Config::exec);
    connect(ui->action_parse_archive_2, &QAction::triggered, config_window, &Config::parse_Archive);
    connect(ui->action_import, &QAction::triggered, this, &MainWindow::import_Config);
    connect(ui->action_export, &QAction::triggered, this, &MainWindow::export_Config);

    connect(config_window, &Config::scriptPath_updated, this, &MainWindow::update_ScriptPathLabel);
    connect(config_window, &Config::archivePath_updated, this, &MainWindow::update_ArchivePathLabel);

    connect(config_window, &Config::portRoles_updated, this, &MainWindow::update_PortRoles);
    connect(config_window, &Config::portIPs_updated, this, &MainWindow::update_PortIPs);
    connect(config_window, &Config::portCycleInstalls_updated, this, &MainWindow::update_PortCycleInstall);
    //  добавить сигнал и соеденить для обновления имен конфига и далее
    
    connect(config_window, &Config::rolesList_updated, this, &MainWindow::update_Roles);
    connect(config_window, &Config::config_name_update, this, &MainWindow::update_Config_Name);
    connect(config_window, &Config::masterFiles_updated, this, &MainWindow::update_MasterFiles);
    connect(config_window, &Config::slaveFiles_updated, this, &MainWindow::update_SlaveFiles);

    connect(config_window, &Config::installPassword_updated, this, &MainWindow::update_InstallPassword);

    //  вызов метода update_config_name_in_main_window для обновления конфигурационного файла
    connect(ui->comboBox, &QComboBox::currentTextChanged, this, &MainWindow::update_config_name_in_main_window);
    

    connect(ui->gb_1_comb, &QComboBox::currentTextChanged, this, [=](QString value){clear_SameRole(Port_A);});
    connect(ui->gb_2_comb, &QComboBox::currentTextChanged, this, [=](QString value){clear_SameRole(Port_B);});
    connect(ui->gb_3_comb, &QComboBox::currentTextChanged, this, [=](QString value){clear_SameRole(Port_C);});
    connect(ui->gb_4_comb, &QComboBox::currentTextChanged, this, [=](QString value){clear_SameRole(Port_D);});

    connect(ui->lineEdit_A, &QLineEdit::textEdited, this, [=](QString value){update_IPs(Port_A, value);});
    connect(ui->lineEdit_B, &QLineEdit::textEdited, this, [=](QString value){update_IPs(Port_B, value);});
    connect(ui->lineEdit_C, &QLineEdit::textEdited, this, [=](QString value){update_IPs(Port_C, value);});
    connect(ui->lineEdit_D, &QLineEdit::textEdited, this, [=](QString value){update_IPs(Port_D, value);});

    connect(ui->gb_1_chb, &QCheckBox::toggled, this, [=](bool value){current_CycleInstallFlag_A = value;});
    connect(ui->gb_2_chb, &QCheckBox::toggled, this, [=](bool value){current_CycleInstallFlag_B = value;});
    connect(ui->gb_3_chb, &QCheckBox::toggled, this, [=](bool value){current_CycleInstallFlag_C = value;});
    connect(ui->gb_4_chb, &QCheckBox::toggled, this, [=](bool value){current_CycleInstallFlag_D = value;});

    connect(ui->gb_1_pb, &QPushButton::toggled, this, [=](bool value){if(value == true){start_Worker(Port_A);}else{stop_Worker(Port_A);}});
    connect(ui->gb_2_pb, &QPushButton::toggled, this, [=](bool value){if(value == true){start_Worker(Port_B);}else{stop_Worker(Port_B);}});
    connect(ui->gb_3_pb, &QPushButton::toggled, this, [=](bool value){if(value == true){start_Worker(Port_C);}else{stop_Worker(Port_C);}});
    connect(ui->gb_4_pb, &QPushButton::toggled, this, [=](bool value){if(value == true){start_Worker(Port_D);}else{stop_Worker(Port_D);}});

    connect(worker_A, &Worker::OneInstall_finished, this, [=](){finished_Worker(Port_A, true);});
    connect(worker_B, &Worker::OneInstall_finished, this, [=](){finished_Worker(Port_B, true);});
    connect(worker_C, &Worker::OneInstall_finished, this, [=](){finished_Worker(Port_C, true);});
    connect(worker_D, &Worker::OneInstall_finished, this, [=](){finished_Worker(Port_D, true);});

    connect(worker_A, &Worker::FullInstall_finished, this, [=](){finished_Worker(Port_A, false);});
    connect(worker_B, &Worker::FullInstall_finished, this, [=](){finished_Worker(Port_B, false);});
    connect(worker_C, &Worker::FullInstall_finished, this, [=](){finished_Worker(Port_C, false);});
    connect(worker_D, &Worker::FullInstall_finished, this, [=](){finished_Worker(Port_D, false);});

    connect(worker_A, &QThread::finished, this, [=](){if(worker_A->term)ui->gb_1->setStyleSheet("background-color:rgb(178,34,34)");});
    connect(worker_B, &QThread::finished, this, [=](){if(worker_B->term)ui->gb_2->setStyleSheet("background-color:rgb(178,34,34)");});
    connect(worker_C, &QThread::finished, this, [=](){if(worker_C->term)ui->gb_3->setStyleSheet("background-color:rgb(178,34,34)");});
    connect(worker_D, &QThread::finished, this, [=](){if(worker_D->term)ui->gb_4->setStyleSheet("background-color:rgb(178,34,34)");});

    connect(worker_A, &Worker::OneInstall_started, this, [=](){ui->gb_1->setStyleSheet("background-color:rgb(204, 150, 2)");});
    connect(worker_B, &Worker::OneInstall_started, this, [=](){ui->gb_2->setStyleSheet("background-color:rgb(204, 150, 2)");});
    connect(worker_C, &Worker::OneInstall_started, this, [=](){ui->gb_3->setStyleSheet("background-color:rgb(204, 150, 2)");});
    connect(worker_D, &Worker::OneInstall_started, this, [=](){ui->gb_4->setStyleSheet("background-color:rgb(204, 150, 2)");});

    connect(worker_A, &Worker::ProgressChanged, ui->progressBar_A, &QProgressBar::setValue);
    connect(worker_B, &Worker::ProgressChanged, ui->progressBar_B, &QProgressBar::setValue);
    connect(worker_C, &Worker::ProgressChanged, ui->progressBar_C, &QProgressBar::setValue);
    connect(worker_D, &Worker::ProgressChanged, ui->progressBar_D, &QProgressBar::setValue);
}

MainWindow::~MainWindow()
{
    disconnect(ui->action_edit, &QAction::triggered, config_window, &Config::open);
    disconnect(ui->action_parse_archive_2, &QAction::triggered, config_window, &Config::parse_Archive);

    disconnect(config_window, &Config::scriptPath_updated, this, &MainWindow::update_ScriptPathLabel);
    disconnect(config_window, &Config::archivePath_updated, this, &MainWindow::update_ArchivePathLabel);

    disconnect(worker_A, &Worker::ProgressChanged, ui->progressBar_A, &QProgressBar::setValue);
    disconnect(worker_B, &Worker::ProgressChanged, ui->progressBar_B, &QProgressBar::setValue);
    disconnect(worker_C, &Worker::ProgressChanged, ui->progressBar_C, &QProgressBar::setValue);
    disconnect(worker_D, &Worker::ProgressChanged, ui->progressBar_D, &QProgressBar::setValue);

    delete config_window;

    delete worker_A;
    delete worker_B;
    delete worker_C;
    delete worker_D;

    delete ui;
}

void MainWindow::import_Config()
{
    qInfo(log_Main()) << "Import config file";

    QString out = QFileDialog::getOpenFileName(this, tr("Open Config file"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation), tr("Config (*.json)"));

    if(!out.isEmpty())
    {
        qInfo(log_Main()) << "Import path: " << out;
        path_config = out;
    }
    else
    {
        qWarning(log_Main()) << "Import path is empty";
    }

    config_window->import_Config(path_config);
}

void MainWindow::export_Config()
{
    qInfo(log_Main()) << "Export config file";

    QString out = QFileDialog::getSaveFileName(this, tr("Save Config file"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/config.json", tr("Config (*.json)"));

    if(!out.isEmpty())
    {
        qInfo(log_Main()) << "Export path: " << out;
        export_path_config = out;
    }
    else
    {
        qWarning(log_Main()) << "Export path is empty";
    }

    config_window->export_Config(export_path_config);
}

void MainWindow::update_ArchivePathLabel(QString path)
{
    qInfo(log_Main()) << "Update Archive Path Label";

    path_archive = path;
    ui->lb_ArchPath->setText(path_archive);

    if((path_archive != "") && (path_script != ""))
    {
        ui->gb_1_pb->setEnabled(true);
        ui->gb_2_pb->setEnabled(true);
        ui->gb_3_pb->setEnabled(true);
        ui->gb_4_pb->setEnabled(true);
    }
}

void MainWindow::update_ScriptPathLabel(QString path)
{
    qInfo(log_Main()) << "Update Script Path Label";

    path_script = path;
    ui->lb_ScPath->setText(path_script);

    if((path_archive != "") && (path_script != ""))
    {
        ui->gb_1_pb->setEnabled(true);
        ui->gb_2_pb->setEnabled(true);
        ui->gb_3_pb->setEnabled(true);
        ui->gb_4_pb->setEnabled(true);
    }
}

void MainWindow::update_MasterFiles(QString path)
{
    qInfo(log_Main()) << "Update Master files path:" << path;
    master_files = path;
}

void MainWindow::update_SlaveFiles(QString path)
{
    qInfo(log_Main()) << "Update Slave files path:" << path;
    slave_files = path;
}

void MainWindow::update_InstallPassword()
{
    qInfo(log_Main()) << "Update password";
    install_password = config_window->get_InstallPassword();
}

void MainWindow::update_PortIPs()
{
    qInfo(log_Main()) << "Update Port IPs";

    current_IP_A = config_window->get_PortIP(Port_A);
    current_IP_B = config_window->get_PortIP(Port_B);
    current_IP_C = config_window->get_PortIP(Port_C);
    current_IP_D = config_window->get_PortIP(Port_D);

    ui->lineEdit_A->setText(current_IP_A);
    ui->lineEdit_B->setText(current_IP_B);
    ui->lineEdit_C->setText(current_IP_C);
    ui->lineEdit_D->setText(current_IP_D);
}

void MainWindow::update_PortRoles()
{
    qInfo(log_Main()) << "Update Port Roles";

    current_Role_A = config_window->get_PortRole(Port_A);
    current_Role_B = config_window->get_PortRole(Port_B);
    current_Role_C = config_window->get_PortRole(Port_C);
    current_Role_D = config_window->get_PortRole(Port_D);

    ui->gb_1_comb->setCurrentText(current_Role_A);
    ui->gb_2_comb->setCurrentText(current_Role_B);
    ui->gb_3_comb->setCurrentText(current_Role_C);
    ui->gb_4_comb->setCurrentText(current_Role_D);
}

void MainWindow::update_PortCycleInstall()
{
    qInfo(log_Main()) << "Update Port CycleInstallFlag";

    current_CycleInstallFlag_A = config_window->get_PortCycleInstall(Port_A);
    current_CycleInstallFlag_B = config_window->get_PortCycleInstall(Port_B);
    current_CycleInstallFlag_C = config_window->get_PortCycleInstall(Port_C);
    current_CycleInstallFlag_D = config_window->get_PortCycleInstall(Port_D);

    ui->gb_1_chb->setChecked(current_CycleInstallFlag_A);
    ui->gb_2_chb->setChecked(current_CycleInstallFlag_B);
    ui->gb_3_chb->setChecked(current_CycleInstallFlag_C);
    ui->gb_4_chb->setChecked(current_CycleInstallFlag_D);
}

void MainWindow::update_Roles()
{
    qInfo(log_Main()) << "Update available Roles";

    role_list = config_window->get_Roles();

    ui->gb_1_comb->clear();
    ui->gb_2_comb->clear();
    ui->gb_3_comb->clear();
    ui->gb_4_comb->clear();

    ui->gb_1_comb->addItems(role_list);
    ui->gb_2_comb->addItems(role_list);
    ui->gb_3_comb->addItems(role_list);
    ui->gb_4_comb->addItems(role_list);
}

void MainWindow::update_Config_Name() {
    ui->comboBox->blockSignals(true);
    qInfo(log_Main()) << "Update available config name";

    // config_name_list = config_window->get_config_name();
    ui->comboBox->clear();
    ui->comboBox->addItems(config_window->config_names_list);
    ui->comboBox->blockSignals(false);
}

void MainWindow::update_IPs(PortNames port_name, QString ip)
{
    qInfo(log_Main()) << "Update Port " << port_name << "IP " << ip;

    switch(port_name)
    {
    case Port_A:
        current_IP_A = ip;
        qInfo(log_Main()) << "IP Port_A: " << current_IP_A;
        break;
    case Port_B:
        current_IP_B = ip;
        qInfo(log_Main()) << "IP Port_B: " << current_IP_B;
        break;
    case Port_C:
        current_IP_C = ip;
        qInfo(log_Main()) << "IP Port_C: " << current_IP_C;
        break;
    case Port_D:
        current_IP_D = ip;
        qInfo(log_Main()) << "IP Port_D: " << current_IP_D;
        break;
    default:
        qCritical(log_Main()) << "Unknown port: " << port_name;
    }
}

void MainWindow::clear_SameRole(PortNames port_name)
{
    qInfo(log_Main()) << "Clear same role";

    switch(port_name)
    {
    case Port_A:
        current_Role_A = ui->gb_1_comb->currentText();

        if(ui->gb_1_comb->currentText() == ui->gb_2_comb->currentText())
        {
            current_Role_B = "None";
            ui->gb_2_comb->setCurrentText("None");
        }

        if(ui->gb_1_comb->currentText() == ui->gb_3_comb->currentText())
        {
            current_Role_C = "None";
            ui->gb_3_comb->setCurrentText("None");
        }

        if(ui->gb_1_comb->currentText() == ui->gb_4_comb->currentText())
        {
            current_Role_D = "None";
            ui->gb_4_comb->setCurrentText("None");
        }

        break;
    case Port_B:
        current_Role_B = ui->gb_2_comb->currentText();

        if(ui->gb_2_comb->currentText() == ui->gb_1_comb->currentText())
        {
            current_Role_A = "None";
            ui->gb_1_comb->setCurrentText("None");
        }

        if(ui->gb_2_comb->currentText() == ui->gb_3_comb->currentText())
        {
            current_Role_C = "None";
            ui->gb_3_comb->setCurrentText("None");
        }

        if(ui->gb_2_comb->currentText() == ui->gb_4_comb->currentText())
        {
            current_Role_D = "None";
            ui->gb_4_comb->setCurrentText("None");
        }

        break;
    case Port_C:
        current_Role_C = ui->gb_3_comb->currentText();

        if(ui->gb_3_comb->currentText() == ui->gb_2_comb->currentText())
        {
            current_Role_B = "None";
            ui->gb_2_comb->setCurrentText("None");
        }

        if(ui->gb_3_comb->currentText() == ui->gb_1_comb->currentText())
        {
            current_Role_A = "None";
            ui->gb_1_comb->setCurrentText("None");
        }

        if(ui->gb_3_comb->currentText() == ui->gb_4_comb->currentText())
        {
            current_Role_D = "None";
            ui->gb_4_comb->setCurrentText("None");
        }

        break;
    case Port_D:
        current_Role_D = ui->gb_4_comb->currentText();

        if(ui->gb_4_comb->currentText() == ui->gb_2_comb->currentText())
        {
            current_Role_B = "None";
            ui->gb_2_comb->setCurrentText("None");
        }

        if(ui->gb_4_comb->currentText() == ui->gb_3_comb->currentText())
        {
            current_Role_C = "None";
            ui->gb_3_comb->setCurrentText("None");
        }

        if(ui->gb_4_comb->currentText() == ui->gb_1_comb->currentText())
        {
            current_Role_A = "None";
            ui->gb_1_comb->setCurrentText("None");
        }

        break;
    }
}

void MainWindow::start_Worker(PortNames port_name)
{
    qInfo(log_Main()) << "Start worker " << port_name;

    switch(port_name)
    {
    case Port_A:
        ui->gb_1_pb->setText("Interrupt");
        ui->gb_1_chb->setEnabled(false);

        worker_A->set_script_path(path_script);
        worker_A->set_archive_path(path_archive);
        worker_A->set_IP(current_IP_A);
        worker_A->set_Role(current_Role_A);
        worker_A->set_CycleInstallFlag(current_CycleInstallFlag_A);
        worker_A->set_password(install_password);
        worker_A->set_WaitIP(config_window->get_RoleWaitIP(current_Role_A));
        if(current_Role_A == "Master" || current_Role_A == "Master --router")
        {
            worker_A->set_miscdir(master_files);
        }
        else
        {
            worker_A->set_miscdir(slave_files);
        }

        worker_A->start();

        break;
    case Port_B:
        ui->gb_2_pb->setText("Interrupt");
        ui->gb_2_chb->setEnabled(false);

        worker_B->set_script_path(path_script);
        worker_B->set_archive_path(path_archive);
        worker_B->set_IP(current_IP_B);
        worker_B->set_Role(current_Role_B);
        worker_B->set_CycleInstallFlag(current_CycleInstallFlag_B);
        worker_B->set_password(install_password);
        worker_B->set_WaitIP(config_window->get_RoleWaitIP(current_Role_B));
        if(current_Role_B == "Master" || current_Role_B == "Master --router")
        {
            worker_B->set_miscdir(master_files);
        }
        else
        {
            worker_B->set_miscdir(slave_files);
        }

        worker_B->start();

        break;
    case Port_C:
        ui->gb_3_pb->setText("Interrupt");
        ui->gb_3_chb->setEnabled(false);

        worker_C->set_script_path(path_script);
        worker_C->set_archive_path(path_archive);
        worker_C->set_IP(current_IP_C);
        worker_C->set_Role(current_Role_C);
        worker_C->set_CycleInstallFlag(current_CycleInstallFlag_C);
        worker_C->set_password(install_password);
        worker_C->set_WaitIP(config_window->get_RoleWaitIP(current_Role_C));
        if(current_Role_C == "Master" || current_Role_C == "Master --router")
        {
            worker_C->set_miscdir(master_files);
        }
        else
        {
            worker_C->set_miscdir(slave_files);
        }

        worker_C->start();

        break;
    case Port_D:
        ui->gb_4_pb->setText("Interrupt");
        ui->gb_4_chb->setEnabled(false);

        worker_D->set_script_path(path_script);
        worker_D->set_archive_path(path_archive);
        worker_D->set_IP(current_IP_D);
        worker_D->set_Role(current_Role_D);
        worker_D->set_CycleInstallFlag(current_CycleInstallFlag_D);
        worker_D->set_password(install_password);
        worker_D->set_WaitIP(config_window->get_RoleWaitIP(current_Role_D));
        if(current_Role_D == "Master" || current_Role_D == "Master --router")
        {
            worker_D->set_miscdir(master_files);
        }
        else
        {
            worker_D->set_miscdir(slave_files);
        }

        worker_D->start();

        break;
    }
}

void MainWindow::stop_Worker(PortNames port_name)
{
    qInfo(log_Main()) << "Stop worker " << port_name;

    switch(port_name)
    {
    case Port_A:
        ui->gb_1_pb->setText("Install");
        ui->gb_1_chb->setEnabled(true);

        worker_A->stop();

        break;
    case Port_B:
        ui->gb_2_pb->setText("Install");
        ui->gb_2_chb->setEnabled(true);

        worker_B->stop();

        break;
    case Port_C:
        ui->gb_3_pb->setText("Install");
        ui->gb_3_chb->setEnabled(true);

        worker_C->stop();

        break;
    case Port_D:
        ui->gb_4_pb->setText("Install");
        ui->gb_4_chb->setEnabled(true);

        worker_D->stop();

        break;
    }
}

void MainWindow::finished_Worker(PortNames port_name, bool finish_one)
{
    qInfo(log_Main()) << "Finished worker " << port_name;

    switch(port_name)
    {
    case Port_A:
        if(!finish_one)
        {
            ui->gb_1_pb->setText("Install");
            ui->gb_1_chb->setEnabled(true);

            ui->gb_1_pb->blockSignals(true);
            ui->gb_1_pb->setChecked(false);
            ui->gb_1_pb->blockSignals(false);
        }

        if(!worker_A->term)
        {
            ui->gb_1->setStyleSheet("background-color:rgb(50,205,50)");
        }
        else
        {
            ui->gb_1->setStyleSheet("background-color:rgb(178,34,34)");
        }

        break;
    case Port_B:
        if(!finish_one)
        {
            ui->gb_2_pb->setText("Install");
            ui->gb_2_chb->setEnabled(true);

            ui->gb_2_pb->blockSignals(true);
            ui->gb_2_pb->setChecked(false);
            ui->gb_2_pb->blockSignals(false);
        }

        if(!worker_B->term)
        {
            ui->gb_2->setStyleSheet("background-color:rgb(50,205,50)");
        }
        else
        {
            ui->gb_2->setStyleSheet("background-color:rgb(178,34,34)");
        }

        break;
    case Port_C:
        if(!finish_one)
        {
            ui->gb_3_pb->setText("Install");
            ui->gb_3_chb->setEnabled(true);

            ui->gb_3_pb->blockSignals(true);
            ui->gb_3_pb->setChecked(false);
            ui->gb_3_pb->blockSignals(false);
        }

        if(!worker_C->term)
        {
            ui->gb_3->setStyleSheet("background-color:rgb(50,205,50)");
        }
        else
        {
            ui->gb_3->setStyleSheet("background-color:rgb(178,34,34)");
        }

        break;
    case Port_D:
        if(!finish_one)
        {
            ui->gb_4_pb->setText("Install");
            ui->gb_4_chb->setEnabled(true);

            ui->gb_4_pb->blockSignals(true);
            ui->gb_4_pb->setChecked(false);
            ui->gb_4_pb->blockSignals(false);
        }

        if(!worker_D->term)
        {
            ui->gb_4->setStyleSheet("background-color:rgb(50,205,50)");
        }
        else
        {
            ui->gb_4->setStyleSheet("background-color:rgb(178,34,34)");
        }

        break;
    }
}

void MainWindow::update_config_name_in_main_window() {
    QString current_config_name = ui->comboBox->currentText();
    qInfo(log_Main()) << "update_config_name_in_main_window - " << current_config_name;
    config_window->readConfigFile(current_config_name);
}
