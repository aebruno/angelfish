import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: page

    SilicaFlickable {
        anchors.fill: parent

        PullDownMenu {
            MenuItem {
                text: qsTr("About AngelFish")
                onClicked: pageStack.push(Qt.resolvedUrl("About.qml"))
            }
            MenuItem {
                text: qsTr("Scan for Devices")
                onClicked: {
                    angel.deviceSearch()
                    pageStack.push(Qt.resolvedUrl("Scan.qml"))
                }
            }
        }

    contentHeight: column.height + Theme.paddingLarge
    contentWidth: parent.width

    VerticalScrollDecorator {}

        Column {
            id: column
            spacing: Theme.paddingLarge
            width: page.width
            PageHeader {
                title: qsTr("Welcome to AngelFish")
            }

        }
    }
}
