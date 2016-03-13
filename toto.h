#ifndef TOTO_H
#define TOTO_H

#include <QObject>
#include <iostream>

class Toto : public QObject
{
    Q_OBJECT

public:
    Toto(QObject* parent = 0);
    ~Toto();

public slots:
    void received(int a, int b, int c, int d);
};

#endif // TOTO_H
