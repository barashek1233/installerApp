#include "config.h"
#include "./ui_config.h"

#include <QDebug>

Config::Config(QWidget *parent) : QDialog(parent), ui(new Ui::Config)  //  вопрос как передать какой конфиг открывать
{
    qInfo(log_Config()) << "Create Config";

    ui->setupUi(this);

    set_ConfigPath("./config.json");  //  -> config_path = ./config.json

    if(!readConfigFile("Sample"))
    {
        qWarning(log_Config()) << "Can't read config file when app has started";

        create_NewConfigFile();  //  если конфига нет, создаем новый шаблон 

        readConfigFile("Sample");  //  и открываем его
    }

    connect(ui->open_ScPath, &QPushButton::clicked, this, &Config::set_ScriptPath);
    connect(ui->open_ArchPath, &QPushButton::clicked, this, &Config::set_ArchivePath);

    connect(ui->open_MF_Path, &QPushButton::clicked, this, &Config::set_MasterFiles);
    connect(ui->open_SF_Path, &QPushButton::clicked, this, &Config::set_SlaveFiles);

    connect(ui->Save, &QPushButton::clicked, this, &Config::saveEditConfigFile);
    connect(ui->Cancel, &QPushButton::clicked, this, &Config::cancelEditConfigFile);

    connect(ui->le_password, &QLineEdit::textChanged, this, &Config::change_InstallPassword);
    connect(ui->view_password, &QCheckBox::stateChanged, this, [=](int value){if(ui->view_password->isChecked()){ui->le_password->setEchoMode(QLineEdit::Normal);} else{ui->le_password->setEchoMode(QLineEdit::Password);};});

    connect(ui->lineEdit_A, &QLineEdit::textChanged, this, [=]( const QString &value ) { this->change_PortIP(Port_A, value);});
    connect(ui->lineEdit_A, &QLineEdit::textChanged, this, [=]( const QString &value ) { this->change_PortIP(Port_A, value);});
    connect(ui->lineEdit_B, &QLineEdit::textChanged, this, [=]( const QString &value ) { this->change_PortIP(Port_B, value);});
    connect(ui->lineEdit_C, &QLineEdit::textChanged, this, [=]( const QString &value ) { this->change_PortIP(Port_C, value);});
    connect(ui->lineEdit_D, &QLineEdit::textChanged, this, [=]( const QString &value ) { this->change_PortIP(Port_D, value);});

    connect(ui->comboBox_A, &QComboBox::currentTextChanged, this, [=]( const QString &value ) { this->change_PortRole(Port_A, value);});
    connect(ui->comboBox_B, &QComboBox::currentTextChanged, this, [=]( const QString &value ) { this->change_PortRole(Port_B, value);});
    connect(ui->comboBox_C, &QComboBox::currentTextChanged, this, [=]( const QString &value ) { this->change_PortRole(Port_C, value);});
    connect(ui->comboBox_D, &QComboBox::currentTextChanged, this, [=]( const QString &value ) { this->change_PortRole(Port_D, value);});

    connect(ui->checkBox_A, &QCheckBox::toggled, this, [=]( const bool &value ) { this->change_PortCycleInstall(Port_A, value);});
    connect(ui->checkBox_B, &QCheckBox::toggled, this, [=]( const bool &value ) { this->change_PortCycleInstall(Port_B, value);});
    connect(ui->checkBox_C, &QCheckBox::toggled, this, [=]( const bool &value ) { this->change_PortCycleInstall(Port_C, value);});
    connect(ui->checkBox_D, &QCheckBox::toggled, this, [=]( const bool &value ) { this->change_PortCycleInstall(Port_D, value);});

    connect(&parser, SIGNAL(parse_Started()), this, SIGNAL(parse_Started()));
    connect(&parser, SIGNAL(parse_Finished()), this, SIGNAL(parse_Finished()));
    connect(&parser, SIGNAL(parse_Finished()), this, SLOT(update_AfterParse()));

    connect(&parser, &Parser::parse_Finished, this, [=]() {emit scriptPath_updated(install_script_path.toString());});
    connect(&parser, &Parser::parse_Finished, this, [=]() {emit archivePath_updated(install_archive_path.toString());});

    connect(&parser, &Parser::parse_Finished, this, [=]() {emit masterFiles_updated(master_files.toString());});
    connect(&parser, &Parser::parse_Finished, this, [=]() {emit slaveFiles_updated(slave_files.toString());});

    connect(&parser, &Parser::parse_Finished, this, &Config::portIPs_updated);
    connect(&parser, &Parser::parse_Finished, this, &Config::portRoles_updated);
    connect(&parser, &Parser::parse_Finished, this, &Config::portCycleInstalls_updated);

    connect(ui->comboBox_A, &QComboBox::currentTextChanged, this, [=](QString value){clear_SameRole(Port_A);});
    connect(ui->comboBox_B, &QComboBox::currentTextChanged, this, [=](QString value){clear_SameRole(Port_B);});
    connect(ui->comboBox_C, &QComboBox::currentTextChanged, this, [=](QString value){clear_SameRole(Port_C);});
    connect(ui->comboBox_D, &QComboBox::currentTextChanged, this, [=](QString value){clear_SameRole(Port_D);});
}

Config::~Config()
{
    disconnect(ui->open_ScPath, &QPushButton::clicked, this, &Config::set_ScriptPath);
    disconnect(ui->open_ArchPath, &QPushButton::clicked, this, &Config::set_ArchivePath);

    disconnect(ui->open_MF_Path, &QPushButton::clicked, this, &Config::set_MasterFiles);
    disconnect(ui->open_SF_Path, &QPushButton::clicked, this, &Config::set_SlaveFiles);

    disconnect(ui->Save, &QPushButton::clicked, this, &Config::saveEditConfigFile);
    disconnect(ui->Cancel, &QPushButton::clicked, this, &Config::cancelEditConfigFile);

    disconnect(ui->le_password, &QLineEdit::textChanged, this, &Config::change_InstallPassword);

    disconnect(&parser, SIGNAL(parse_Started()), this, SIGNAL(parse_Started()));
    disconnect(&parser, SIGNAL(parse_Finished()), this, SIGNAL(parse_Finished()));
    disconnect(&parser, SIGNAL(parse_Finished()), this, SLOT(update_AfterParse()));

    disconnect(&parser, &Parser::parse_Finished, this, &Config::portIPs_updated);
    disconnect(&parser, &Parser::parse_Finished, this, &Config::portRoles_updated);
    disconnect(&parser, &Parser::parse_Finished, this, &Config::portCycleInstalls_updated);

    delete ui;
}

void Config::set_ConfigPath(QString path)
{
    qInfo(log_Config()) << "Set config path: " << path;

    config_path = path;
}

bool Config::readConfigFile(QString config_name)
{
    qInfo(log_Config()) << "Read config file";

    config_file.setFileName(config_path);  //  а мне нравится эта запись надо перенять в воркер
    bool err = config_file.open(QIODevice::ReadOnly);
    if(!err)
    {
        qCritical(log_Config()) << "Can't open config file to read";
        return false;
    }

    if(config_file.size() == 0)
    {
        qCritical(log_Config()) << "Config file is empty";
        return false;
    }

    config_doc = QJsonDocument::fromJson(config_file.readAll());

    config_file.close();

    config_data_sample = config_doc.object();
    Config_Names = config_data_sample.keys();
    config_data = config_data_sample.value(config_name).toObject();

    install_script_path = config_data.value("InstallScriptPath");
    install_archive_path = config_data.value("InstallArchivePath");

    master_files = config_data.value("MasterFiles");
    slave_files = config_data.value("SlaveFiles");

    install_password = config_data.value("InstallPassword");

    //qDebug() << "Script path:" << install_script_path;
    //qDebug() << "Archive path:" << install_archive_path;

    DHCP_IP_List = config_data.value("DHCP").toArray();
    Roles = config_data.value("Roles").toArray();
    Roles_IP_List = config_data.value("RolesIPs").toObject();

    //qDebug() << "DHCP:" << DHCP_IP_List;
    //qDebug() << "Role:" << Roles;
    //qDebug() << "Roles IP:" << Roles_IP_List;

    StartIPs = config_data.value("StartIPs").toArray();
    StartRoles = config_data.value("StartRoles").toArray();
    StartCycleInstallValue = config_data.value("StartCycleInstallValue").toArray();

    //qDebug() << "StartIPs:" << StartIPs;
    //qDebug() << "StartRoles:" << StartRoles;
    //qDebug() << "StartCycleInstallValue:" << StartCycleInstallValue;

    qInfo(log_Config()) << "Parameters have readen";

    update_SettingsValues();

    emit scriptPath_updated(install_script_path.toString());
    emit archivePath_updated(install_archive_path.toString());

    emit masterFiles_updated(master_files.toString());
    emit slaveFiles_updated(slave_files.toString());
    emit config_name_update();
    emit rolesList_updated();
    emit ipList_updated();

    emit installPassword_updated();

    emit portRoles_updated();
    emit portIPs_updated();
    emit portCycleInstalls_updated();

    qInfo(log_Config()) << "Send all 'updated' signals";

    return true;
}

void Config::update_SettingsValues()
{
    qInfo(log_Config()) << "Update parameters in interface";

    ui->lb_ScPath->setText(install_script_path.toString());
    ui->lb_ArchPath->setText(install_archive_path.toString());

    ui->lb_MF_path->setText(master_files.toString());
    ui->lb_SF_path->setText(slave_files.toString());

    ui->le_password->setText(install_password.toString());

    ui->lineEdit_A->setText(StartIPs[0].toString());
    ui->lineEdit_B->setText(StartIPs[1].toString());
    ui->lineEdit_C->setText(StartIPs[2].toString());
    ui->lineEdit_D->setText(StartIPs[3].toString());

    QStringList roles_list;
    for(unsigned int i = 0; i < Roles.size() + 1; i++)
    {
        if(Roles[0].toString() != "None")
        {
            if (i == 0)
            {
                roles_list.append("None");
            }
            else
            {
                roles_list.append(Roles[i-1].toString());
            }
        }
        else
        {
            if(i == Roles.size() + 1) break;
            roles_list.append(Roles[i].toString());
        }
    }
    QStringList config_names_list;
    for (size_t index = 0; index < Config_Names.size(); index++) {
        config_names_list.append(Config_Names[index]);
    }

    ui->comboBox_2->blockSignals(true);

    ui->comboBox_A->blockSignals(true);
    ui->comboBox_B->blockSignals(true);
    ui->comboBox_C->blockSignals(true);
    ui->comboBox_D->blockSignals(true);

    ui->comboBox_2->clear();

    ui->comboBox_A->clear();
    ui->comboBox_B->clear();
    ui->comboBox_C->clear();
    ui->comboBox_D->clear();

    ui->comboBox_2->addItems(config_names_list);

    ui->comboBox_A->addItems(roles_list);
    ui->comboBox_B->addItems(roles_list);
    ui->comboBox_C->addItems(roles_list);
    ui->comboBox_D->addItems(roles_list);

    ui->comboBox_2->blockSignals(false);

    ui->comboBox_A->blockSignals(false);
    ui->comboBox_B->blockSignals(false);
    ui->comboBox_C->blockSignals(false);
    ui->comboBox_D->blockSignals(false);

    ui->comboBox_A->setCurrentText(StartRoles[0].toString());
    ui->comboBox_B->setCurrentText(StartRoles[1].toString());
    ui->comboBox_C->setCurrentText(StartRoles[2].toString());
    ui->comboBox_D->setCurrentText(StartRoles[3].toString());

    ui->checkBox_A->setChecked(StartCycleInstallValue[0].toBool());
    ui->checkBox_B->setChecked(StartCycleInstallValue[1].toBool());
    ui->checkBox_C->setChecked(StartCycleInstallValue[2].toBool());
    ui->checkBox_D->setChecked(StartCycleInstallValue[3].toBool());

    qInfo(log_Config()) << "Update parameters in interface finished";
}

void Config::create_NewConfigFile()
{
    qInfo(log_Config()) << "Create new config file";

    config_path = "./config.json";
    config_file.setFileName(config_path);
    bool err = config_file.open(QIODevice::WriteOnly|QFile::Truncate);

    if(!err)
    {
        qCritical(log_Config()) << "Can't open config file to write";
        return;
    }

    config_data.insert("InstallArchivePath", "");
    config_data.insert("InstallScriptPath", "");

    config_data.insert("MasterFiles", "");
    config_data.insert("SlaveFiles", "");

    config_data.insert("InstallPassword", "");

    DHCP_IP_List.push_back("192.168.1.102");
    DHCP_IP_List.push_back("192.168.1.106");
    DHCP_IP_List.push_back("192.168.1.110");
    DHCP_IP_List.push_back("192.168.1.114");

    config_data.insert("DHCP", DHCP_IP_List);

    Roles.push_back("Master");
    Roles.push_back("Master --router");
    Roles.push_back("Slave1");
    Roles.push_back("Slave2");
    Roles.push_back("Slave3");
    Roles.push_back("Slave4");
    Roles.push_back("Slave5");

    config_data.insert("Roles", Roles);

    Roles_IP_List.insert("Master", "192.168.1.10");
    Roles_IP_List.insert("Master --router", "192.168.1.10");
    Roles_IP_List.insert("Slave1", "192.168.1.11");
    Roles_IP_List.insert("Slave2", "192.168.1.12");
    Roles_IP_List.insert("Slave3", "192.168.1.13");
    Roles_IP_List.insert("Slave4", "192.168.1.14");
    Roles_IP_List.insert("Slave5", "192.168.1.15");

    config_data.insert("RolesIPs", Roles_IP_List);

    StartIPs.push_back("192.168.1.102");
    StartIPs.push_back("192.168.1.106");
    StartIPs.push_back("192.168.1.110");
    StartIPs.push_back("192.168.1.114");

    config_data.insert("StartIPs", StartIPs);

    StartRoles.push_back("Master");
    StartRoles.push_back("Slave1");
    StartRoles.push_back("Slave2");
    StartRoles.push_back("Slave3");

    config_data.insert("StartRoles", StartRoles);

    StartCycleInstallValue.push_back(false);
    StartCycleInstallValue.push_back(false);
    StartCycleInstallValue.push_back(false);
    StartCycleInstallValue.push_back(false);

    config_data.insert("StartCycleInstallValue", StartCycleInstallValue);
    config_data_sample.insert("Sample", config_data);
    config_doc.setObject(config_data_sample);

    config_file.write(config_doc.toJson());

    config_file.close();

    qInfo(log_Config()) << "Write parameters in empty config file finished";
}

void Config::set_ArchivePath(bool ch)
{
    qInfo(log_Config()) << "Open archive path";

    QString out = QFileDialog::getOpenFileName(this, tr("Open Archive file"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation), tr("Archives (*.tar.gz *.tar *.zip *.tar.bz)"));

    if(!out.isEmpty())
    {
        qInfo(log_Config()) << "Archive path is " << out;

        config_data.insert("InstallArchivePath", out);
        install_archive_path = config_data.value("InstallArchivePath");
    }
    else
    {
        qWarning(log_Config()) << "Empty archive path";
    }

    ui->lb_ArchPath->setText(install_archive_path.toString());

    emit archivePath_updated(install_archive_path.toString());
}

void Config::set_ScriptPath(bool ch)
{
    qInfo(log_Config()) << "Open script path";

    QString out = QFileDialog::getOpenFileName(this, tr("Open Script file"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation), tr("Scripts (*)"));

    if(!out.isEmpty())
    {
        qInfo(log_Config()) << "Script path is " << out;

        config_data.insert("InstallScriptPath", out);
        install_script_path = config_data.value("InstallScriptPath");
    }
    else
    {
        qWarning(log_Config()) << "Empty script path";
    }

    ui->lb_ScPath->setText(install_script_path.toString());

    emit scriptPath_updated(install_script_path.toString());
}

void Config::set_MasterFiles(bool ch)
{
    qInfo(log_Config()) << "Open master files path";

    QString out = QFileDialog::getExistingDirectory(this, tr("Open Master Files Dir"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if(!out.isEmpty())
    {
        qInfo(log_Config()) << "Master files path is " << out;

        config_data.insert("MasterFiles", out);
        master_files = config_data.value("MasterFiles");
    }
    else
    {
        qWarning(log_Config()) << "Empty master files path";
    }

    ui->lb_MF_path->setText(master_files.toString());

    emit masterFiles_updated(master_files.toString());
}

void Config::set_SlaveFiles(bool ch)
{
    qInfo(log_Config()) << "Open slave files path";

    QString out = QFileDialog::getExistingDirectory(this, tr("Open Slave Files Dir"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if(!out.isEmpty())
    {
        qInfo(log_Config()) << "Slave files path is " << out;

        config_data.insert("SlaveFiles", out);
        slave_files = config_data.value("SlaveFiles");
    }
    else
    {
        qWarning(log_Config()) << "Empty slave files path";
    }

    ui->lb_SF_path->setText(slave_files.toString());

    emit slaveFiles_updated(slave_files.toString());
}

bool Config::saveEditConfigFile()
{
    qInfo(log_Config()) << "Save config file";

    config_doc.setObject(config_data);

    config_file.setFileName(config_path);
    bool err = config_file.open(QIODevice::WriteOnly | QFile::Truncate);
    if(err == false)
    {
        qCritical(log_Config()) << "Can't open config file in 'QIODevice::WriteOnly | QFile::Truncate'";

        return false;
    }

    config_file.write(config_doc.toJson());

    config_file.close();

    ui->view_password->setChecked(false);

    this->close();

    emit installPassword_updated();

    qInfo(log_Config()) << "Config file is saved";

    return true;
}

void Config::cancelEditConfigFile()
{
    qInfo(log_Config()) << "Cancel edit config file";

    qInfo(log_Config()) << "Read old config file";
    readConfigFile();

    ui->view_password->setChecked(false);
    this->close();
}

void Config::change_InstallPassword(QString password)
{
    qInfo(log_Config()) << "Change password";

    config_data.insert("InstallPassword", password);
    install_password = config_data.value("InstallPassword");
}

void Config::change_PortIP(PortNames port_name, QString new_ip)
{
    qInfo(log_Config()) << "Change Port IP for " << port_name << "to " << new_ip;

    switch(port_name)
    {
        case Port_A:
            StartIPs.replace(0, new_ip);
            break;
        case Port_B:
            StartIPs.replace(1, new_ip);
            break;
        case Port_C:
            StartIPs.replace(2, new_ip);
            break;
        case Port_D:
            StartIPs.replace(3, new_ip);
            break;
        default:
            qCritical(log_Config()) << "Unknown port name: " << port_name;
            return;
    }
    config_data.insert("StartIPs", StartIPs);

    emit portIPs_updated();
}

void Config::change_PortRole(PortNames port_name, QString new_role)
{
    qInfo(log_Config()) << "Change Port Role for " << port_name << "to " << new_role;

    switch(port_name)
    {
        case Port_A:
            StartRoles.replace(0, new_role);
            break;
        case Port_B:
            StartRoles.replace(1, new_role);
            break;
        case Port_C:
            StartRoles.replace(2, new_role);
            break;
        case Port_D:
            StartRoles.replace(3, new_role);
            break;
        default:
            qCritical(log_Config()) << "Unknown port name: " << port_name;
            return;
    }
    config_data.insert("StartRoles", StartRoles);

    emit portRoles_updated();

    //qDebug() << "Change Start Roles:" << StartRoles;
}

void Config::change_PortCycleInstall(PortNames port_name, bool new_check)
{
    qInfo(log_Config()) << "Change Port CycleInstallFlag for " << port_name << "to " << new_check;

    switch(port_name)
    {
        case Port_A:
            StartCycleInstallValue.replace(0, new_check);
            break;
        case Port_B:
            StartCycleInstallValue.replace(1, new_check);
            break;
        case Port_C:
            StartCycleInstallValue.replace(2, new_check);
            break;
        case Port_D:
            StartCycleInstallValue.replace(3, new_check);
            break;
        default:
            qCritical(log_Config()) << "Unknown port name: " << port_name;
            return;
    }
    config_data.insert("StartCycleInstallValue", StartCycleInstallValue);

    emit portCycleInstalls_updated();
}

QString Config::get_ScriptPath()
{
    qInfo(log_Config()) << "Get script path";
    return install_script_path.toString();
}

QString Config::get_ArchivePath()
{
    qInfo(log_Config()) << "Get archive path";
    return install_archive_path.toString();
}

QString Config::get_MasterFiles()
{
    qInfo(log_Config()) << "Get master files path";
    return master_files.toString();
}

QString Config::get_SlaveFiles()
{
    qInfo(log_Config()) << "Get slave files path";
    return slave_files.toString();
}

QString Config::get_InstallPassword()
{
    qInfo(log_Config()) << "Get password";
    return install_password.toString();
}

QString Config::get_RoleWaitIP(QString role)
{
    qInfo(log_Config()) << "Get ip for role " << role;
    return Roles_IP_List.value(role).toString();
}

QString Config::get_PortIP(PortNames port_name)
{
    qInfo(log_Config()) << "Get ip for " << port_name;
    switch(port_name)
    {
        case Port_A:
            return StartIPs[0].toString();
        case Port_B:
            return StartIPs[1].toString();
        case Port_C:
            return StartIPs[2].toString();
        case Port_D:
            return StartIPs[3].toString();
        default:
            qCritical(log_Config()) << "Unknown port name: " << port_name;
            return "None";
    }
}

QString Config::get_PortRole(PortNames port_name)
{
    qInfo(log_Config()) << "Get role for " << port_name;
    switch(port_name)
    {
        case Port_A:
            return StartRoles[0].toString();
        case Port_B:
            return StartRoles[1].toString();
        case Port_C:
            return StartRoles[2].toString();
        case Port_D:
            return StartRoles[3].toString();
        default:
            qCritical(log_Config()) << "Unknown port name: " << port_name;
            return "None";
    }
}

bool Config::get_PortCycleInstall(PortNames port_name)
{
    qInfo(log_Config()) << "Get cycle flag for " << port_name;
    switch(port_name)
    {
        case Port_A:
            return StartCycleInstallValue[0].toBool();
        case Port_B:
            return StartCycleInstallValue[1].toBool();
        case Port_C:
            return StartCycleInstallValue[2].toBool();
        case Port_D:
            return StartCycleInstallValue[3].toBool();
        default:
            qCritical(log_Config()) << "Unknown port name: " << port_name;
            return "None";
    }
}

QStringList Config::get_config_name() {
    qInfo(log_Config()) << "Get available config name";
    QStringList list;

    for(size_t index = 0; index < Config_Names.size(); index++) {
        list.append(Config_Names[index]);
    }

    return list;
}

QStringList Config::get_Roles()
{
    qInfo(log_Config()) << "Get available roles";

    QStringList list;

    for(unsigned int i = 0; i < Roles.size() + 1; i++)
    {
        if(Roles[0].toString() != "None")
        {
            if (i == 0)
            {
                qInfo(log_Config()) << "Add 'None' role";
                list.append("None");
            }
            else
            {
                list.append(Roles[i-1].toString());
            }
        }
        else
        {
            if(i == Roles.size() + 1) break;
            list.append(Roles[i].toString());
        }
    }

    return list;
}

void Config::parse_Archive()
{
    qInfo(log_Config()) << "Parse archive";

    QString out = QFileDialog::getOpenFileName(this, tr("Open Archive file"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation), tr("Archives (*.zip *.7z *.tar)"));

    if(!out.isEmpty())
    {
        qInfo(log_Config()) << "Start Parse archive";
        parser.set_InputArchivePath(out);
        parser.parse_Archive();
    }
    else
    {
        qWarning(log_Config()) << "Empty path to parse archive";
    }
}

void Config::import_Config(QString path)
{
    qInfo(log_Config()) << "Import config file with path: " << path;

    set_ConfigPath(path);

    readConfigFile();
}

void Config::export_Config(QString path)
{
    qInfo(log_Config()) << "Export config file to path: " << path;

    QString old_path = config_path;
    set_ConfigPath(path);

    saveEditConfigFile();

    set_ConfigPath(old_path);
}

void Config::set_MainPath(QString path)
{
    parser.set_MainPath(path);
}

void Config::update_AfterParse()
{
    qInfo(log_Config()) << "Update after archive parse";

    readConfigFile();
}

void Config::clear_SameRole(PortNames port_name)
{
    qInfo(log_Config()) << "Clear same with port " << port_name << "role";

    switch(port_name)
    {
    case Port_A:
        if(ui->comboBox_A->currentText() == ui->comboBox_B->currentText()) ui->comboBox_B->setCurrentText("None");
        if(ui->comboBox_A->currentText() == ui->comboBox_C->currentText()) ui->comboBox_C->setCurrentText("None");
        if(ui->comboBox_A->currentText() == ui->comboBox_D->currentText()) ui->comboBox_D->setCurrentText("None");
        break;
    case Port_B:
        if(ui->comboBox_B->currentText() == ui->comboBox_A->currentText()) ui->comboBox_A->setCurrentText("None");
        if(ui->comboBox_B->currentText() == ui->comboBox_C->currentText()) ui->comboBox_C->setCurrentText("None");
        if(ui->comboBox_B->currentText() == ui->comboBox_D->currentText()) ui->comboBox_D->setCurrentText("None");
        break;
    case Port_C:
        if(ui->comboBox_C->currentText() == ui->comboBox_A->currentText()) ui->comboBox_A->setCurrentText("None");
        if(ui->comboBox_C->currentText() == ui->comboBox_B->currentText()) ui->comboBox_B->setCurrentText("None");
        if(ui->comboBox_C->currentText() == ui->comboBox_D->currentText()) ui->comboBox_D->setCurrentText("None");
        break;
    case Port_D:
        if(ui->comboBox_D->currentText() == ui->comboBox_A->currentText()) ui->comboBox_A->setCurrentText("None");
        if(ui->comboBox_D->currentText() == ui->comboBox_B->currentText()) ui->comboBox_B->setCurrentText("None");
        if(ui->comboBox_D->currentText() == ui->comboBox_C->currentText()) ui->comboBox_C->setCurrentText("None");
        break;
    default:
        qCritical(log_Config()) << "Unknown port name: " << port_name;
        break;
    }
}
