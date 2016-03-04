import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: root

    SilicaFlickable {
        anchors.fill: parent
        contentWidth: parent.width

        ViewPlaceholder {
            enabled: !angel.hasSensor
            text: "No sensor configured"
            hintText: "Setup new sensor by scanning for device"
        }

        VerticalScrollDecorator {}

        Column {
            visible: angel.hasSensor
            id: content
            spacing: Theme.paddingMedium
            width: root.width

            PageHeader {
                title: "Sensor Information"
            }

            DetailItem {
                label: "Name"
                value: angel.name
            }
            DetailItem {
                label: "Address"
                value: angel.address
            }
            DetailItem {
                label: "Battery"
                value: angel.battery
            }
            DetailItem {
                label: "Manufacturer"
                value: angel.manufacturer
            }
            DetailItem {
                label: "Model Number"
                value: angel.modelNumber
            }
            DetailItem {
                label: "Serial Number"
                value: angel.serialNumber
            }
        }
    }
}
