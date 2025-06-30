#include <QCoreApplication>
#include "subscriber.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    
    Subscriber subscriber;
    subscriber.connectToBroker();
    
    return app.exec();
}