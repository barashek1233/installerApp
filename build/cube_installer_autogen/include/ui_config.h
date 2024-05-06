/********************************************************************************
** Form generated from reading UI file 'config.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIG_H
#define UI_CONFIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Config
{
public:
    QTabWidget *tabWidget;
    QWidget *tab_Path;
    QLabel *label_Sc;
    QLabel *label_Arch;
    QLabel *lb_ArchPath;
    QLabel *lb_ScPath;
    QPushButton *open_ArchPath;
    QPushButton *open_ScPath;
    QLabel *lb_MF_path;
    QLabel *label_MF;
    QPushButton *open_MF_Path;
    QPushButton *open_SF_Path;
    QLabel *label_SF;
    QLabel *lb_SF_path;
    QWidget *tab_param;
    QGroupBox *groupBox_A;
    QLabel *label_1A;
    QLabel *label_2A;
    QLabel *label_3A;
    QCheckBox *checkBox_A;
    QComboBox *comboBox_A;
    QLineEdit *lineEdit_A;
    QGroupBox *groupBox_B;
    QLabel *label_1B;
    QLabel *label_2B;
    QLabel *label_3B;
    QCheckBox *checkBox_B;
    QComboBox *comboBox_B;
    QLineEdit *lineEdit_B;
    QGroupBox *groupBox_C;
    QLabel *label_1C;
    QLabel *label_2C;
    QLabel *label_3C;
    QCheckBox *checkBox_C;
    QComboBox *comboBox_C;
    QLineEdit *lineEdit_C;
    QGroupBox *groupBox_D;
    QLabel *label_1D;
    QLabel *label_2D;
    QLabel *label_3D;
    QCheckBox *checkBox_D;
    QComboBox *comboBox_D;
    QLineEdit *lineEdit_D;
    QWidget *tab_auth;
    QLabel *lb_password;
    QLineEdit *le_password;
    QCheckBox *view_password;
    QPushButton *Cancel;
    QPushButton *Save;

    void setupUi(QDialog *Config)
    {
        if (Config->objectName().isEmpty())
            Config->setObjectName("Config");
        Config->resize(552, 362);
        Config->setMinimumSize(QSize(552, 362));
        Config->setMaximumSize(QSize(552, 362));
        tabWidget = new QTabWidget(Config);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(10, 10, 531, 311));
        tab_Path = new QWidget();
        tab_Path->setObjectName("tab_Path");
        label_Sc = new QLabel(tab_Path);
        label_Sc->setObjectName("label_Sc");
        label_Sc->setGeometry(QRect(10, 10, 91, 21));
        label_Arch = new QLabel(tab_Path);
        label_Arch->setObjectName("label_Arch");
        label_Arch->setGeometry(QRect(10, 40, 91, 21));
        lb_ArchPath = new QLabel(tab_Path);
        lb_ArchPath->setObjectName("lb_ArchPath");
        lb_ArchPath->setGeometry(QRect(100, 40, 331, 21));
        lb_ArchPath->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lb_ScPath = new QLabel(tab_Path);
        lb_ScPath->setObjectName("lb_ScPath");
        lb_ScPath->setGeometry(QRect(100, 10, 331, 21));
        lb_ScPath->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        open_ArchPath = new QPushButton(tab_Path);
        open_ArchPath->setObjectName("open_ArchPath");
        open_ArchPath->setGeometry(QRect(440, 40, 80, 26));
        open_ScPath = new QPushButton(tab_Path);
        open_ScPath->setObjectName("open_ScPath");
        open_ScPath->setGeometry(QRect(440, 10, 80, 26));
        lb_MF_path = new QLabel(tab_Path);
        lb_MF_path->setObjectName("lb_MF_path");
        lb_MF_path->setGeometry(QRect(100, 90, 331, 21));
        lb_MF_path->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_MF = new QLabel(tab_Path);
        label_MF->setObjectName("label_MF");
        label_MF->setGeometry(QRect(10, 90, 91, 21));
        open_MF_Path = new QPushButton(tab_Path);
        open_MF_Path->setObjectName("open_MF_Path");
        open_MF_Path->setGeometry(QRect(440, 90, 80, 26));
        open_SF_Path = new QPushButton(tab_Path);
        open_SF_Path->setObjectName("open_SF_Path");
        open_SF_Path->setGeometry(QRect(440, 120, 80, 26));
        label_SF = new QLabel(tab_Path);
        label_SF->setObjectName("label_SF");
        label_SF->setGeometry(QRect(10, 120, 91, 21));
        lb_SF_path = new QLabel(tab_Path);
        lb_SF_path->setObjectName("lb_SF_path");
        lb_SF_path->setGeometry(QRect(100, 120, 331, 21));
        lb_SF_path->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        tabWidget->addTab(tab_Path, QString());
        tab_param = new QWidget();
        tab_param->setObjectName("tab_param");
        groupBox_A = new QGroupBox(tab_param);
        groupBox_A->setObjectName("groupBox_A");
        groupBox_A->setGeometry(QRect(10, 10, 241, 121));
        label_1A = new QLabel(groupBox_A);
        label_1A->setObjectName("label_1A");
        label_1A->setGeometry(QRect(10, 30, 81, 21));
        label_2A = new QLabel(groupBox_A);
        label_2A->setObjectName("label_2A");
        label_2A->setGeometry(QRect(10, 60, 81, 21));
        label_3A = new QLabel(groupBox_A);
        label_3A->setObjectName("label_3A");
        label_3A->setGeometry(QRect(10, 90, 81, 21));
        checkBox_A = new QCheckBox(groupBox_A);
        checkBox_A->setObjectName("checkBox_A");
        checkBox_A->setGeometry(QRect(100, 90, 131, 21));
        checkBox_A->setChecked(true);
        checkBox_A->setTristate(false);
        comboBox_A = new QComboBox(groupBox_A);
        comboBox_A->setObjectName("comboBox_A");
        comboBox_A->setGeometry(QRect(100, 60, 131, 21));
        lineEdit_A = new QLineEdit(groupBox_A);
        lineEdit_A->setObjectName("lineEdit_A");
        lineEdit_A->setGeometry(QRect(100, 30, 131, 21));
        lineEdit_A->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        groupBox_B = new QGroupBox(tab_param);
        groupBox_B->setObjectName("groupBox_B");
        groupBox_B->setGeometry(QRect(270, 10, 241, 121));
        label_1B = new QLabel(groupBox_B);
        label_1B->setObjectName("label_1B");
        label_1B->setGeometry(QRect(10, 30, 81, 21));
        label_2B = new QLabel(groupBox_B);
        label_2B->setObjectName("label_2B");
        label_2B->setGeometry(QRect(10, 60, 81, 21));
        label_3B = new QLabel(groupBox_B);
        label_3B->setObjectName("label_3B");
        label_3B->setGeometry(QRect(10, 90, 81, 21));
        checkBox_B = new QCheckBox(groupBox_B);
        checkBox_B->setObjectName("checkBox_B");
        checkBox_B->setGeometry(QRect(100, 90, 131, 21));
        checkBox_B->setChecked(true);
        checkBox_B->setTristate(false);
        comboBox_B = new QComboBox(groupBox_B);
        comboBox_B->setObjectName("comboBox_B");
        comboBox_B->setGeometry(QRect(100, 60, 131, 21));
        lineEdit_B = new QLineEdit(groupBox_B);
        lineEdit_B->setObjectName("lineEdit_B");
        lineEdit_B->setGeometry(QRect(100, 30, 131, 21));
        lineEdit_B->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        groupBox_C = new QGroupBox(tab_param);
        groupBox_C->setObjectName("groupBox_C");
        groupBox_C->setGeometry(QRect(10, 150, 241, 121));
        label_1C = new QLabel(groupBox_C);
        label_1C->setObjectName("label_1C");
        label_1C->setGeometry(QRect(10, 30, 81, 21));
        label_2C = new QLabel(groupBox_C);
        label_2C->setObjectName("label_2C");
        label_2C->setGeometry(QRect(10, 60, 81, 21));
        label_3C = new QLabel(groupBox_C);
        label_3C->setObjectName("label_3C");
        label_3C->setGeometry(QRect(10, 90, 81, 21));
        checkBox_C = new QCheckBox(groupBox_C);
        checkBox_C->setObjectName("checkBox_C");
        checkBox_C->setGeometry(QRect(100, 90, 131, 21));
        checkBox_C->setChecked(true);
        checkBox_C->setTristate(false);
        comboBox_C = new QComboBox(groupBox_C);
        comboBox_C->setObjectName("comboBox_C");
        comboBox_C->setGeometry(QRect(100, 60, 131, 21));
        lineEdit_C = new QLineEdit(groupBox_C);
        lineEdit_C->setObjectName("lineEdit_C");
        lineEdit_C->setGeometry(QRect(100, 30, 131, 21));
        lineEdit_C->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        groupBox_D = new QGroupBox(tab_param);
        groupBox_D->setObjectName("groupBox_D");
        groupBox_D->setGeometry(QRect(270, 150, 241, 121));
        label_1D = new QLabel(groupBox_D);
        label_1D->setObjectName("label_1D");
        label_1D->setGeometry(QRect(10, 30, 81, 21));
        label_2D = new QLabel(groupBox_D);
        label_2D->setObjectName("label_2D");
        label_2D->setGeometry(QRect(10, 60, 81, 21));
        label_3D = new QLabel(groupBox_D);
        label_3D->setObjectName("label_3D");
        label_3D->setGeometry(QRect(10, 90, 81, 21));
        checkBox_D = new QCheckBox(groupBox_D);
        checkBox_D->setObjectName("checkBox_D");
        checkBox_D->setGeometry(QRect(100, 90, 131, 21));
        checkBox_D->setChecked(true);
        checkBox_D->setTristate(false);
        comboBox_D = new QComboBox(groupBox_D);
        comboBox_D->setObjectName("comboBox_D");
        comboBox_D->setGeometry(QRect(100, 60, 131, 21));
        lineEdit_D = new QLineEdit(groupBox_D);
        lineEdit_D->setObjectName("lineEdit_D");
        lineEdit_D->setGeometry(QRect(100, 30, 131, 21));
        lineEdit_D->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        tabWidget->addTab(tab_param, QString());
        tab_auth = new QWidget();
        tab_auth->setObjectName("tab_auth");
        lb_password = new QLabel(tab_auth);
        lb_password->setObjectName("lb_password");
        lb_password->setGeometry(QRect(10, 10, 81, 21));
        le_password = new QLineEdit(tab_auth);
        le_password->setObjectName("le_password");
        le_password->setGeometry(QRect(90, 10, 361, 21));
        le_password->setInputMethodHints(Qt::ImhHiddenText|Qt::ImhNoAutoUppercase|Qt::ImhNoPredictiveText|Qt::ImhSensitiveData);
        le_password->setEchoMode(QLineEdit::Password);
        view_password = new QCheckBox(tab_auth);
        view_password->setObjectName("view_password");
        view_password->setGeometry(QRect(460, 10, 61, 21));
        tabWidget->addTab(tab_auth, QString());
        Cancel = new QPushButton(Config);
        Cancel->setObjectName("Cancel");
        Cancel->setGeometry(QRect(450, 330, 80, 26));
        Save = new QPushButton(Config);
        Save->setObjectName("Save");
        Save->setGeometry(QRect(360, 330, 80, 26));

        retranslateUi(Config);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Config);
    } // setupUi

    void retranslateUi(QDialog *Config)
    {
        Config->setWindowTitle(QCoreApplication::translate("Config", "Dialog", nullptr));
        label_Sc->setText(QCoreApplication::translate("Config", "Script Path:", nullptr));
        label_Arch->setText(QCoreApplication::translate("Config", "Archive Path:", nullptr));
        lb_ArchPath->setText(QString());
        lb_ScPath->setText(QString());
        open_ArchPath->setText(QCoreApplication::translate("Config", "Open", nullptr));
        open_ScPath->setText(QCoreApplication::translate("Config", "Open", nullptr));
        lb_MF_path->setText(QString());
        label_MF->setText(QCoreApplication::translate("Config", "Master Files:", nullptr));
        open_MF_Path->setText(QCoreApplication::translate("Config", "Open", nullptr));
        open_SF_Path->setText(QCoreApplication::translate("Config", "Open", nullptr));
        label_SF->setText(QCoreApplication::translate("Config", "Slave Files:", nullptr));
        lb_SF_path->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_Path), QCoreApplication::translate("Config", "File Pathes", nullptr));
        groupBox_A->setTitle(QCoreApplication::translate("Config", "Port A", nullptr));
        label_1A->setText(QCoreApplication::translate("Config", "Start IP", nullptr));
        label_2A->setText(QCoreApplication::translate("Config", "Start Role", nullptr));
        label_3A->setText(QCoreApplication::translate("Config", "Cycle install", nullptr));
        checkBox_A->setText(QString());
        lineEdit_A->setText(QString());
        groupBox_B->setTitle(QCoreApplication::translate("Config", "Port B", nullptr));
        label_1B->setText(QCoreApplication::translate("Config", "Start IP", nullptr));
        label_2B->setText(QCoreApplication::translate("Config", "Start Role", nullptr));
        label_3B->setText(QCoreApplication::translate("Config", "Cycle install", nullptr));
        checkBox_B->setText(QString());
        lineEdit_B->setText(QString());
        groupBox_C->setTitle(QCoreApplication::translate("Config", "Port C", nullptr));
        label_1C->setText(QCoreApplication::translate("Config", "Start IP", nullptr));
        label_2C->setText(QCoreApplication::translate("Config", "Start Role", nullptr));
        label_3C->setText(QCoreApplication::translate("Config", "Cycle install", nullptr));
        checkBox_C->setText(QString());
        lineEdit_C->setText(QString());
        groupBox_D->setTitle(QCoreApplication::translate("Config", "Port D", nullptr));
        label_1D->setText(QCoreApplication::translate("Config", "Start IP", nullptr));
        label_2D->setText(QCoreApplication::translate("Config", "Start Role", nullptr));
        label_3D->setText(QCoreApplication::translate("Config", "Cycle install", nullptr));
        checkBox_D->setText(QString());
        lineEdit_D->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_param), QCoreApplication::translate("Config", "Ports parameters", nullptr));
        lb_password->setText(QCoreApplication::translate("Config", "Password:", nullptr));
        view_password->setText(QCoreApplication::translate("Config", "View", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_auth), QCoreApplication::translate("Config", "Authentication", nullptr));
        Cancel->setText(QCoreApplication::translate("Config", "Cancel", nullptr));
        Save->setText(QCoreApplication::translate("Config", "Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Config: public Ui_Config {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIG_H
