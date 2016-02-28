import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {
    id: page
    canAccept: false

    onRejected: {
        console.log("Stop scan")
        angel.stopSearch()
    }


    SilicaListView {
        id: listView
        anchors.fill: parent
        model: angel.devices
        header: DialogHeader { 
            acceptText: ""
            cancelText: "Cancel"
        }

        ViewPlaceholder {
            enabled: listView.count == 0
            text: "No devices found"
            hintText: "Press the button on your sensor"
        }

        delegate: ListItem {
            id: listItem
            menu: connectMenu

            Label {
                id: label
                text: name
                color: listItem.highlighted ? Theme.highlightColor : Theme.primaryColor
                anchors {
                    left: parent.left
                    leftMargin: Theme.horizontalPageMargin
                }
            }
            Label {
                anchors.top: label.bottom
                text: address
                font.pixelSize: Theme.fontSizeSmall
                color: listItem.highlighted ? Theme.highlightColor : Theme.secondaryColor
                anchors {
                    top: label.bottom
                    left: parent.left
                    leftMargin: Theme.horizontalPageMargin
                }
            }

            function connect() {
                remorseBluez.execute(qsTr("Bluetooth Error"),
                    function() {
                        angel.stopSearch()
                        progressPanel.open = false
                    }, 5000)
            }

            onClicked: {
                console.log("Clicked " + index)
            }

            Component {
                id: connectMenu
                ContextMenu {
                    MenuItem {
                        text: "Connect"
                        onClicked: connect()
                    }
                }
            }
        }
    }

    RemorsePopup {
        id: remorseBluez
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
