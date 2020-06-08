#include <QByteArray>
#include <QProcess>
#include <QMessageBox>
#include "assistant.h"

Assistant::Assistant()
    : proc(0)
{
}

Assistant::~Assistant()
{
    if (proc && proc->state() == QProcess::Running) {
        // 试图终止进程
        proc->terminate();
        proc->waitForFinished(3000);
    }
    // 销毁proc
    delete proc;
}

// 显示文档
void Assistant::showDocumentation(const QString &page)
{
    if (!startAssistant())
        return;
    QByteArray ba("SetSource ");
    ba.append("qthelp://yafeilinux.myHelp/doc/");
    proc->write(ba + page.toLocal8Bit() + '\n');
}

// 启动Qt Assistant
bool Assistant::startAssistant()
{
    // 如果没有创建进程，则新创建一个
    if (!proc)
        proc = new QProcess();

    // 如果进程没有运行，则运行assistant，并添加参数
    if (proc->state() != QProcess::Running) {
        QString app = QLatin1String("../myWhatsThis/documentation/assistant.exe");
        QStringList args;
        args << QLatin1String("-collectionFile")
             << QLatin1String("../myWhatsThis/documentation/myHelp.qhc");
        proc->start(app, args);
        if (!proc->waitForStarted()) {
            QMessageBox::critical(0, QObject::tr("my help"),
                                  QObject::tr("Unable to launch Qt Assistant (%1)").arg(app));
            return false;
        }
    }
    return true;
}

