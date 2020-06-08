/********************************************************************************
** Form generated from reading UI file 'qcolumnview_demo.ui'
**
** Created: Wed Apr 25 11:08:40 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QCOLUMNVIEW_DEMO_H
#define UI_QCOLUMNVIEW_DEMO_H

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

class Ui_QColumnView_demoClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QColumnView_demoClass)
    {
        if (QColumnView_demoClass->objectName().isEmpty())
            QColumnView_demoClass->setObjectName(QString::fromUtf8("QColumnView_demoClass"));
        QColumnView_demoClass->resize(600, 400);
        menuBar = new QMenuBar(QColumnView_demoClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        QColumnView_demoClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QColumnView_demoClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QColumnView_demoClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(QColumnView_demoClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QColumnView_demoClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QColumnView_demoClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QColumnView_demoClass->setStatusBar(statusBar);

        retranslateUi(QColumnView_demoClass);

        QMetaObject::connectSlotsByName(QColumnView_demoClass);
    } // setupUi

    void retranslateUi(QMainWindow *QColumnView_demoClass)
    {
        QColumnView_demoClass->setWindowTitle(QApplication::translate("QColumnView_demoClass", "QColumnView_demo", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QColumnView_demoClass: public Ui_QColumnView_demoClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QCOLUMNVIEW_DEMO_H
