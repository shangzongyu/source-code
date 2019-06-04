#ifndef WEBVIEW_H
#define WEBVIEW_H

#include <QWebEngineView>
class MainWindow;

class WebView : public QWebEngineView
{
    Q_OBJECT

public:
    WebView(QWidget *parent = nullptr);

protected:
    QWebEngineView *createWindow(QWebEnginePage::WebWindowType type) override;

private:
    MainWindow *mainWindow;
};

#endif // WEBVIEW_H
