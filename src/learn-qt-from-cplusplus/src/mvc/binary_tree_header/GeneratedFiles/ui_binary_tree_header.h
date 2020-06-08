/********************************************************************************
** Form generated from reading UI file 'binary_tree_header.ui'
**
** Created: Wed Apr 25 10:55:18 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BINARY_TREE_HEADER_H
#define UI_BINARY_TREE_HEADER_H

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

class Ui_binary_tree_headerClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *binary_tree_headerClass)
    {
        if (binary_tree_headerClass->objectName().isEmpty())
            binary_tree_headerClass->setObjectName(QString::fromUtf8("binary_tree_headerClass"));
        binary_tree_headerClass->resize(600, 400);
        menuBar = new QMenuBar(binary_tree_headerClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        binary_tree_headerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(binary_tree_headerClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        binary_tree_headerClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(binary_tree_headerClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        binary_tree_headerClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(binary_tree_headerClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        binary_tree_headerClass->setStatusBar(statusBar);

        retranslateUi(binary_tree_headerClass);

        QMetaObject::connectSlotsByName(binary_tree_headerClass);
    } // setupUi

    void retranslateUi(QMainWindow *binary_tree_headerClass)
    {
        binary_tree_headerClass->setWindowTitle(QApplication::translate("binary_tree_headerClass", "binary_tree_header", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class binary_tree_headerClass: public Ui_binary_tree_headerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BINARY_TREE_HEADER_H
