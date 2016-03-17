/*
 * Copyright (C) 2016 Andrew E. Bruno <aeb@qnot.org>
 *
 * This file is part of AngelFish.
 * 
 * AngelFish is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * AngelFish is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with AngelFish.  If not, see <http://www.gnu.org/licenses/>. 
 */

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
#include "version.h"
#include "angel.h"
#include "devicemodel.h"
#include "settings.h"
#include "batteryservice.h"
#include "infoservice.h"
#include "heartservice.h"
#include "activityservice.h"

int main(int argc, char *argv[])
{

    QGuiApplication *app = SailfishApp::application(argc, argv);
    app->setApplicationVersion(ANGELFISH_VERSION);
    app->setOrganizationName("");
    app->setApplicationName("harbour-angelfish");

    qmlRegisterType<DeviceModel>();

    qDebug() << "Data location path: " << QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    qDebug() << "Config location path: " << QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);
    
    Settings settings;
    BatteryService batteryService;
    InfoService infoService;
    HeartService heartService;
    ActivityService activityService;

    Angel angel;
    angel.registerService(&batteryService);
    angel.registerService(&infoService);
    angel.registerService(&heartService);
    angel.registerService(&activityService);

    QQuickView *view = SailfishApp::createView();
    view->setSource(SailfishApp::pathTo("qml/harbour-angelfish.qml"));
    view->rootContext()->setContextProperty("angel", &angel);
    view->rootContext()->setContextProperty("settings", &settings);
    view->rootContext()->setContextProperty("battery", &batteryService);
    view->rootContext()->setContextProperty("heart", &heartService);
    view->rootContext()->setContextProperty("activity", &activityService);

    view->showFullScreen();

    return app->exec();
}
