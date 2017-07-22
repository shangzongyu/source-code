/********************************************************************************
** Form generated from reading UI file 'item_roles.ui'
**
** Created: Wed Apr 25 11:01:47 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ITEM_ROLES_H
#define UI_ITEM_ROLES_H

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

class Ui_item_rolesClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *item_rolesClass)
    {
        if (item_rolesClass->objectName().isEmpty())
            item_rolesClass->setObjectName(QString::fromUtf8("item_rolesClass"));
        item_rolesClass->resize(600, 400);
        menuBar = new QMenuBar(item_rolesClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        item_rolesClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(item_rolesClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        item_rolesClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(item_rolesClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        item_rolesClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(item_rolesClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        item_rolesClass->setStatusBar(statusBar);

        retranslateUi(item_rolesClass);

        QMetaObject::connectSlotsByName(item_rolesClass);
    } // setupUi

    void retranslateUi(QMainWindow *item_rolesClass)
    {
        item_rolesClass->setWindowTitle(QApplication::translate("item_rolesClass", "item_roles", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class item_rolesClass: public Ui_item_rolesClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ITEM_ROLES_H
