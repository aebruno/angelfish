import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: root

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height + Theme.paddingLarge
        contentWidth: parent.width

        PullDownMenu {
            MenuItem {
                text: qsTr("About AngelFish")
                onClicked: pageStack.push(Qt.resolvedUrl("About.qml"))
            }
            MenuItem {
                text: qsTr("Scan for devices")
                onClicked: {
                    pageStack.push(Qt.resolvedUrl("Scan.qml"))
                }
            }
            MenuItem {
                enabled: angel.hasSensor
                text: qsTr("Device Info")
                onClicked: {
                    pageStack.push(Qt.resolvedUrl("SensorInfo.qml"))
                }
            }
        }

        VerticalScrollDecorator {}

        ViewPlaceholder {
            enabled: !angel.hasSensor
            text: "No sensor configured"
            hintText: "Setup new sensor by scanning for device"
        }

        Column {
            visible: angel.hasSensor
            id: column
            spacing: Theme.paddingLarge
            width: root.width
            PageHeader {
                title: qsTr("AngelFish")
            }

            IconTextSwitch {
                text: angel.name
                description: checked ? "Connected" : "Disconnected"
                icon.source: "image://theme/icon-m-bluetooth"
                onCheckedChanged: {
                    checked ? angel.connectSensor() : angel.disconnectSensor()
                }
            }

            DetailItem {
                label: "Battery"
                value: angel.battery
            }
            DetailItem {
                label: "Heart Rate"
                value: "67"
            }
            DetailItem {
                label: "Step Count"
                value: "132"
            }


        }
    }
}
