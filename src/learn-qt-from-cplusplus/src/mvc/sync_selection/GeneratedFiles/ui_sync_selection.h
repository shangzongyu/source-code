/********************************************************************************
** Form generated from reading UI file 'sync_selection.ui'
**
** Created: Wed Apr 25 10:34:27 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYNC_SELECTION_H
#define UI_SYNC_SELECTION_H

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

class Ui_sync_selectionClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *sync_selectionClass)
    {
        if (sync_selectionClass->objectName().isEmpty())
            sync_selectionClass->setObjectName(QString::fromUtf8("sync_selectionClass"));
        sync_selectionClass->resize(600, 400);
        menuBar = new QMenuBar(sync_selectionClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        sync_selectionClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(sync_selectionClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        sync_selectionClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(sync_selectionClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        sync_selectionClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(sync_selectionClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        sync_selectionClass->setStatusBar(statusBar);

        retranslateUi(sync_selectionClass);

        QMetaObject::connectSlotsByName(sync_selectionClass);
    } // setupUi

    void retranslateUi(QMainWindow *sync_selectionClass)
    {
        sync_selectionClass->setWindowTitle(QApplication::translate("sync_selectionClass", "sync_selection", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class sync_selectionClass: public Ui_sync_selectionClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYNC_SELECTION_H
