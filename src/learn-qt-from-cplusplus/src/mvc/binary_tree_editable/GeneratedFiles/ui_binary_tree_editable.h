/********************************************************************************
** Form generated from reading UI file 'binary_tree_editable.ui'
**
** Created: Wed Apr 25 10:53:57 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BINARY_TREE_EDITABLE_H
#define UI_BINARY_TREE_EDITABLE_H

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

class Ui_binary_tree_editableClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *binary_tree_editableClass)
    {
        if (binary_tree_editableClass->objectName().isEmpty())
            binary_tree_editableClass->setObjectName(QString::fromUtf8("binary_tree_editableClass"));
        binary_tree_editableClass->resize(600, 400);
        menuBar = new QMenuBar(binary_tree_editableClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        binary_tree_editableClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(binary_tree_editableClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        binary_tree_editableClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(binary_tree_editableClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        binary_tree_editableClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(binary_tree_editableClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        binary_tree_editableClass->setStatusBar(statusBar);

        retranslateUi(binary_tree_editableClass);

        QMetaObject::connectSlotsByName(binary_tree_editableClass);
    } // setupUi

    void retranslateUi(QMainWindow *binary_tree_editableClass)
    {
        binary_tree_editableClass->setWindowTitle(QApplication::translate("binary_tree_editableClass", "binary_tree_editable", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class binary_tree_editableClass: public Ui_binary_tree_editableClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BINARY_TREE_EDITABLE_H
