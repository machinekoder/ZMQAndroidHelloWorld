#include "qtquick2controlsapplicationviewer.h"
#include "subscribertest.h"
#include <QtQml>

int main(int argc, char *argv[])
{
    Application app(argc, argv);

    qmlRegisterType<SubscriberTest>("nzmqt",1,0,"SubscriberTest");

    QtQuick2ControlsApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/ZMQAndroidHelloWorld/main.qml"));
    viewer.show();

    return app.exec();
}
