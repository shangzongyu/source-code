/********************************************************************************
** Form generated from reading UI file 'introspect_qobject.ui'
**
** Created: Tue Apr 24 20:26:12 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTROSPECT_QOBJECT_H
#define UI_INTROSPECT_QOBJECT_H

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

class Ui_introspect_qobjectClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *introspect_qobjectClass)
    {
        if (introspect_qobjectClass->objectName().isEmpty())
            introspect_qobjectClass->setObjectName(QString::fromUtf8("introspect_qobjectClass"));
        introspect_qobjectClass->resize(600, 400);
        menuBar = new QMenuBar(introspect_qobjectClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        introspect_qobjectClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(introspect_qobjectClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        introspect_qobjectClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(introspect_qobjectClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        introspect_qobjectClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(introspect_qobjectClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        introspect_qobjectClass->setStatusBar(statusBar);

        retranslateUi(introspect_qobjectClass);

        QMetaObject::connectSlotsByName(introspect_qobjectClass);
    } // setupUi

    void retranslateUi(QMainWindow *introspect_qobjectClass)
    {
        introspect_qobjectClass->setWindowTitle(QApplication::translate("introspect_qobjectClass", "introspect_qobject", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class introspect_qobjectClass: public Ui_introspect_qobjectClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTROSPECT_QOBJECT_H
