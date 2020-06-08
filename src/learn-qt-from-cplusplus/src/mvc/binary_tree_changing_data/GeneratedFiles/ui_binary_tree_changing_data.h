/********************************************************************************
** Form generated from reading UI file 'binary_tree_changing_data.ui'
**
** Created: Wed Apr 25 10:52:30 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BINARY_TREE_CHANGING_DATA_H
#define UI_BINARY_TREE_CHANGING_DATA_H

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

class Ui_binary_tree_changing_dataClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *binary_tree_changing_dataClass)
    {
        if (binary_tree_changing_dataClass->objectName().isEmpty())
            binary_tree_changing_dataClass->setObjectName(QString::fromUtf8("binary_tree_changing_dataClass"));
        binary_tree_changing_dataClass->resize(600, 400);
        menuBar = new QMenuBar(binary_tree_changing_dataClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        binary_tree_changing_dataClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(binary_tree_changing_dataClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        binary_tree_changing_dataClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(binary_tree_changing_dataClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        binary_tree_changing_dataClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(binary_tree_changing_dataClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        binary_tree_changing_dataClass->setStatusBar(statusBar);

        retranslateUi(binary_tree_changing_dataClass);

        QMetaObject::connectSlotsByName(binary_tree_changing_dataClass);
    } // setupUi

    void retranslateUi(QMainWindow *binary_tree_changing_dataClass)
    {
        binary_tree_changing_dataClass->setWindowTitle(QApplication::translate("binary_tree_changing_dataClass", "binary_tree_changing_data", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class binary_tree_changing_dataClass: public Ui_binary_tree_changing_dataClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BINARY_TREE_CHANGING_DATA_H
