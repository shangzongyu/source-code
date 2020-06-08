/********************************************************************************
** Form generated from reading UI file 'qtreewidget_demo.ui'
**
** Created: Wed Apr 25 10:24:05 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTREEWIDGET_DEMO_H
#define UI_QTREEWIDGET_DEMO_H

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

class Ui_QTreeWidget_demoClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QTreeWidget_demoClass)
    {
        if (QTreeWidget_demoClass->objectName().isEmpty())
            QTreeWidget_demoClass->setObjectName(QString::fromUtf8("QTreeWidget_demoClass"));
        QTreeWidget_demoClass->resize(600, 400);
        menuBar = new QMenuBar(QTreeWidget_demoClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        QTreeWidget_demoClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QTreeWidget_demoClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QTreeWidget_demoClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(QTreeWidget_demoClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QTreeWidget_demoClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QTreeWidget_demoClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QTreeWidget_demoClass->setStatusBar(statusBar);

        retranslateUi(QTreeWidget_demoClass);

        QMetaObject::connectSlotsByName(QTreeWidget_demoClass);
    } // setupUi

    void retranslateUi(QMainWindow *QTreeWidget_demoClass)
    {
        QTreeWidget_demoClass->setWindowTitle(QApplication::translate("QTreeWidget_demoClass", "QTreeWidget_demo", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QTreeWidget_demoClass: public Ui_QTreeWidget_demoClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTREEWIDGET_DEMO_H
