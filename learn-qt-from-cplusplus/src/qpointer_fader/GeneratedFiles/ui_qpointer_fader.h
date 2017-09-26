/********************************************************************************
** Form generated from reading UI file 'qpointer_fader.ui'
**
** Created: Wed Apr 25 08:48:25 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QPOINTER_FADER_H
#define UI_QPOINTER_FADER_H

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

class Ui_qpointer_faderClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *qpointer_faderClass)
    {
        if (qpointer_faderClass->objectName().isEmpty())
            qpointer_faderClass->setObjectName(QString::fromUtf8("qpointer_faderClass"));
        qpointer_faderClass->resize(600, 400);
        menuBar = new QMenuBar(qpointer_faderClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        qpointer_faderClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(qpointer_faderClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        qpointer_faderClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(qpointer_faderClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        qpointer_faderClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(qpointer_faderClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        qpointer_faderClass->setStatusBar(statusBar);

        retranslateUi(qpointer_faderClass);

        QMetaObject::connectSlotsByName(qpointer_faderClass);
    } // setupUi

    void retranslateUi(QMainWindow *qpointer_faderClass)
    {
        qpointer_faderClass->setWindowTitle(QApplication::translate("qpointer_faderClass", "qpointer_fader", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class qpointer_faderClass: public Ui_qpointer_faderClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QPOINTER_FADER_H
