/* This file is part of the examples of the Qt Toolkit.*/

#include <QApplication>

#include "widgetgallery.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(styles);

    QApplication app(argc, argv);
    WidgetGallery gallery;
    gallery.show();
    return app.exec();
}
