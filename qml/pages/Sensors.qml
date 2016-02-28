import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: page
    property string message: angel.message
    SilicaListView {
        id: listView
        model: angel.name
        anchors.fill: parent
        header: PageHeader {
            title: angel.message
        }
        delegate: Item {
            id: delegate

            Label {
                x: Theme.paddingLarge
                text: modelData.deviceName
                anchors.verticalCenter: parent.verticalCenter
                color: delegate.highlighted ? Theme.highlightColor : Theme.primaryColor
            }
            Label {
                x: Theme.paddingSmall
                text: modelData.deviceAddress
                anchors.verticalCenter: parent.verticalCenter
                color: delegate.highlighted ? Theme.highlightColor : Theme.primaryColor
            }
            onClicked: {
                angel.stopSearch()
                progressPanel.open = !progressPanel.open
                console.log("Clicked " + index)
            }
        }
        VerticalScrollDecorator {}
    }

    DockedPanel {
        id: progressPanel
        open: true
        width: page.isPortrait ? parent.width : Theme.itemSizeExtraLarge + Theme.paddingLarge
        height: page.isPortrait ? Theme.itemSizeExtraLarge + Theme.paddingLarge : parent.height

        dock: page.isPortrait ? Dock.Bottom : Dock.Right

        ProgressCircle {
            id: progressCircle

            anchors.centerIn: parent

            NumberAnimation on value {
                from: 0
                to: 1
                duration: 1000
                running: progressPanel.expanded
                loops: Animation.Infinite
            }
        }
    }
}
