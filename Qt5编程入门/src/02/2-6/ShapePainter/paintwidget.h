#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>

class BrushInterface;

class PaintWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PaintWidget(QWidget *parent = 0);

    void setBrush(BrushInterface *brushInterface, const QString &brush);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    void setupPainter(QPainter &painter);

    QImage theImage;
    QColor color;
    int thickness;

    BrushInterface *brushInterface;
    QString brush;
    QPoint lastPos;
};

#endif // PAINTWIDGET_H
