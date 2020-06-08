#include <QMouseEvent>
#include <QPainter>

#include "brushinterface.h"
#include "paintwidget.h"

PaintWidget::PaintWidget(QWidget *parent) :
    QWidget(parent),
    theImage(500, 400, QImage::Format_RGB32),
    color(Qt::blue),
    thickness(3),
    brushInterface(0),
    lastPos(-1, -1)
{
    setAttribute(Qt::WA_StaticContents);
    setAttribute(Qt::WA_NoBackground);

    theImage.fill(qRgb(255, 255, 255));
}

void PaintWidget::setBrush(BrushInterface *brushInterface, const QString &brush)
{
    this->brushInterface = brushInterface;
    this->brush = brush;
}

void PaintWidget::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    painter.drawImage(QPoint(0, 0), theImage);
}

void PaintWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if (brushInterface) {
            QPainter painter(&theImage);
            setupPainter(painter);
            const QRect rect = brushInterface->mousePress(brush, painter,
                                                          event->pos());
            update(rect);
        }
        lastPos = event->pos();
    }
}

void PaintWidget::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && lastPos != QPoint(-1, -1)) {
        if (brushInterface) {
            QPainter painter(&theImage);
            setupPainter(painter);
            const QRect rect = brushInterface->mouseMove(brush, painter, lastPos,
                                                         event->pos());
            update(rect);
        }

        lastPos = event->pos();
    }
}

void PaintWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && lastPos != QPoint(-1, -1)) {
        if (brushInterface) {
            QPainter painter(&theImage);
            setupPainter(painter);
            QRect rect = brushInterface->mouseRelease(brush, painter,
                                                      event->pos());
            update(rect);
        }

        lastPos = QPoint(-1, -1);
    }
}

void PaintWidget::setupPainter(QPainter &painter)
{
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(color, thickness, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
}
