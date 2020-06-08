#include <QDir>
#include <QPluginLoader>

#include "brushinterface.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    brushActionGroup(new QActionGroup(this))
{
    ui->setupUi(this);

    loadPlugins();

    if (!brushActionGroup->actions().isEmpty()) {
        brushActionGroup->actions().first()->trigger();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

void MainWindow::changeBrush()
{
    QAction *action = qobject_cast<QAction *>(sender());
    BrushInterface *iBrush = qobject_cast<BrushInterface *>(action->parent());
    const QString brush = action->text();

    ui->paintWidget->setBrush(iBrush, brush);
}

void MainWindow::loadPlugins()
{
    QDir pluginsDir = QDir(QApplication::applicationDirPath());
#if defined(Q_OS_WIN)
    if (pluginsDir.dirName().toLower() == "debug"
            || pluginsDir.dirName().toLower() == "release")
        pluginsDir.cdUp();
#elif defined(Q_OS_MAC)
    if (pluginsDir.dirName() == "MacOS") {
        pluginsDir.cdUp();
        pluginsDir.cdUp();
        pluginsDir.cdUp();
    }
#endif
    pluginsDir.cd("plugins");

    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = loader.instance();
        if (plugin) {
            BrushInterface *iBrush = qobject_cast<BrushInterface *>(plugin);
            if (iBrush) {
                foreach (QString text, iBrush->brushes()) {
                        QAction *action = new QAction(text, plugin);
                        connect(action, &QAction::triggered,
                                this, &MainWindow::changeBrush);
                        ui->menuBrushes->addAction(action);
                        action->setCheckable(true);
                        brushActionGroup->addAction(action);
                    }
            }
        }
    }

    ui->menuBrushes->setEnabled(!brushActionGroup->actions().isEmpty());
}
