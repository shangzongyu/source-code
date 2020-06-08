#include "mydesignerplugin.h"
#include "mydesignerpluginplugin.h"

#include <QtPlugin>

MyDesignerPluginPlugin::MyDesignerPluginPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void MyDesignerPluginPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool MyDesignerPluginPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *MyDesignerPluginPlugin::createWidget(QWidget *parent)
{
    return new MyDesignerPlugin(parent);
}

QString MyDesignerPluginPlugin::name() const
{
    return QLatin1String("MyDesignerPlugin");
}

QString MyDesignerPluginPlugin::group() const
{
    return QLatin1String("");
}

QIcon MyDesignerPluginPlugin::icon() const
{
    return QIcon(QLatin1String(":/yafeilinux.png"));
}

QString MyDesignerPluginPlugin::toolTip() const
{
    return QLatin1String("");
}

QString MyDesignerPluginPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool MyDesignerPluginPlugin::isContainer() const
{
    return false;
}

QString MyDesignerPluginPlugin::domXml() const
{
    return QLatin1String("<widget class=\"MyDesignerPlugin\" name=\"myDesignerPlugin\">\n</widget>\n");
}

QString MyDesignerPluginPlugin::includeFile() const
{
    return QLatin1String("mydesignerplugin.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(mydesignerpluginplugin, MyDesignerPluginPlugin)
#endif // QT_VERSION < 0x050000
