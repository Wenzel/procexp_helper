#include "toto.h"

Toto::Toto(QObject* parent)
    : QObject(parent)
{

}

Toto::~Toto()
{

}

void Toto::received(int a, int b, int c, int d)
{
    std::cout << "received" << std::endl;
}
