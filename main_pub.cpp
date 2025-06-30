#include <QCoreApplication>
#include "publisher.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    
    Publisher publisher;
    publisher.connectToBroker();
    
    return app.exec();
}