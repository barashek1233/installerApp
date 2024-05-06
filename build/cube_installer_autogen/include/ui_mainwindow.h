/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_open_script;
    QAction *action_open_archive;
    QAction *action_edit;
    QAction *action_import;
    QAction *action_export;
    QAction *action_parse_archive;
    QAction *action_parse_folder;
    QAction *action_parse_folder_2;
    QAction *action_parse_folder_3;
    QAction *action_parse_folder_4;
    QAction *action_open_log;
    QAction *action_parse_archive_2;
    QAction *action_open_script_2;
    QAction *action_open_archive_2;
    QWidget *centralwidget;
    QGroupBox *gb_1;
    QLabel *gb_1_lb1;
    QLabel *gb_1_lb2;
    QPushButton *gb_1_pb;
    QComboBox *gb_1_comb;
    QCheckBox *gb_1_chb;
    QLineEdit *lineEdit_A;
    QProgressBar *progressBar_A;
    QGroupBox *gb_2;
    QLabel *gb_2_lb1;
    QLabel *gb_2_lb2;
    QPushButton *gb_2_pb;
    QComboBox *gb_2_comb;
    QCheckBox *gb_2_chb;
    QLineEdit *lineEdit_B;
    QProgressBar *progressBar_B;
    QGroupBox *gb_3;
    QLabel *gb_3_lb1;
    QLabel *gb_3_lb2;
    QPushButton *gb_3_pb;
    QComboBox *gb_3_comb;
    QCheckBox *gb_3_chb;
    QLineEdit *lineEdit_C;
    QProgressBar *progressBar_C;
    QGroupBox *gb_4;
    QLabel *gb_4_lb1;
    QLabel *gb_4_lb2;
    QPushButton *gb_4_pb;
    QComboBox *gb_4_comb;
    QCheckBox *gb_4_chb;
    QLineEdit *lineEdit_D;
    QProgressBar *progressBar_D;
    QLabel *lb_ArchPath;
    QLabel *lb_ScPath;
    QLabel *label_Sc;
    QLabel *label_Arch;
    QMenuBar *menuBar;
    QMenu *menu_Open;
    QMenu *menu_Settings;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(424, 416);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(424, 416));
        MainWindow->setMaximumSize(QSize(424, 416));
        action_open_script = new QAction(MainWindow);
        action_open_script->setObjectName("action_open_script");
        action_open_archive = new QAction(MainWindow);
        action_open_archive->setObjectName("action_open_archive");
        action_edit = new QAction(MainWindow);
        action_edit->setObjectName("action_edit");
        action_import = new QAction(MainWindow);
        action_import->setObjectName("action_import");
        action_import->setEnabled(true);
        action_export = new QAction(MainWindow);
        action_export->setObjectName("action_export");
        action_export->setEnabled(true);
        action_parse_archive = new QAction(MainWindow);
        action_parse_archive->setObjectName("action_parse_archive");
        action_parse_folder = new QAction(MainWindow);
        action_parse_folder->setObjectName("action_parse_folder");
        action_parse_folder_2 = new QAction(MainWindow);
        action_parse_folder_2->setObjectName("action_parse_folder_2");
        action_parse_folder_3 = new QAction(MainWindow);
        action_parse_folder_3->setObjectName("action_parse_folder_3");
        action_parse_folder_4 = new QAction(MainWindow);
        action_parse_folder_4->setObjectName("action_parse_folder_4");
        action_open_log = new QAction(MainWindow);
        action_open_log->setObjectName("action_open_log");
        action_parse_archive_2 = new QAction(MainWindow);
        action_parse_archive_2->setObjectName("action_parse_archive_2");
        action_open_script_2 = new QAction(MainWindow);
        action_open_script_2->setObjectName("action_open_script_2");
        action_open_archive_2 = new QAction(MainWindow);
        action_open_archive_2->setObjectName("action_open_archive_2");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gb_1 = new QGroupBox(centralwidget);
        gb_1->setObjectName("gb_1");
        gb_1->setGeometry(QRect(10, 70, 191, 151));
        gb_1->setAlignment(Qt::AlignCenter);
        gb_1_lb1 = new QLabel(gb_1);
        gb_1_lb1->setObjectName("gb_1_lb1");
        gb_1_lb1->setGeometry(QRect(10, 30, 41, 21));
        gb_1_lb2 = new QLabel(gb_1);
        gb_1_lb2->setObjectName("gb_1_lb2");
        gb_1_lb2->setGeometry(QRect(10, 60, 41, 21));
        gb_1_pb = new QPushButton(gb_1);
        gb_1_pb->setObjectName("gb_1_pb");
        gb_1_pb->setEnabled(false);
        gb_1_pb->setGeometry(QRect(10, 90, 171, 26));
        gb_1_pb->setCheckable(true);
        gb_1_comb = new QComboBox(gb_1);
        gb_1_comb->setObjectName("gb_1_comb");
        gb_1_comb->setGeometry(QRect(60, 60, 121, 21));
        gb_1_chb = new QCheckBox(gb_1);
        gb_1_chb->setObjectName("gb_1_chb");
        gb_1_chb->setGeometry(QRect(10, 120, 171, 21));
        gb_1_chb->setChecked(true);
        lineEdit_A = new QLineEdit(gb_1);
        lineEdit_A->setObjectName("lineEdit_A");
        lineEdit_A->setGeometry(QRect(60, 30, 121, 21));
        lineEdit_A->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        progressBar_A = new QProgressBar(gb_1);
        progressBar_A->setObjectName("progressBar_A");
        progressBar_A->setGeometry(QRect(10, 140, 171, 7));
        progressBar_A->setStyleSheet(QString::fromUtf8(""));
        progressBar_A->setMaximum(100);
        progressBar_A->setValue(0);
        progressBar_A->setTextVisible(false);
        progressBar_A->setInvertedAppearance(false);
        gb_2 = new QGroupBox(centralwidget);
        gb_2->setObjectName("gb_2");
        gb_2->setGeometry(QRect(220, 70, 191, 151));
        gb_2->setAlignment(Qt::AlignCenter);
        gb_2_lb1 = new QLabel(gb_2);
        gb_2_lb1->setObjectName("gb_2_lb1");
        gb_2_lb1->setGeometry(QRect(10, 30, 41, 21));
        gb_2_lb2 = new QLabel(gb_2);
        gb_2_lb2->setObjectName("gb_2_lb2");
        gb_2_lb2->setGeometry(QRect(10, 60, 41, 21));
        gb_2_pb = new QPushButton(gb_2);
        gb_2_pb->setObjectName("gb_2_pb");
        gb_2_pb->setEnabled(false);
        gb_2_pb->setGeometry(QRect(10, 90, 171, 26));
        gb_2_pb->setCheckable(true);
        gb_2_comb = new QComboBox(gb_2);
        gb_2_comb->setObjectName("gb_2_comb");
        gb_2_comb->setGeometry(QRect(60, 60, 121, 21));
        gb_2_chb = new QCheckBox(gb_2);
        gb_2_chb->setObjectName("gb_2_chb");
        gb_2_chb->setGeometry(QRect(10, 120, 171, 21));
        gb_2_chb->setChecked(true);
        lineEdit_B = new QLineEdit(gb_2);
        lineEdit_B->setObjectName("lineEdit_B");
        lineEdit_B->setGeometry(QRect(60, 30, 121, 21));
        lineEdit_B->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        progressBar_B = new QProgressBar(gb_2);
        progressBar_B->setObjectName("progressBar_B");
        progressBar_B->setGeometry(QRect(10, 140, 171, 7));
        progressBar_B->setMaximum(100);
        progressBar_B->setValue(0);
        progressBar_B->setTextVisible(false);
        progressBar_B->setInvertedAppearance(false);
        gb_3 = new QGroupBox(centralwidget);
        gb_3->setObjectName("gb_3");
        gb_3->setGeometry(QRect(10, 230, 191, 151));
        gb_3->setAlignment(Qt::AlignCenter);
        gb_3_lb1 = new QLabel(gb_3);
        gb_3_lb1->setObjectName("gb_3_lb1");
        gb_3_lb1->setGeometry(QRect(10, 30, 41, 21));
        gb_3_lb2 = new QLabel(gb_3);
        gb_3_lb2->setObjectName("gb_3_lb2");
        gb_3_lb2->setGeometry(QRect(10, 60, 41, 21));
        gb_3_pb = new QPushButton(gb_3);
        gb_3_pb->setObjectName("gb_3_pb");
        gb_3_pb->setEnabled(false);
        gb_3_pb->setGeometry(QRect(10, 90, 171, 26));
        gb_3_pb->setCheckable(true);
        gb_3_comb = new QComboBox(gb_3);
        gb_3_comb->setObjectName("gb_3_comb");
        gb_3_comb->setGeometry(QRect(60, 60, 121, 21));
        gb_3_chb = new QCheckBox(gb_3);
        gb_3_chb->setObjectName("gb_3_chb");
        gb_3_chb->setGeometry(QRect(10, 120, 171, 21));
        gb_3_chb->setChecked(true);
        lineEdit_C = new QLineEdit(gb_3);
        lineEdit_C->setObjectName("lineEdit_C");
        lineEdit_C->setGeometry(QRect(60, 30, 121, 21));
        lineEdit_C->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        progressBar_C = new QProgressBar(gb_3);
        progressBar_C->setObjectName("progressBar_C");
        progressBar_C->setGeometry(QRect(10, 140, 171, 7));
        progressBar_C->setMaximum(100);
        progressBar_C->setValue(0);
        progressBar_C->setTextVisible(false);
        progressBar_C->setInvertedAppearance(false);
        gb_4 = new QGroupBox(centralwidget);
        gb_4->setObjectName("gb_4");
        gb_4->setGeometry(QRect(220, 230, 191, 151));
        gb_4->setAlignment(Qt::AlignCenter);
        gb_4_lb1 = new QLabel(gb_4);
        gb_4_lb1->setObjectName("gb_4_lb1");
        gb_4_lb1->setGeometry(QRect(10, 30, 41, 21));
        gb_4_lb2 = new QLabel(gb_4);
        gb_4_lb2->setObjectName("gb_4_lb2");
        gb_4_lb2->setGeometry(QRect(10, 60, 41, 21));
        gb_4_pb = new QPushButton(gb_4);
        gb_4_pb->setObjectName("gb_4_pb");
        gb_4_pb->setEnabled(false);
        gb_4_pb->setGeometry(QRect(10, 90, 171, 26));
        gb_4_pb->setCheckable(true);
        gb_4_comb = new QComboBox(gb_4);
        gb_4_comb->setObjectName("gb_4_comb");
        gb_4_comb->setGeometry(QRect(60, 60, 121, 21));
        gb_4_chb = new QCheckBox(gb_4);
        gb_4_chb->setObjectName("gb_4_chb");
        gb_4_chb->setGeometry(QRect(10, 120, 171, 21));
        gb_4_chb->setChecked(true);
        lineEdit_D = new QLineEdit(gb_4);
        lineEdit_D->setObjectName("lineEdit_D");
        lineEdit_D->setGeometry(QRect(60, 30, 121, 21));
        lineEdit_D->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        progressBar_D = new QProgressBar(gb_4);
        progressBar_D->setObjectName("progressBar_D");
        progressBar_D->setGeometry(QRect(10, 140, 171, 7));
        progressBar_D->setMaximum(100);
        progressBar_D->setValue(0);
        progressBar_D->setTextVisible(false);
        progressBar_D->setInvertedAppearance(false);
        lb_ArchPath = new QLabel(centralwidget);
        lb_ArchPath->setObjectName("lb_ArchPath");
        lb_ArchPath->setGeometry(QRect(100, 40, 311, 21));
        lb_ArchPath->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lb_ScPath = new QLabel(centralwidget);
        lb_ScPath->setObjectName("lb_ScPath");
        lb_ScPath->setGeometry(QRect(100, 10, 311, 21));
        lb_ScPath->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_Sc = new QLabel(centralwidget);
        label_Sc->setObjectName("label_Sc");
        label_Sc->setGeometry(QRect(10, 10, 91, 21));
        label_Arch = new QLabel(centralwidget);
        label_Arch->setObjectName("label_Arch");
        label_Arch->setGeometry(QRect(10, 40, 91, 21));
        MainWindow->setCentralWidget(centralwidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 424, 23));
        menu_Open = new QMenu(menuBar);
        menu_Open->setObjectName("menu_Open");
        menu_Settings = new QMenu(menuBar);
        menu_Settings->setObjectName("menu_Settings");
        MainWindow->setMenuBar(menuBar);
        QWidget::setTabOrder(lineEdit_A, gb_1_comb);
        QWidget::setTabOrder(gb_1_comb, gb_1_pb);
        QWidget::setTabOrder(gb_1_pb, gb_1_chb);
        QWidget::setTabOrder(gb_1_chb, lineEdit_B);
        QWidget::setTabOrder(lineEdit_B, gb_2_comb);
        QWidget::setTabOrder(gb_2_comb, gb_2_pb);
        QWidget::setTabOrder(gb_2_pb, gb_2_chb);
        QWidget::setTabOrder(gb_2_chb, lineEdit_C);
        QWidget::setTabOrder(lineEdit_C, gb_3_comb);
        QWidget::setTabOrder(gb_3_comb, gb_3_pb);
        QWidget::setTabOrder(gb_3_pb, gb_3_chb);
        QWidget::setTabOrder(gb_3_chb, lineEdit_D);
        QWidget::setTabOrder(lineEdit_D, gb_4_comb);
        QWidget::setTabOrder(gb_4_comb, gb_4_pb);
        QWidget::setTabOrder(gb_4_pb, gb_4_chb);

        menuBar->addAction(menu_Open->menuAction());
        menuBar->addAction(menu_Settings->menuAction());
        menu_Open->addAction(action_parse_archive_2);
        menu_Settings->addAction(action_edit);
        menu_Settings->addSeparator();
        menu_Settings->addAction(action_import);
        menu_Settings->addAction(action_export);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        action_open_script->setText(QCoreApplication::translate("MainWindow", "...install script", nullptr));
        action_open_archive->setText(QCoreApplication::translate("MainWindow", "...install archive", nullptr));
        action_edit->setText(QCoreApplication::translate("MainWindow", "...edit", nullptr));
        action_import->setText(QCoreApplication::translate("MainWindow", "...import", nullptr));
        action_export->setText(QCoreApplication::translate("MainWindow", "...export", nullptr));
        action_parse_archive->setText(QCoreApplication::translate("MainWindow", "...parse archive", nullptr));
        action_parse_folder->setText(QCoreApplication::translate("MainWindow", "...parse folder", nullptr));
        action_parse_folder->setIconText(QCoreApplication::translate("MainWindow", "parse folder", nullptr));
#if QT_CONFIG(tooltip)
        action_parse_folder->setToolTip(QCoreApplication::translate("MainWindow", "parse folder", nullptr));
#endif // QT_CONFIG(tooltip)
        action_parse_folder_2->setText(QCoreApplication::translate("MainWindow", "...parse folder", nullptr));
        action_parse_folder_3->setText(QCoreApplication::translate("MainWindow", "...parse folder", nullptr));
        action_parse_folder_4->setText(QCoreApplication::translate("MainWindow", "...parse folder", nullptr));
        action_open_log->setText(QCoreApplication::translate("MainWindow", "...open log", nullptr));
        action_parse_archive_2->setText(QCoreApplication::translate("MainWindow", "...archive", nullptr));
        action_open_script_2->setText(QCoreApplication::translate("MainWindow", "...script path", nullptr));
        action_open_archive_2->setText(QCoreApplication::translate("MainWindow", "...archive path", nullptr));
        gb_1->setTitle(QCoreApplication::translate("MainWindow", "Port A", nullptr));
        gb_1_lb1->setText(QCoreApplication::translate("MainWindow", "IP", nullptr));
        gb_1_lb2->setText(QCoreApplication::translate("MainWindow", "Role", nullptr));
        gb_1_pb->setText(QCoreApplication::translate("MainWindow", "install", nullptr));
        gb_1_chb->setText(QCoreApplication::translate("MainWindow", "Cycle installation", nullptr));
        gb_2->setTitle(QCoreApplication::translate("MainWindow", "Port B", nullptr));
        gb_2_lb1->setText(QCoreApplication::translate("MainWindow", "IP", nullptr));
        gb_2_lb2->setText(QCoreApplication::translate("MainWindow", "Role", nullptr));
        gb_2_pb->setText(QCoreApplication::translate("MainWindow", "install", nullptr));
        gb_2_chb->setText(QCoreApplication::translate("MainWindow", "Cycle installation", nullptr));
        gb_3->setTitle(QCoreApplication::translate("MainWindow", "Port C", nullptr));
        gb_3_lb1->setText(QCoreApplication::translate("MainWindow", "IP", nullptr));
        gb_3_lb2->setText(QCoreApplication::translate("MainWindow", "Role", nullptr));
        gb_3_pb->setText(QCoreApplication::translate("MainWindow", "install", nullptr));
        gb_3_chb->setText(QCoreApplication::translate("MainWindow", "Cycle installation", nullptr));
        gb_4->setTitle(QCoreApplication::translate("MainWindow", "Port D", nullptr));
        gb_4_lb1->setText(QCoreApplication::translate("MainWindow", "IP", nullptr));
        gb_4_lb2->setText(QCoreApplication::translate("MainWindow", "Role", nullptr));
        gb_4_pb->setText(QCoreApplication::translate("MainWindow", "install", nullptr));
        gb_4_chb->setText(QCoreApplication::translate("MainWindow", "Cycle installation", nullptr));
        lb_ArchPath->setText(QString());
        lb_ScPath->setText(QString());
        label_Sc->setText(QCoreApplication::translate("MainWindow", "Script Path:", nullptr));
        label_Arch->setText(QCoreApplication::translate("MainWindow", "Archive Path:", nullptr));
        menu_Open->setTitle(QCoreApplication::translate("MainWindow", "Open...", nullptr));
        menu_Settings->setTitle(QCoreApplication::translate("MainWindow", "Settings...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
