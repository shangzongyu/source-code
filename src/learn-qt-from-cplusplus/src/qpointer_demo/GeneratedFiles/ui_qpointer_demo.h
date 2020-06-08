/********************************************************************************
** Form generated from reading UI file 'qpointer_demo.ui'
**
** Created: Wed Apr 25 08:21:03 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QPOINTER_DEMO_H
#define UI_QPOINTER_DEMO_H

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

class Ui_qpointer_demoClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *qpointer_demoClass)
    {
        if (qpointer_demoClass->objectName().isEmpty())
            qpointer_demoClass->setObjectName(QString::fromUtf8("qpointer_demoClass"));
        qpointer_demoClass->resize(600, 400);
        menuBar = new QMenuBar(qpointer_demoClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        qpointer_demoClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(qpointer_demoClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        qpointer_demoClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(qpointer_demoClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        qpointer_demoClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(qpointer_demoClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        qpointer_demoClass->setStatusBar(statusBar);

        retranslateUi(qpointer_demoClass);

        QMetaObject::connectSlotsByName(qpointer_demoClass);
    } // setupUi

    void retranslateUi(QMainWindow *qpointer_demoClass)
    {
        qpointer_demoClass->setWindowTitle(QApplication::translate("qpointer_demoClass", "qpointer_demo", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class qpointer_demoClass: public Ui_qpointer_demoClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QPOINTER_DEMO_H
