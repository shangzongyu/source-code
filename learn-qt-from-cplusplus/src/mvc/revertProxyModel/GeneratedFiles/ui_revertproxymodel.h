/********************************************************************************
** Form generated from reading UI file 'revertproxymodel.ui'
**
** Created: Wed Apr 25 10:26:12 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REVERTPROXYMODEL_H
#define UI_REVERTPROXYMODEL_H

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

class Ui_revertProxyModelClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *revertProxyModelClass)
    {
        if (revertProxyModelClass->objectName().isEmpty())
            revertProxyModelClass->setObjectName(QString::fromUtf8("revertProxyModelClass"));
        revertProxyModelClass->resize(600, 400);
        menuBar = new QMenuBar(revertProxyModelClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        revertProxyModelClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(revertProxyModelClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        revertProxyModelClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(revertProxyModelClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        revertProxyModelClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(revertProxyModelClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        revertProxyModelClass->setStatusBar(statusBar);

        retranslateUi(revertProxyModelClass);

        QMetaObject::connectSlotsByName(revertProxyModelClass);
    } // setupUi

    void retranslateUi(QMainWindow *revertProxyModelClass)
    {
        revertProxyModelClass->setWindowTitle(QApplication::translate("revertProxyModelClass", "revertProxyModel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class revertProxyModelClass: public Ui_revertProxyModelClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REVERTPROXYMODEL_H
