#include <QtCore/QCoreApplication>
#include <QtDBus/QtDBus>
#include "ProcexpHelperInterface.h"
#include "toto.h"

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    Toto t(&app);

    com::procexp::helper helper("com.procexp.helper", "/", QDBusConnection::sessionBus(), &app);
    QObject::connect(&helper, SIGNAL(fork(int,int,int,int)), &t, SLOT(received(int,int,int,int)));

    app.exec();

    return 0;
}
