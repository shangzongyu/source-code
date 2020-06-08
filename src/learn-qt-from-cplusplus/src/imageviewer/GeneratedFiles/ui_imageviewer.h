/********************************************************************************
** Form generated from reading UI file 'imageviewer.ui'
**
** Created: Tue Apr 24 20:10:01 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEVIEWER_H
#define UI_IMAGEVIEWER_H

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

class Ui_imageviewerClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *imageviewerClass)
    {
        if (imageviewerClass->objectName().isEmpty())
            imageviewerClass->setObjectName(QString::fromUtf8("imageviewerClass"));
        imageviewerClass->resize(600, 400);
        menuBar = new QMenuBar(imageviewerClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        imageviewerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(imageviewerClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        imageviewerClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(imageviewerClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        imageviewerClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(imageviewerClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        imageviewerClass->setStatusBar(statusBar);

        retranslateUi(imageviewerClass);

        QMetaObject::connectSlotsByName(imageviewerClass);
    } // setupUi

    void retranslateUi(QMainWindow *imageviewerClass)
    {
        imageviewerClass->setWindowTitle(QApplication::translate("imageviewerClass", "imageviewer", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class imageviewerClass: public Ui_imageviewerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEVIEWER_H
