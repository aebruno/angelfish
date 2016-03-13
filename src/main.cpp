#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <sailfishapp.h>
#include <QQuickView>
#include <QGuiApplication>
#include <QQmlContext>
#include <QtQml>
#include <QSettings>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "angel.h"
#include "devicemodel.h"
#include "settings.h"

int main(int argc, char *argv[])
{

    QGuiApplication *app = SailfishApp::application(argc, argv);
    app->setApplicationVersion("0.0.1");
    app->setOrganizationName("");
    app->setApplicationName("harbour-angelfish");

    qmlRegisterType<DeviceModel>();

    qDebug() << "Data location path: " << QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    qDebug() << "Config location path: " << QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);
    
    Settings settings;
    Angel angel;
    QQuickView *view = SailfishApp::createView();
    view->setSource(SailfishApp::pathTo("qml/harbour-angelfish.qml"));
    view->rootContext()->setContextProperty("angel", &angel);
    view->rootContext()->setContextProperty("settings", &settings);

    view->showFullScreen();

    return app->exec();
}
