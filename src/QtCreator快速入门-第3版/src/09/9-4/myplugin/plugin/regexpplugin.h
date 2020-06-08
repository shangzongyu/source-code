#ifndef REGEXPPLUGIN_H
#define REGEXPPLUGIN_H

#include <QObject>
#include "regexpinterface.h"

class RegExpPlugin : public QObject, RegExpInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qter.Examples.myplugin.RegExpInterface"
                      FILE "myplugin.json")
    Q_INTERFACES(RegExpInterface)

public:
    QString regexp(const QString &message);
};

#endif
