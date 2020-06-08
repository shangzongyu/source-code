/********************************************************************************
** Form generated from reading UI file 'selection_monitoring.ui'
**
** Created: Wed Apr 25 10:28:44 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTION_MONITORING_H
#define UI_SELECTION_MONITORING_H

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

class Ui_selection_monitoringClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *selection_monitoringClass)
    {
        if (selection_monitoringClass->objectName().isEmpty())
            selection_monitoringClass->setObjectName(QString::fromUtf8("selection_monitoringClass"));
        selection_monitoringClass->resize(600, 400);
        menuBar = new QMenuBar(selection_monitoringClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        selection_monitoringClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(selection_monitoringClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        selection_monitoringClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(selection_monitoringClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        selection_monitoringClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(selection_monitoringClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        selection_monitoringClass->setStatusBar(statusBar);

        retranslateUi(selection_monitoringClass);

        QMetaObject::connectSlotsByName(selection_monitoringClass);
    } // setupUi

    void retranslateUi(QMainWindow *selection_monitoringClass)
    {
        selection_monitoringClass->setWindowTitle(QApplication::translate("selection_monitoringClass", "selection_monitoring", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class selection_monitoringClass: public Ui_selection_monitoringClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTION_MONITORING_H
