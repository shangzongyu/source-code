#ifndef BRUSHPLUGIN_H
#define BRUSHPLUGIN_H

#include <QObject>
#include <QtPlugin>

#include <brushinterface.h>

class BrushPlugin : public QObject, public BrushInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID BrushInterface_iid FILE "brushplugin.json")
    Q_INTERFACES(BrushInterface)
public:
    QStringList brushes() const;
    QRect mousePress(const QString &brush, QPainter &painter,
                     const QPoint &pos);
    QRect mouseMove(const QString &brush, QPainter &painter,
                    const QPoint &oldPos, const QPoint &newPos);
    QRect mouseRelease(const QString &brush, QPainter &painter,
                       const QPoint &pos);
};

#endif // BRUSHPLUGIN_H
