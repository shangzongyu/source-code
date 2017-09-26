/********************************************************************************
** Form generated from reading UI file 'styles.ui'
**
** Created: Wed Apr 25 09:30:03 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STYLES_H
#define UI_STYLES_H

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

class Ui_stylesClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *stylesClass)
    {
        if (stylesClass->objectName().isEmpty())
            stylesClass->setObjectName(QString::fromUtf8("stylesClass"));
        stylesClass->resize(600, 400);
        menuBar = new QMenuBar(stylesClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        stylesClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(stylesClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        stylesClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(stylesClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        stylesClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(stylesClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        stylesClass->setStatusBar(statusBar);

        retranslateUi(stylesClass);

        QMetaObject::connectSlotsByName(stylesClass);
    } // setupUi

    void retranslateUi(QMainWindow *stylesClass)
    {
        stylesClass->setWindowTitle(QApplication::translate("stylesClass", "styles", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class stylesClass: public Ui_stylesClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STYLES_H
