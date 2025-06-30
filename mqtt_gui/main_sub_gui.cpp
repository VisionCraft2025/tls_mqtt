#include <QApplication>
#include "subscriber_gui.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    SubscriberGui subscriber;
    subscriber.show();
    
    return app.exec();
}