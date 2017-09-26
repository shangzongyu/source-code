/********************************************************************************
** Form generated from reading UI file 'qstandarditemmodel_demo.ui'
**
** Created: Wed Apr 25 11:12:51 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QSTANDARDITEMMODEL_DEMO_H
#define UI_QSTANDARDITEMMODEL_DEMO_H

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

class Ui_QStandardItemModel_demoClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QStandardItemModel_demoClass)
    {
        if (QStandardItemModel_demoClass->objectName().isEmpty())
            QStandardItemModel_demoClass->setObjectName(QString::fromUtf8("QStandardItemModel_demoClass"));
        QStandardItemModel_demoClass->resize(600, 400);
        menuBar = new QMenuBar(QStandardItemModel_demoClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        QStandardItemModel_demoClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QStandardItemModel_demoClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QStandardItemModel_demoClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(QStandardItemModel_demoClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QStandardItemModel_demoClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QStandardItemModel_demoClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QStandardItemModel_demoClass->setStatusBar(statusBar);

        retranslateUi(QStandardItemModel_demoClass);

        QMetaObject::connectSlotsByName(QStandardItemModel_demoClass);
    } // setupUi

    void retranslateUi(QMainWindow *QStandardItemModel_demoClass)
    {
        QStandardItemModel_demoClass->setWindowTitle(QApplication::translate("QStandardItemModel_demoClass", "QStandardItemModel_demo", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QStandardItemModel_demoClass: public Ui_QStandardItemModel_demoClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QSTANDARDITEMMODEL_DEMO_H
