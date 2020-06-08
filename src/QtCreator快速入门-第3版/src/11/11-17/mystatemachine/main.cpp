#include <QApplication>
#include <QPushButton>
#include <QState>
#include <QStateMachine>
#include <QLabel>

int main(int argc, char* argv[ ])
{
    QApplication app(argc, argv);

    QPushButton button1("clean or not");
    QPushButton button2("moving or not");
    QLabel label;
    QLabel label1(&label);
    QLabel label2(&label);

    QStateMachine machine;
    QState *s1 = new QState(QState::ParallelStates);
    QState *s11 = new QState(s1);
    QState *clean = new QState(s11);
    QState *dirty = new QState(s11);
    s11->setInitialState(clean);
    clean->assignProperty(&label1, "text", "clean");
    dirty->assignProperty(&label1, "text", "dirty");
    clean->addTransition(&button1, &QPushButton::clicked, dirty);
    dirty->addTransition(&button1, &QPushButton::clicked, clean);
    QState *s12 = new QState(s1);
    QState *moving = new QState(s12);
    QState *notMoving = new QState(s12);
    s12->setInitialState(notMoving);
    moving->assignProperty(&label2, "text", "moving");
    notMoving->assignProperty(&label2, "text", "not moving");
    moving->addTransition(&button2, &QPushButton::clicked, notMoving);
    notMoving->addTransition(&button2, &QPushButton::clicked, moving);

    machine.addState(s1);
    machine.setInitialState(s1);
    machine.start();
    button1.move(100, 300);
    button1.show();
    button2.move(300, 300);
    button2.show();
    label1.resize(100, 20);
    label2.resize(100, 20);
    label2.move(0, 20);
    label.move(180, 120);
    label.resize(100, 50);
    label.show();

    return app.exec();
}


