#include <QApplication>
#include "publisher_gui.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    PublisherGui publisher;
    publisher.show();
    
    return app.exec();
}