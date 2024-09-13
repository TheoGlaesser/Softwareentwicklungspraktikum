/********************************************************************************
** Form generated from reading UI file 'mainwindow_right.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_RIGHT_H
#define UI_MAINWINDOW_RIGHT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QPushButton *addNodeButton;
    QLineEdit *lineEditX;
    QLineEdit *lineEditY;
    QPushButton *undoButton;
    QPushButton *removeButton;
    QPushButton *makeForceButton;
    QLineEdit *lineEditX_2;
    QLineEdit *lineEditX_3;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *clearButton;
    QPushButton *solveButton;
    QPushButton *supportButton;
    QLineEdit *lineEditX_6;
    QLineEdit *lineEditX_7;
    QLineEdit *lineEditX_8;
    QLineEdit *lineEditX_9;
    QPushButton *parametersButton;
    QLineEdit *lineEditX_4;
    QLineEdit *lineEditX_5;
    QPushButton *saveButton;
    QPushButton *loadButton;
    QLabel *label_5;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_4;
    QGraphicsView *graphicsView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(30, 20, 251, 551));
        addNodeButton = new QPushButton(groupBox);
        addNodeButton->setObjectName(QString::fromUtf8("addNodeButton"));
        addNodeButton->setGeometry(QRect(90, 50, 80, 18));
        lineEditX = new QLineEdit(groupBox);
        lineEditX->setObjectName(QString::fromUtf8("lineEditX"));
        lineEditX->setGeometry(QRect(10, 20, 113, 20));
        lineEditY = new QLineEdit(groupBox);
        lineEditY->setObjectName(QString::fromUtf8("lineEditY"));
        lineEditY->setGeometry(QRect(130, 20, 113, 20));
        undoButton = new QPushButton(groupBox);
        undoButton->setObjectName(QString::fromUtf8("undoButton"));
        undoButton->setGeometry(QRect(0, 370, 80, 18));
        removeButton = new QPushButton(groupBox);
        removeButton->setObjectName(QString::fromUtf8("removeButton"));
        removeButton->setGeometry(QRect(90, 370, 80, 18));
        makeForceButton = new QPushButton(groupBox);
        makeForceButton->setObjectName(QString::fromUtf8("makeForceButton"));
        makeForceButton->setGeometry(QRect(90, 160, 80, 18));
        lineEditX_2 = new QLineEdit(groupBox);
        lineEditX_2->setObjectName(QString::fromUtf8("lineEditX_2"));
        lineEditX_2->setGeometry(QRect(50, 100, 61, 20));
        lineEditX_3 = new QLineEdit(groupBox);
        lineEditX_3->setObjectName(QString::fromUtf8("lineEditX_3"));
        lineEditX_3->setGeometry(QRect(160, 100, 61, 20));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 100, 37, 12));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(120, 100, 37, 12));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 130, 37, 12));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(120, 130, 37, 12));
        clearButton = new QPushButton(groupBox);
        clearButton->setObjectName(QString::fromUtf8("clearButton"));
        clearButton->setGeometry(QRect(170, 370, 80, 18));
        solveButton = new QPushButton(groupBox);
        solveButton->setObjectName(QString::fromUtf8("solveButton"));
        solveButton->setGeometry(QRect(80, 520, 80, 18));
        supportButton = new QPushButton(groupBox);
        supportButton->setObjectName(QString::fromUtf8("supportButton"));
        supportButton->setGeometry(QRect(90, 240, 80, 18));
        lineEditX_6 = new QLineEdit(groupBox);
        lineEditX_6->setObjectName(QString::fromUtf8("lineEditX_6"));
        lineEditX_6->setGeometry(QRect(50, 210, 51, 20));
        lineEditX_7 = new QLineEdit(groupBox);
        lineEditX_7->setObjectName(QString::fromUtf8("lineEditX_7"));
        lineEditX_7->setGeometry(QRect(150, 210, 51, 20));
        lineEditX_8 = new QLineEdit(groupBox);
        lineEditX_8->setObjectName(QString::fromUtf8("lineEditX_8"));
        lineEditX_8->setGeometry(QRect(60, 300, 51, 20));
        lineEditX_9 = new QLineEdit(groupBox);
        lineEditX_9->setObjectName(QString::fromUtf8("lineEditX_9"));
        lineEditX_9->setGeometry(QRect(130, 300, 51, 20));
        parametersButton = new QPushButton(groupBox);
        parametersButton->setObjectName(QString::fromUtf8("parametersButton"));
        parametersButton->setGeometry(QRect(80, 330, 80, 18));
        lineEditX_4 = new QLineEdit(groupBox);
        lineEditX_4->setObjectName(QString::fromUtf8("lineEditX_4"));
        lineEditX_4->setGeometry(QRect(50, 130, 61, 20));
        lineEditX_5 = new QLineEdit(groupBox);
        lineEditX_5->setObjectName(QString::fromUtf8("lineEditX_5"));
        lineEditX_5->setGeometry(QRect(160, 130, 61, 20));
        saveButton = new QPushButton(groupBox);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));
        saveButton->setGeometry(QRect(30, 400, 80, 18));
        loadButton = new QPushButton(groupBox);
        loadButton->setObjectName(QString::fromUtf8("loadButton"));
        loadButton->setGeometry(QRect(150, 400, 80, 18));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 460, 51, 21));
        checkBox = new QCheckBox(groupBox);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(110, 430, 71, 18));
        checkBox_2 = new QCheckBox(groupBox);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setGeometry(QRect(110, 460, 91, 18));
        checkBox_4 = new QCheckBox(groupBox);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));
        checkBox_4->setGeometry(QRect(110, 490, 58, 18));
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(320, 20, 441, 551));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 17));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Drawing Tools", nullptr));
        addNodeButton->setText(QCoreApplication::translate("MainWindow", "Make Points", nullptr));
        lineEditX->setText(QString());
        undoButton->setText(QCoreApplication::translate("MainWindow", "Undo", nullptr));
        removeButton->setText(QCoreApplication::translate("MainWindow", "Remove", nullptr));
        makeForceButton->setText(QCoreApplication::translate("MainWindow", "Make Force", nullptr));
        lineEditX_2->setText(QString());
        lineEditX_3->setText(QString());
        label->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Betrag", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "WInkel", nullptr));
        clearButton->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        solveButton->setText(QCoreApplication::translate("MainWindow", "Solve", nullptr));
        supportButton->setText(QCoreApplication::translate("MainWindow", "Support", nullptr));
        lineEditX_6->setText(QString());
        lineEditX_7->setText(QString());
        lineEditX_8->setText(QString());
        lineEditX_9->setText(QString());
        parametersButton->setText(QCoreApplication::translate("MainWindow", "E and A", nullptr));
        lineEditX_4->setText(QString());
        lineEditX_5->setText(QString());
        saveButton->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        loadButton->setText(QCoreApplication::translate("MainWindow", "Load", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Visibility", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "Original", nullptr));
        checkBox_2->setText(QCoreApplication::translate("MainWindow", "Displacement", nullptr));
        checkBox_4->setText(QCoreApplication::translate("MainWindow", "New", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_RIGHT_H
