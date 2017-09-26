/********************************************************************************
** Form generated from reading UI file 'binary_tree.ui'
**
** Created: Wed Apr 25 10:50:36 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BINARY_TREE_H
#define UI_BINARY_TREE_H

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

class Ui_binary_treeClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *binary_treeClass)
    {
        if (binary_treeClass->objectName().isEmpty())
            binary_treeClass->setObjectName(QString::fromUtf8("binary_treeClass"));
        binary_treeClass->resize(600, 400);
        menuBar = new QMenuBar(binary_treeClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        binary_treeClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(binary_treeClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        binary_treeClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(binary_treeClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        binary_treeClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(binary_treeClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        binary_treeClass->setStatusBar(statusBar);

        retranslateUi(binary_treeClass);

        QMetaObject::connectSlotsByName(binary_treeClass);
    } // setupUi

    void retranslateUi(QMainWindow *binary_treeClass)
    {
        binary_treeClass->setWindowTitle(QApplication::translate("binary_treeClass", "binary_tree", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class binary_treeClass: public Ui_binary_treeClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BINARY_TREE_H
