#include <QStringList>
#include <QRect>
#include <QPainter>

#include "brushplugin.h"

QStringList BrushPlugin::brushes() const
{
    return QStringList() << tr("Pencil") << tr("Air Brush")
                         << tr("Random Letters");
}

QRect BrushPlugin::mousePress(const QString &brush, QPainter &painter,
                              const QPoint &pos)
{
    return mouseMove(brush, painter, pos, pos);
}

QRect BrushPlugin::mouseMove(const QString &brush, QPainter &painter,
                             const QPoint &oldPos, const QPoint &newPos)
{
    painter.save();

    int rad = painter.pen().width() / 2;
    QRect boundingRect = QRect(oldPos, newPos).normalized()
                                              .adjusted(-rad, -rad, +rad, +rad);
    QColor color = painter.pen().color();
    int thickness = painter.pen().width();

    if (brush == tr("Pencil")) {
        painter.drawLine(oldPos, newPos);
    } else if (brush == tr("Air Brush")) {
        int numSteps = 2 + (newPos - oldPos).manhattanLength() / 2;

        painter.setBrush(QBrush(color, Qt::Dense6Pattern));
        painter.setPen(Qt::NoPen);

        for (int i = 0; i < numSteps; ++i) {
            int x = oldPos.x() + i * (newPos.x() - oldPos.x()) / (numSteps - 1);
            int y = oldPos.y() + i * (newPos.y() - oldPos.y()) / (numSteps - 1);

            painter.drawEllipse(x - (thickness / 2), y - (thickness / 2),
                                thickness, thickness);
        }
    } else if (brush == tr("Random Letters")) {
        QChar ch('A' + (qrand() % 26));

        QFont biggerFont = painter.font();
        biggerFont.setBold(true);
        biggerFont.setPointSize(biggerFont.pointSize() + thickness);
        painter.setFont(biggerFont);

        painter.drawText(newPos, QString(ch));

        QFontMetrics metrics(painter.font());
        boundingRect = metrics.boundingRect(ch);
        boundingRect.translate(newPos);
        boundingRect.adjust(-10, -10, +10, +10);
    }
    painter.restore();
    return boundingRect;
}

QRect BrushPlugin::mouseRelease(const QString & /* brush */,
                                QPainter & /* painter */,
                                const QPoint & /* pos */)
{
    return QRect(0, 0, 0, 0);
}
