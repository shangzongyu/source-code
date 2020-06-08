/********************************************************************************
** Form generated from reading UI file 'undoframework.ui'
**
** Created: Wed Apr 25 09:39:32 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UNDOFRAMEWORK_H
#define UI_UNDOFRAMEWORK_H

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

class Ui_undoframeworkClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *undoframeworkClass)
    {
        if (undoframeworkClass->objectName().isEmpty())
            undoframeworkClass->setObjectName(QString::fromUtf8("undoframeworkClass"));
        undoframeworkClass->resize(600, 400);
        menuBar = new QMenuBar(undoframeworkClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        undoframeworkClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(undoframeworkClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        undoframeworkClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(undoframeworkClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        undoframeworkClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(undoframeworkClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        undoframeworkClass->setStatusBar(statusBar);

        retranslateUi(undoframeworkClass);

        QMetaObject::connectSlotsByName(undoframeworkClass);
    } // setupUi

    void retranslateUi(QMainWindow *undoframeworkClass)
    {
        undoframeworkClass->setWindowTitle(QApplication::translate("undoframeworkClass", "undoframework", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class undoframeworkClass: public Ui_undoframeworkClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UNDOFRAMEWORK_H
