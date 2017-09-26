/********************************************************************************
** Form generated from reading UI file 'qtablewidget_demo.ui'
**
** Created: Wed Apr 25 10:21:57 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTABLEWIDGET_DEMO_H
#define UI_QTABLEWIDGET_DEMO_H

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

class Ui_QTableWidget_demoClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QTableWidget_demoClass)
    {
        if (QTableWidget_demoClass->objectName().isEmpty())
            QTableWidget_demoClass->setObjectName(QString::fromUtf8("QTableWidget_demoClass"));
        QTableWidget_demoClass->resize(600, 400);
        menuBar = new QMenuBar(QTableWidget_demoClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        QTableWidget_demoClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QTableWidget_demoClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QTableWidget_demoClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(QTableWidget_demoClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QTableWidget_demoClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QTableWidget_demoClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QTableWidget_demoClass->setStatusBar(statusBar);

        retranslateUi(QTableWidget_demoClass);

        QMetaObject::connectSlotsByName(QTableWidget_demoClass);
    } // setupUi

    void retranslateUi(QMainWindow *QTableWidget_demoClass)
    {
        QTableWidget_demoClass->setWindowTitle(QApplication::translate("QTableWidget_demoClass", "QTableWidget_demo", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QTableWidget_demoClass: public Ui_QTableWidget_demoClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTABLEWIDGET_DEMO_H
