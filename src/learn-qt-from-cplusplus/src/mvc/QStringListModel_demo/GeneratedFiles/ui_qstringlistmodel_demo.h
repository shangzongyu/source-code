/********************************************************************************
** Form generated from reading UI file 'qstringlistmodel_demo.ui'
**
** Created: Wed Apr 25 11:15:30 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QSTRINGLISTMODEL_DEMO_H
#define UI_QSTRINGLISTMODEL_DEMO_H

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

class Ui_QStringListModel_demoClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QStringListModel_demoClass)
    {
        if (QStringListModel_demoClass->objectName().isEmpty())
            QStringListModel_demoClass->setObjectName(QString::fromUtf8("QStringListModel_demoClass"));
        QStringListModel_demoClass->resize(600, 400);
        menuBar = new QMenuBar(QStringListModel_demoClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        QStringListModel_demoClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QStringListModel_demoClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QStringListModel_demoClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(QStringListModel_demoClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QStringListModel_demoClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QStringListModel_demoClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QStringListModel_demoClass->setStatusBar(statusBar);

        retranslateUi(QStringListModel_demoClass);

        QMetaObject::connectSlotsByName(QStringListModel_demoClass);
    } // setupUi

    void retranslateUi(QMainWindow *QStringListModel_demoClass)
    {
        QStringListModel_demoClass->setWindowTitle(QApplication::translate("QStringListModel_demoClass", "QStringListModel_demo", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QStringListModel_demoClass: public Ui_QStringListModel_demoClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QSTRINGLISTMODEL_DEMO_H
