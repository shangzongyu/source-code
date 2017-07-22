/********************************************************************************
** Form generated from reading UI file 'file_system.ui'
**
** Created: Wed Apr 25 10:58:20 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILE_SYSTEM_H
#define UI_FILE_SYSTEM_H

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

class Ui_file_systemClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *file_systemClass)
    {
        if (file_systemClass->objectName().isEmpty())
            file_systemClass->setObjectName(QString::fromUtf8("file_systemClass"));
        file_systemClass->resize(600, 400);
        menuBar = new QMenuBar(file_systemClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        file_systemClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(file_systemClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        file_systemClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(file_systemClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        file_systemClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(file_systemClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        file_systemClass->setStatusBar(statusBar);

        retranslateUi(file_systemClass);

        QMetaObject::connectSlotsByName(file_systemClass);
    } // setupUi

    void retranslateUi(QMainWindow *file_systemClass)
    {
        file_systemClass->setWindowTitle(QApplication::translate("file_systemClass", "file_system", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class file_systemClass: public Ui_file_systemClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILE_SYSTEM_H
