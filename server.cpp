#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusConnectionInterface>
#include <QCoreApplication>
#include <thread>

#include <iostream>
#include <unistd.h>

#include "procexphelper.h"
#include "ProcexpHelperAdaptor.h"
#include "ProcexpHelperInterface.h"
#include "toto.h"

#define CONNECTOR_SERVICE "com.procexp.helper"
#define CONNECTOR_PATH "/"

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    QDBusConnection connection = QDBusConnection::sessionBus();

    ProcexpHelper* conn = new ProcexpHelper(&app);
    ProcexpHelperAdaptor* adaptor = new ProcexpHelperAdaptor(conn);

    if (!connection.registerService(CONNECTOR_SERVICE))
        qFatal("Could not register the service");

    if (!connection.registerObject(CONNECTOR_PATH, adaptor, QDBusConnection::ExportAllContents))
        qFatal("Could not register the adapter object");

    com::procexp::helper* iface = new com::procexp::helper(CONNECTOR_SERVICE, CONNECTOR_PATH, connection);

    while (1)
    {
        emit iface->fork(1, 2 ,3 ,4);
        app.processEvents();
    }
}
