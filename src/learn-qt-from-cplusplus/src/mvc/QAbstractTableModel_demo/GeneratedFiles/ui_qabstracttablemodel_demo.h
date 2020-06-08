/********************************************************************************
** Form generated from reading UI file 'qabstracttablemodel_demo.ui'
**
** Created: Wed Apr 25 11:06:53 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QABSTRACTTABLEMODEL_DEMO_H
#define UI_QABSTRACTTABLEMODEL_DEMO_H

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

class Ui_QAbstractTableModel_demoClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QAbstractTableModel_demoClass)
    {
        if (QAbstractTableModel_demoClass->objectName().isEmpty())
            QAbstractTableModel_demoClass->setObjectName(QString::fromUtf8("QAbstractTableModel_demoClass"));
        QAbstractTableModel_demoClass->resize(600, 400);
        menuBar = new QMenuBar(QAbstractTableModel_demoClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        QAbstractTableModel_demoClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QAbstractTableModel_demoClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QAbstractTableModel_demoClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(QAbstractTableModel_demoClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QAbstractTableModel_demoClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QAbstractTableModel_demoClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QAbstractTableModel_demoClass->setStatusBar(statusBar);

        retranslateUi(QAbstractTableModel_demoClass);

        QMetaObject::connectSlotsByName(QAbstractTableModel_demoClass);
    } // setupUi

    void retranslateUi(QMainWindow *QAbstractTableModel_demoClass)
    {
        QAbstractTableModel_demoClass->setWindowTitle(QApplication::translate("QAbstractTableModel_demoClass", "QAbstractTableModel_demo", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QAbstractTableModel_demoClass: public Ui_QAbstractTableModel_demoClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QABSTRACTTABLEMODEL_DEMO_H
