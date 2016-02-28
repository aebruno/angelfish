#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <sailfishapp.h>
#include <QQuickView>
#include <QGuiApplication>
#include <QQmlContext>
#include <QtQml>
#include "angel.h"
#include "devicemodel.h"
#include "deviceinfo.h"

int main(int argc, char *argv[])
{
    QGuiApplication *app = SailfishApp::application(argc, argv);

    qmlRegisterType<DeviceModel>();
    qmlRegisterType<DeviceInfo>();
    
    Angel angel;
    QQuickView *view = SailfishApp::createView();
    view->setSource(SailfishApp::pathTo("qml/harbour-angelfish.qml"));
    view->rootContext()->setContextProperty("angel", &angel);

    view->showFullScreen();

    return app->exec();
}
