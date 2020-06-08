#ifndef BRUSHINTERFACE_H
#define BRUSHINTERFACE_H

#include <QtPlugin>

QT_BEGIN_NAMESPACE
class QPainter;
class QPoint;
class QRect;
QT_END_NAMESPACE

class BrushInterface
{
public:
    virtual ~BrushInterface() {}

    virtual QStringList brushes() const = 0;
    virtual QRect mousePress(const QString &brush,
                             QPainter &painter,
                             const QPoint &pos) = 0;
    virtual QRect mouseMove(const QString &brush,
                            QPainter &painter,
                            const QPoint &oldPos,
                            const QPoint &newPos) = 0;
    virtual QRect mouseRelease(const QString &brush,
                               QPainter &painter,
                               const QPoint &pos) = 0;
};

#define BrushInterface_iid "org.qter.ShapePainter.BrushInterface/1.0"

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(BrushInterface, BrushInterface_iid)
QT_END_NAMESPACE

#endif // BRUSHINTERFACE_H
