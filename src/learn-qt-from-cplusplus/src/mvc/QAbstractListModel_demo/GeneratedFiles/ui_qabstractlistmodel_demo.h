/********************************************************************************
** Form generated from reading UI file 'qabstractlistmodel_demo.ui'
**
** Created: Wed Apr 25 11:04:08 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QABSTRACTLISTMODEL_DEMO_H
#define UI_QABSTRACTLISTMODEL_DEMO_H

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

class Ui_QAbstractListModel_demoClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QAbstractListModel_demoClass)
    {
        if (QAbstractListModel_demoClass->objectName().isEmpty())
            QAbstractListModel_demoClass->setObjectName(QString::fromUtf8("QAbstractListModel_demoClass"));
        QAbstractListModel_demoClass->resize(600, 400);
        menuBar = new QMenuBar(QAbstractListModel_demoClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        QAbstractListModel_demoClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QAbstractListModel_demoClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QAbstractListModel_demoClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(QAbstractListModel_demoClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QAbstractListModel_demoClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QAbstractListModel_demoClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QAbstractListModel_demoClass->setStatusBar(statusBar);

        retranslateUi(QAbstractListModel_demoClass);

        QMetaObject::connectSlotsByName(QAbstractListModel_demoClass);
    } // setupUi

    void retranslateUi(QMainWindow *QAbstractListModel_demoClass)
    {
        QAbstractListModel_demoClass->setWindowTitle(QApplication::translate("QAbstractListModel_demoClass", "QAbstractListModel_demo", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QAbstractListModel_demoClass: public Ui_QAbstractListModel_demoClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QABSTRACTLISTMODEL_DEMO_H
