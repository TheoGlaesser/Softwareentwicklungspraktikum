/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QSplitter *splitter;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_4;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_6;
    QLineEdit *lineEditX;
    QLabel *label_7;
    QLineEdit *lineEditY;
    QPushButton *addNodeButton;
    QFrame *frame;
    QSpacerItem *horizontalSpacer;
    QFrame *line_2;
    QFrame *line_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *lineEditX_2;
    QLabel *label_2;
    QLineEdit *lineEditX_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *lineEditX_4;
    QLabel *label_4;
    QLineEdit *lineEditX_5;
    QPushButton *makeForceButton;
    QFrame *line_4;
    QSpacerItem *horizontalSpacer_2;
    QFrame *line_6;
    QGridLayout *gridLayout_3;
    QLabel *label_9;
    QLineEdit *lineEdit_x_pos;
    QLineEdit *lineEditX_y_pos;
    QLabel *label_11;
    QHBoxLayout *horizontalLayout_9;
    QCheckBox *checkBox_y_fixed_2;
    QCheckBox *checkBox_y_fixed;
    QPushButton *supportButton;
    QFrame *line_7;
    QSpacerItem *horizontalSpacer_8;
    QFrame *line_8;
    QHBoxLayout *horizontalLayout_5;
    QCheckBox *checkBox_3;
    QPushButton *pushButton;
    QLineEdit *lineEditX_8;
    QPushButton *parametersButton;
    QLineEdit *lineEditX_9;
    QHBoxLayout *horizontalLayout_6;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton_itemInfo;
    QFrame *line_9;
    QFrame *line_10;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *saveButton;
    QPushButton *removeButton;
    QPushButton *solveButton;
    QPushButton *undoButton;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_10;
    QPushButton *clearButton;
    QPushButton *loadButton;
    QFrame *line_11;
    QFrame *line_12;
    QFrame *line;
    QFrame *line_14;
    QFrame *line_15;
    QFrame *line_16;
    QFrame *line_5;
    QSpacerItem *horizontalSpacer_11;
    QFrame *line_13;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_5;
    QVBoxLayout *verticalLayout;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_4;
    QHBoxLayout *horizontalLayout_8;
    QDoubleSpinBox *zoom_scale_spin_box;
    QPushButton *button_zoom_in;
    QPushButton *button_zoom_out;
    QGraphicsView *graphicsView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(860, 645);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        groupBox = new QGroupBox(splitter);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_3 = new QVBoxLayout(groupBox);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        scrollArea = new QScrollArea(groupBox);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 673, 863));
        gridLayout_4 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_6 = new QLabel(scrollAreaWidgetContents);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout->addWidget(label_6);

        lineEditX = new QLineEdit(scrollAreaWidgetContents);
        lineEditX->setObjectName(QString::fromUtf8("lineEditX"));

        horizontalLayout->addWidget(lineEditX);

        label_7 = new QLabel(scrollAreaWidgetContents);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout->addWidget(label_7);

        lineEditY = new QLineEdit(scrollAreaWidgetContents);
        lineEditY->setObjectName(QString::fromUtf8("lineEditY"));

        horizontalLayout->addWidget(lineEditY);


        verticalLayout_2->addLayout(horizontalLayout);

        addNodeButton = new QPushButton(scrollAreaWidgetContents);
        addNodeButton->setObjectName(QString::fromUtf8("addNodeButton"));
        QFont font;
        font.setBold(true);
        addNodeButton->setFont(font);

        verticalLayout_2->addWidget(addNodeButton);

        frame = new QFrame(scrollAreaWidgetContents);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        verticalLayout_2->addWidget(frame);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_2->addItem(horizontalSpacer);

        line_2 = new QFrame(scrollAreaWidgetContents);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_2);

        line_3 = new QFrame(scrollAreaWidgetContents);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(scrollAreaWidgetContents);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        lineEditX_2 = new QLineEdit(scrollAreaWidgetContents);
        lineEditX_2->setObjectName(QString::fromUtf8("lineEditX_2"));

        horizontalLayout_2->addWidget(lineEditX_2);

        label_2 = new QLabel(scrollAreaWidgetContents);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        lineEditX_3 = new QLineEdit(scrollAreaWidgetContents);
        lineEditX_3->setObjectName(QString::fromUtf8("lineEditX_3"));

        horizontalLayout_2->addWidget(lineEditX_3);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(scrollAreaWidgetContents);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        lineEditX_4 = new QLineEdit(scrollAreaWidgetContents);
        lineEditX_4->setObjectName(QString::fromUtf8("lineEditX_4"));

        horizontalLayout_3->addWidget(lineEditX_4);

        label_4 = new QLabel(scrollAreaWidgetContents);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_3->addWidget(label_4);

        lineEditX_5 = new QLineEdit(scrollAreaWidgetContents);
        lineEditX_5->setObjectName(QString::fromUtf8("lineEditX_5"));

        horizontalLayout_3->addWidget(lineEditX_5);


        verticalLayout_2->addLayout(horizontalLayout_3);

        makeForceButton = new QPushButton(scrollAreaWidgetContents);
        makeForceButton->setObjectName(QString::fromUtf8("makeForceButton"));
        makeForceButton->setFont(font);

        verticalLayout_2->addWidget(makeForceButton);

        line_4 = new QFrame(scrollAreaWidgetContents);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_4);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        verticalLayout_2->addItem(horizontalSpacer_2);

        line_6 = new QFrame(scrollAreaWidgetContents);
        line_6->setObjectName(QString::fromUtf8("line_6"));
        line_6->setFrameShape(QFrame::HLine);
        line_6->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_6);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(-1, 0, -1, -1);
        label_9 = new QLabel(scrollAreaWidgetContents);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_3->addWidget(label_9, 0, 0, 1, 1);

        lineEdit_x_pos = new QLineEdit(scrollAreaWidgetContents);
        lineEdit_x_pos->setObjectName(QString::fromUtf8("lineEdit_x_pos"));

        gridLayout_3->addWidget(lineEdit_x_pos, 0, 1, 1, 1);

        lineEditX_y_pos = new QLineEdit(scrollAreaWidgetContents);
        lineEditX_y_pos->setObjectName(QString::fromUtf8("lineEditX_y_pos"));

        gridLayout_3->addWidget(lineEditX_y_pos, 0, 4, 1, 1);

        label_11 = new QLabel(scrollAreaWidgetContents);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_3->addWidget(label_11, 0, 3, 1, 1);


        verticalLayout_2->addLayout(gridLayout_3);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(-1, -1, -1, 0);
        checkBox_y_fixed_2 = new QCheckBox(scrollAreaWidgetContents);
        checkBox_y_fixed_2->setObjectName(QString::fromUtf8("checkBox_y_fixed_2"));
        checkBox_y_fixed_2->setSizeIncrement(QSize(120, 18));
        checkBox_y_fixed_2->setCursor(QCursor(Qt::BusyCursor));

        horizontalLayout_9->addWidget(checkBox_y_fixed_2);

        checkBox_y_fixed = new QCheckBox(scrollAreaWidgetContents);
        checkBox_y_fixed->setObjectName(QString::fromUtf8("checkBox_y_fixed"));

        horizontalLayout_9->addWidget(checkBox_y_fixed);


        verticalLayout_2->addLayout(horizontalLayout_9);

        supportButton = new QPushButton(scrollAreaWidgetContents);
        supportButton->setObjectName(QString::fromUtf8("supportButton"));
        supportButton->setFont(font);

        verticalLayout_2->addWidget(supportButton);

        line_7 = new QFrame(scrollAreaWidgetContents);
        line_7->setObjectName(QString::fromUtf8("line_7"));
        line_7->setFrameShape(QFrame::HLine);
        line_7->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_7);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        verticalLayout_2->addItem(horizontalSpacer_8);

        line_8 = new QFrame(scrollAreaWidgetContents);
        line_8->setObjectName(QString::fromUtf8("line_8"));
        line_8->setFrameShape(QFrame::HLine);
        line_8->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_8);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        checkBox_3 = new QCheckBox(scrollAreaWidgetContents);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));

        horizontalLayout_5->addWidget(checkBox_3);

        pushButton = new QPushButton(scrollAreaWidgetContents);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_5->addWidget(pushButton);

        lineEditX_8 = new QLineEdit(scrollAreaWidgetContents);
        lineEditX_8->setObjectName(QString::fromUtf8("lineEditX_8"));

        horizontalLayout_5->addWidget(lineEditX_8);

        parametersButton = new QPushButton(scrollAreaWidgetContents);
        parametersButton->setObjectName(QString::fromUtf8("parametersButton"));

        horizontalLayout_5->addWidget(parametersButton);

        lineEditX_9 = new QLineEdit(scrollAreaWidgetContents);
        lineEditX_9->setObjectName(QString::fromUtf8("lineEditX_9"));

        horizontalLayout_5->addWidget(lineEditX_9);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));

        verticalLayout_2->addLayout(horizontalLayout_6);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        pushButton_itemInfo = new QPushButton(scrollAreaWidgetContents);
        pushButton_itemInfo->setObjectName(QString::fromUtf8("pushButton_itemInfo"));

        gridLayout_2->addWidget(pushButton_itemInfo, 6, 1, 1, 1);

        line_9 = new QFrame(scrollAreaWidgetContents);
        line_9->setObjectName(QString::fromUtf8("line_9"));
        line_9->setFrameShape(QFrame::HLine);
        line_9->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(line_9, 2, 0, 1, 1);

        line_10 = new QFrame(scrollAreaWidgetContents);
        line_10->setObjectName(QString::fromUtf8("line_10"));
        line_10->setFrameShape(QFrame::HLine);
        line_10->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(line_10, 4, 0, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_9, 3, 0, 1, 2);

        saveButton = new QPushButton(scrollAreaWidgetContents);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));

        gridLayout_2->addWidget(saveButton, 11, 0, 1, 1);

        removeButton = new QPushButton(scrollAreaWidgetContents);
        removeButton->setObjectName(QString::fromUtf8("removeButton"));

        gridLayout_2->addWidget(removeButton, 5, 1, 1, 1);

        solveButton = new QPushButton(scrollAreaWidgetContents);
        solveButton->setObjectName(QString::fromUtf8("solveButton"));
        solveButton->setFont(font);

        gridLayout_2->addWidget(solveButton, 0, 0, 1, 2);

        undoButton = new QPushButton(scrollAreaWidgetContents);
        undoButton->setObjectName(QString::fromUtf8("undoButton"));

        gridLayout_2->addWidget(undoButton, 5, 0, 1, 1);

        pushButton_2 = new QPushButton(scrollAreaWidgetContents);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        gridLayout_2->addWidget(pushButton_2, 12, 1, 1, 1);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_10, 9, 0, 1, 2);

        clearButton = new QPushButton(scrollAreaWidgetContents);
        clearButton->setObjectName(QString::fromUtf8("clearButton"));

        gridLayout_2->addWidget(clearButton, 6, 0, 1, 1);

        loadButton = new QPushButton(scrollAreaWidgetContents);
        loadButton->setObjectName(QString::fromUtf8("loadButton"));

        gridLayout_2->addWidget(loadButton, 12, 0, 1, 1);

        line_11 = new QFrame(scrollAreaWidgetContents);
        line_11->setObjectName(QString::fromUtf8("line_11"));
        line_11->setFrameShape(QFrame::HLine);
        line_11->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(line_11, 8, 0, 1, 1);

        line_12 = new QFrame(scrollAreaWidgetContents);
        line_12->setObjectName(QString::fromUtf8("line_12"));
        line_12->setFrameShape(QFrame::HLine);
        line_12->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(line_12, 10, 0, 1, 1);

        line = new QFrame(scrollAreaWidgetContents);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(line, 10, 1, 1, 1);

        line_14 = new QFrame(scrollAreaWidgetContents);
        line_14->setObjectName(QString::fromUtf8("line_14"));
        line_14->setFrameShape(QFrame::HLine);
        line_14->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(line_14, 4, 1, 1, 1);

        line_15 = new QFrame(scrollAreaWidgetContents);
        line_15->setObjectName(QString::fromUtf8("line_15"));
        line_15->setFrameShape(QFrame::HLine);
        line_15->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(line_15, 2, 1, 1, 1);

        line_16 = new QFrame(scrollAreaWidgetContents);
        line_16->setObjectName(QString::fromUtf8("line_16"));
        line_16->setFrameShape(QFrame::HLine);
        line_16->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(line_16, 8, 1, 1, 1);


        verticalLayout_2->addLayout(gridLayout_2);

        line_5 = new QFrame(scrollAreaWidgetContents);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_5);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        verticalLayout_2->addItem(horizontalSpacer_11);

        line_13 = new QFrame(scrollAreaWidgetContents);
        line_13->setObjectName(QString::fromUtf8("line_13"));
        line_13->setFrameShape(QFrame::HLine);
        line_13->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_13);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_5 = new QLabel(scrollAreaWidgetContents);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setToolTipDuration(12);
        label_5->setFrameShape(QFrame::StyledPanel);

        horizontalLayout_7->addWidget(label_5);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        checkBox = new QCheckBox(scrollAreaWidgetContents);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        verticalLayout->addWidget(checkBox);

        checkBox_2 = new QCheckBox(scrollAreaWidgetContents);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));

        verticalLayout->addWidget(checkBox_2);

        checkBox_4 = new QCheckBox(scrollAreaWidgetContents);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));

        verticalLayout->addWidget(checkBox_4);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        zoom_scale_spin_box = new QDoubleSpinBox(scrollAreaWidgetContents);
        zoom_scale_spin_box->setObjectName(QString::fromUtf8("zoom_scale_spin_box"));
        zoom_scale_spin_box->setContextMenuPolicy(Qt::DefaultContextMenu);
        zoom_scale_spin_box->setDecimals(1);
        zoom_scale_spin_box->setMinimum(1.100000000000000);
        zoom_scale_spin_box->setMaximum(3.000000000000000);
        zoom_scale_spin_box->setSingleStep(0.100000000000000);

        horizontalLayout_8->addWidget(zoom_scale_spin_box);

        button_zoom_in = new QPushButton(scrollAreaWidgetContents);
        button_zoom_in->setObjectName(QString::fromUtf8("button_zoom_in"));

        horizontalLayout_8->addWidget(button_zoom_in);

        button_zoom_out = new QPushButton(scrollAreaWidgetContents);
        button_zoom_out->setObjectName(QString::fromUtf8("button_zoom_out"));

        horizontalLayout_8->addWidget(button_zoom_out);


        verticalLayout->addLayout(horizontalLayout_8);


        horizontalLayout_7->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout_7);


        gridLayout_4->addLayout(verticalLayout_2, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_3->addWidget(scrollArea);

        splitter->addWidget(groupBox);
        graphicsView = new QGraphicsView(splitter);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        graphicsView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        splitter->addWidget(graphicsView);

        gridLayout->addWidget(splitter, 0, 2, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 860, 22));
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
        label_6->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        lineEditX->setText(QString());
        label_7->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        addNodeButton->setText(QCoreApplication::translate("MainWindow", "Make Point", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        lineEditX_2->setText(QString());
        label_2->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        lineEditX_3->setText(QString());
        label_3->setText(QCoreApplication::translate("MainWindow", "Amount", nullptr));
        lineEditX_4->setText(QString());
        label_4->setText(QCoreApplication::translate("MainWindow", "Angle", nullptr));
        lineEditX_5->setText(QString());
        makeForceButton->setText(QCoreApplication::translate("MainWindow", "Make Force", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "xPosition", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "yPosition", nullptr));
        checkBox_y_fixed_2->setText(QCoreApplication::translate("MainWindow", "Fixed x", nullptr));
        checkBox_y_fixed->setText(QCoreApplication::translate("MainWindow", "Fixed y", nullptr));
        supportButton->setText(QCoreApplication::translate("MainWindow", "Make Support", nullptr));
        checkBox_3->setText(QCoreApplication::translate("MainWindow", "Linear", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "set A", nullptr));
        lineEditX_8->setText(QString());
        parametersButton->setText(QCoreApplication::translate("MainWindow", "set E", nullptr));
        lineEditX_9->setText(QString());
        pushButton_itemInfo->setText(QCoreApplication::translate("MainWindow", "Item Info", nullptr));
        saveButton->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        removeButton->setText(QCoreApplication::translate("MainWindow", "Remove", nullptr));
        solveButton->setText(QCoreApplication::translate("MainWindow", "Solve", nullptr));
        undoButton->setText(QCoreApplication::translate("MainWindow", "Undo", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Graphical Export", nullptr));
        clearButton->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        loadButton->setText(QCoreApplication::translate("MainWindow", "Load", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Visibility", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "Original", nullptr));
        checkBox_2->setText(QCoreApplication::translate("MainWindow", "Displacement", nullptr));
        checkBox_4->setText(QCoreApplication::translate("MainWindow", "show result", nullptr));
        button_zoom_in->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        button_zoom_out->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
