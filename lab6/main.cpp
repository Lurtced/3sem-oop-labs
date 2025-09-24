#include <QApplication>
#include "dynamicwidgetcollection.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    DynamicWidgetCollection collection;
    collection.show();

    return app.exec();
}
