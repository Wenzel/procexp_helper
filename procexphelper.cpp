#include "procexphelper.h"

ProcexpHelper::ProcexpHelper(QObject *parent)
    : QObject(parent)
{

}

ProcexpHelper::~ProcexpHelper()
{

}

QString ProcexpHelper::ping()
{
    return "pong";
}
