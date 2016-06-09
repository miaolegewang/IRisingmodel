/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSlider>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QLineEdit *gamma_box;
    QSlider *gamma_slider;
    QLabel *label_2;
    QLabel *label_6;
    QGroupBox *groupBox_2;
    QLabel *label_5;
    QLineEdit *nbeta_box;
    QGroupBox *groupBox_3;
    QRadioButton *manual_run_check;
    QRadioButton *auto_run_check;
    QPushButton *restore_trigger;
    QFrame *line;
    QGroupBox *groupBox_4;
    QLabel *label;
    QLabel *label_7;
    QDoubleSpinBox *noise_level_box;
    QToolButton *image_path;
    QFrame *line_3;
    QLabel *path_display;
    QPushButton *add_noise_button;
    QGroupBox *groupBox_5;
    QLabel *noisy_image;
    QFrame *line_2;
    QLabel *label_3;
    QLabel *original_noise_level;
    QGroupBox *groupBox_6;
    QLabel *restore_image;
    QFrame *line_4;
    QLabel *label_8;
    QLabel *restore_noise_level;
    QMenuBar *menuBar;
    QMenu *menuImage_Restoration;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1202, 783);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(520, 640, 441, 80));
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"	border: 1px solid gray;\n"
"	border-radius: 9px;\n"
"	margin-top: 0.5em;\n"
"}\n"
"\n"
"QGroupBox::title{\n"
"	subcontrol-origin: margin;\n"
"	left: 10px;\n"
"	padding: 0 3px 0 3px;\n"
"}"));
        groupBox->setFlat(false);
        gamma_box = new QLineEdit(groupBox);
        gamma_box->setObjectName(QString::fromUtf8("gamma_box"));
        gamma_box->setGeometry(QRect(10, 30, 61, 27));
        gamma_slider = new QSlider(groupBox);
        gamma_slider->setObjectName(QString::fromUtf8("gamma_slider"));
        gamma_slider->setGeometry(QRect(100, 30, 301, 29));
        gamma_slider->setOrientation(Qt::Horizontal);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(380, 60, 21, 17));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(100, 60, 21, 17));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(350, 640, 151, 80));
        groupBox_2->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"	border: 1px solid gray;\n"
"	border-radius: 9px;\n"
"	margin-top: 0.5em;\n"
"}\n"
"\n"
"QGroupBox::title{\n"
"	subcontrol-origin: margin;\n"
"	left: 10px;\n"
"	padding: 0 3px 0 3px;\n"
"}"));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 40, 67, 21));
        nbeta_box = new QLineEdit(groupBox_2);
        nbeta_box->setObjectName(QString::fromUtf8("nbeta_box"));
        nbeta_box->setGeometry(QRect(60, 40, 71, 27));
        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(980, 640, 191, 80));
        groupBox_3->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"	border: 1px solid gray;\n"
"	border-radius: 9px;\n"
"	margin-top: 0.5em;\n"
"}\n"
"\n"
"QGroupBox::title{\n"
"	subcontrol-origin: margin;\n"
"	left: 10px;\n"
"	padding: 0 3px 0 3px;\n"
"}"));
        manual_run_check = new QRadioButton(groupBox_3);
        manual_run_check->setObjectName(QString::fromUtf8("manual_run_check"));
        manual_run_check->setGeometry(QRect(10, 20, 91, 22));
        auto_run_check = new QRadioButton(groupBox_3);
        auto_run_check->setObjectName(QString::fromUtf8("auto_run_check"));
        auto_run_check->setGeometry(QRect(10, 40, 91, 31));
        restore_trigger = new QPushButton(groupBox_3);
        restore_trigger->setObjectName(QString::fromUtf8("restore_trigger"));
        restore_trigger->setGeometry(QRect(110, 30, 61, 31));
        line = new QFrame(groupBox_3);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(90, 20, 20, 51));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        groupBox_4 = new QGroupBox(centralWidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(20, 640, 311, 81));
        groupBox_4->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"	border: 1px solid gray;\n"
"	border-radius: 9px;\n"
"	margin-top: 0.5em;\n"
"}\n"
"\n"
"QGroupBox::title{\n"
"	subcontrol-origin: margin;\n"
"	left: 10px;\n"
"	padding: 0 3px 0 3px;\n"
"}"));
        label = new QLabel(groupBox_4);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(140, 20, 81, 21));
        label_7 = new QLabel(groupBox_4);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 20, 31, 31));
        noise_level_box = new QDoubleSpinBox(groupBox_4);
        noise_level_box->setObjectName(QString::fromUtf8("noise_level_box"));
        noise_level_box->setGeometry(QRect(140, 40, 69, 27));
        image_path = new QToolButton(groupBox_4);
        image_path->setObjectName(QString::fromUtf8("image_path"));
        image_path->setGeometry(QRect(50, 20, 24, 25));
        line_3 = new QFrame(groupBox_4);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setGeometry(QRect(120, 20, 20, 51));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);
        path_display = new QLabel(groupBox_4);
        path_display->setObjectName(QString::fromUtf8("path_display"));
        path_display->setGeometry(QRect(20, 50, 101, 20));
        path_display->setLayoutDirection(Qt::LeftToRight);
        add_noise_button = new QPushButton(groupBox_4);
        add_noise_button->setObjectName(QString::fromUtf8("add_noise_button"));
        add_noise_button->setGeometry(QRect(220, 40, 81, 27));
        groupBox_5 = new QGroupBox(centralWidget);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(10, 0, 571, 621));
        groupBox_5->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"	border: 1px solid gray;\n"
"	border-radius: 9px;\n"
"	margin-top: 0.5em;\n"
"}\n"
"\n"
"QGroupBox::title{\n"
"	subcontrol-origin: margin;\n"
"	left: 10px;\n"
"	padding: 0 3px 0 3px;\n"
"}"));
        noisy_image = new QLabel(groupBox_5);
        noisy_image->setObjectName(QString::fromUtf8("noisy_image"));
        noisy_image->setGeometry(QRect(30, 30, 512, 512));
        line_2 = new QFrame(groupBox_5);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(20, 570, 521, 16));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        label_3 = new QLabel(groupBox_5);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 590, 91, 17));
        original_noise_level = new QLabel(groupBox_5);
        original_noise_level->setObjectName(QString::fromUtf8("original_noise_level"));
        original_noise_level->setGeometry(QRect(140, 590, 67, 17));
        groupBox_6 = new QGroupBox(centralWidget);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setGeometry(QRect(620, 0, 570, 621));
        groupBox_6->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"	border: 1px solid gray;\n"
"	border-radius: 9px;\n"
"	margin-top: 0.5em;\n"
"}\n"
"\n"
"QGroupBox::title{\n"
"	subcontrol-origin: margin;\n"
"	left: 10px;\n"
"	padding: 0 3px 0 3px;\n"
"}"));
        restore_image = new QLabel(groupBox_6);
        restore_image->setObjectName(QString::fromUtf8("restore_image"));
        restore_image->setGeometry(QRect(30, 30, 512, 512));
        line_4 = new QFrame(groupBox_6);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setGeometry(QRect(20, 570, 531, 16));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);
        label_8 = new QLabel(groupBox_6);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(20, 590, 81, 17));
        restore_noise_level = new QLabel(groupBox_6);
        restore_noise_level->setObjectName(QString::fromUtf8("restore_noise_level"));
        restore_noise_level->setGeometry(QRect(130, 590, 111, 17));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1202, 25));
        menuImage_Restoration = new QMenu(menuBar);
        menuImage_Restoration->setObjectName(QString::fromUtf8("menuImage_Restoration"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuImage_Restoration->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MainWindow", "Adjust gamma", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        gamma_box->setWhatsThis(QApplication::translate("MainWindow", "<html><head/><body><p>ratio of beta_max over beta</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        label_2->setText(QApplication::translate("MainWindow", "3.0", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "0.0", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Adjust Nbeta", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "Nbeta", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        nbeta_box->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        nbeta_box->setPlaceholderText(QString());
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Auto-run", 0, QApplication::UnicodeUTF8));
        manual_run_check->setText(QApplication::translate("MainWindow", "Manual", 0, QApplication::UnicodeUTF8));
        auto_run_check->setText(QApplication::translate("MainWindow", "Auto", 0, QApplication::UnicodeUTF8));
        restore_trigger->setText(QApplication::translate("MainWindow", "Restore", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "Image Preprocess", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Noise Level", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "Path", 0, QApplication::UnicodeUTF8));
        image_path->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        path_display->setText(QString());
        add_noise_button->setText(QApplication::translate("MainWindow", "Add Noise", 0, QApplication::UnicodeUTF8));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "Noisy Image", 0, QApplication::UnicodeUTF8));
        noisy_image->setText(QString());
        label_3->setText(QApplication::translate("MainWindow", "Noise Level:", 0, QApplication::UnicodeUTF8));
        original_noise_level->setText(QString());
        groupBox_6->setTitle(QApplication::translate("MainWindow", "Restored Image using Ising Model", 0, QApplication::UnicodeUTF8));
        restore_image->setText(QString());
        label_8->setText(QApplication::translate("MainWindow", "Noise Level:", 0, QApplication::UnicodeUTF8));
        restore_noise_level->setText(QString());
        menuImage_Restoration->setTitle(QApplication::translate("MainWindow", "Image Restoration using Ising Model", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
