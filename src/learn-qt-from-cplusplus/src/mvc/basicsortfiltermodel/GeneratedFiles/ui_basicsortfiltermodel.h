/********************************************************************************
** Form generated from reading UI file 'basicsortfiltermodel.ui'
**
** Created: Wed Apr 25 10:48:46 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BASICSORTFILTERMODEL_H
#define UI_BASICSORTFILTERMODEL_H

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

class Ui_basicsortfiltermodelClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *basicsortfiltermodelClass)
    {
        if (basicsortfiltermodelClass->objectName().isEmpty())
            basicsortfiltermodelClass->setObjectName(QString::fromUtf8("basicsortfiltermodelClass"));
        basicsortfiltermodelClass->resize(600, 400);
        menuBar = new QMenuBar(basicsortfiltermodelClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        basicsortfiltermodelClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(basicsortfiltermodelClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        basicsortfiltermodelClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(basicsortfiltermodelClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        basicsortfiltermodelClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(basicsortfiltermodelClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        basicsortfiltermodelClass->setStatusBar(statusBar);

        retranslateUi(basicsortfiltermodelClass);

        QMetaObject::connectSlotsByName(basicsortfiltermodelClass);
    } // setupUi

    void retranslateUi(QMainWindow *basicsortfiltermodelClass)
    {
        basicsortfiltermodelClass->setWindowTitle(QApplication::translate("basicsortfiltermodelClass", "basicsortfiltermodel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class basicsortfiltermodelClass: public Ui_basicsortfiltermodelClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BASICSORTFILTERMODEL_H
