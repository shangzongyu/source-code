#ifndef ASSISTANT_H
#define ASSISTANT_H
#include <QString>
class QProcess;

class Assistant
{
public:
    Assistant();
    ~Assistant();
    void showDocumentation(const QString &file);
private:
    bool startAssistant();
    QProcess *proc;
};

#endif // ASSISTANT_H
