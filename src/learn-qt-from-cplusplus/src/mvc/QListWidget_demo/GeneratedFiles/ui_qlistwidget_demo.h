/********************************************************************************
** Form generated from reading UI file 'qlistwidget_demo.ui'
**
** Created: Wed Apr 25 11:09:57 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QLISTWIDGET_DEMO_H
#define UI_QLISTWIDGET_DEMO_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QListWidget_demoClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QListWidget_demoClass)
    {
        if (QListWidget_demoClass->objectName().isEmpty())
            QListWidget_demoClass->setObjectName(QString::fromUtf8("QListWidget_demoClass"));
        QListWidget_demoClass->resize(600, 400);
        menuBar = new QMenuBar(QListWidget_demoClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        QListWidget_demoClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QListWidget_demoClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QListWidget_demoClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(QListWidget_demoClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QListWidget_demoClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QListWidget_demoClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QListWidget_demoClass->setStatusBar(statusBar);

        retranslateUi(QListWidget_demoClass);

        QMetaObject::connectSlotsByName(QListWidget_demoClass);
    } // setupUi

    void retranslateUi(QMainWindow *QListWidget_demoClass)
    {
        QListWidget_demoClass->setWindowTitle(QApplication::translate("QListWidget_demoClass", "QListWidget_demo", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QListWidget_demoClass: public Ui_QListWidget_demoClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QLISTWIDGET_DEMO_H
