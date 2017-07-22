/********************************************************************************
** Form generated from reading UI file 'find_dialog.ui'
**
** Created: Tue Apr 24 20:02:25 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIND_DIALOG_H
#define UI_FIND_DIALOG_H

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

class Ui_find_dialogClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *find_dialogClass)
    {
        if (find_dialogClass->objectName().isEmpty())
            find_dialogClass->setObjectName(QString::fromUtf8("find_dialogClass"));
        find_dialogClass->resize(600, 400);
        menuBar = new QMenuBar(find_dialogClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        find_dialogClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(find_dialogClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        find_dialogClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(find_dialogClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        find_dialogClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(find_dialogClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        find_dialogClass->setStatusBar(statusBar);

        retranslateUi(find_dialogClass);

        QMetaObject::connectSlotsByName(find_dialogClass);
    } // setupUi

    void retranslateUi(QMainWindow *find_dialogClass)
    {
        find_dialogClass->setWindowTitle(QApplication::translate("find_dialogClass", "find_dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class find_dialogClass: public Ui_find_dialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIND_DIALOG_H
