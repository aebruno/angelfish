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
                value: settings.setting("device/name")
            }
            DetailItem {
                label: "Address"
                value: settings.setting("device/address")
            }
            DetailItem {
                label: "Manufacturer"
                value: settings.setting("device/manufacturer")
            }
            DetailItem {
                label: "Model Number"
                value: settings.setting("device/model")
            }
            DetailItem {
                label: "Serial Number"
                value: settings.setting("device/serial")
            }
            DetailItem {
                label: "Firmware Revision"
                value: settings.setting("device/firmrev")
            }
        }
    }
}
