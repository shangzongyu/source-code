/********************************************************************************
** Form generated from reading UI file 'spinboxdelegate.ui'
**
** Created: Wed Apr 25 10:32:21 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPINBOXDELEGATE_H
#define UI_SPINBOXDELEGATE_H

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

class Ui_spinboxdelegateClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *spinboxdelegateClass)
    {
        if (spinboxdelegateClass->objectName().isEmpty())
            spinboxdelegateClass->setObjectName(QString::fromUtf8("spinboxdelegateClass"));
        spinboxdelegateClass->resize(600, 400);
        menuBar = new QMenuBar(spinboxdelegateClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        spinboxdelegateClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(spinboxdelegateClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        spinboxdelegateClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(spinboxdelegateClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        spinboxdelegateClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(spinboxdelegateClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        spinboxdelegateClass->setStatusBar(statusBar);

        retranslateUi(spinboxdelegateClass);

        QMetaObject::connectSlotsByName(spinboxdelegateClass);
    } // setupUi

    void retranslateUi(QMainWindow *spinboxdelegateClass)
    {
        spinboxdelegateClass->setWindowTitle(QApplication::translate("spinboxdelegateClass", "spinboxdelegate", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class spinboxdelegateClass: public Ui_spinboxdelegateClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPINBOXDELEGATE_H
