/********************************************************************************
** Form generated from reading UI file 'calendarwidget.ui'
**
** Created: Tue Apr 24 19:04:16 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALENDARWIDGET_H
#define UI_CALENDARWIDGET_H

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

class Ui_calendarwidgetClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *calendarwidgetClass)
    {
        if (calendarwidgetClass->objectName().isEmpty())
            calendarwidgetClass->setObjectName(QString::fromUtf8("calendarwidgetClass"));
        calendarwidgetClass->resize(600, 400);
        menuBar = new QMenuBar(calendarwidgetClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        calendarwidgetClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(calendarwidgetClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        calendarwidgetClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(calendarwidgetClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        calendarwidgetClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(calendarwidgetClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        calendarwidgetClass->setStatusBar(statusBar);

        retranslateUi(calendarwidgetClass);

        QMetaObject::connectSlotsByName(calendarwidgetClass);
    } // setupUi

    void retranslateUi(QMainWindow *calendarwidgetClass)
    {
        calendarwidgetClass->setWindowTitle(QApplication::translate("calendarwidgetClass", "calendarwidget", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class calendarwidgetClass: public Ui_calendarwidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALENDARWIDGET_H
