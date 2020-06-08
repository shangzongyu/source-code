/********************************************************************************
** Form generated from reading UI file 'binary_tree_more_role.ui'
**
** Created: Wed Apr 25 10:56:57 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BINARY_TREE_MORE_ROLE_H
#define UI_BINARY_TREE_MORE_ROLE_H

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

class Ui_binary_tree_more_roleClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *binary_tree_more_roleClass)
    {
        if (binary_tree_more_roleClass->objectName().isEmpty())
            binary_tree_more_roleClass->setObjectName(QString::fromUtf8("binary_tree_more_roleClass"));
        binary_tree_more_roleClass->resize(600, 400);
        menuBar = new QMenuBar(binary_tree_more_roleClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        binary_tree_more_roleClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(binary_tree_more_roleClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        binary_tree_more_roleClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(binary_tree_more_roleClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        binary_tree_more_roleClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(binary_tree_more_roleClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        binary_tree_more_roleClass->setStatusBar(statusBar);

        retranslateUi(binary_tree_more_roleClass);

        QMetaObject::connectSlotsByName(binary_tree_more_roleClass);
    } // setupUi

    void retranslateUi(QMainWindow *binary_tree_more_roleClass)
    {
        binary_tree_more_roleClass->setWindowTitle(QApplication::translate("binary_tree_more_roleClass", "binary_tree_more_role", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class binary_tree_more_roleClass: public Ui_binary_tree_more_roleClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BINARY_TREE_MORE_ROLE_H
