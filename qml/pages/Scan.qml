import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {
    id: root

    property int selectedDevice: -1
    property bool deviceSelected: false

    canAccept: deviceSelected

    onOpened: {
        timer.start()
        angel.deviceSearch()
    }

    onRejected: {
        console.log("Stop scan")
        timer.stop()
        angel.stopSearch()
    }

    onAccepted: {
        timer.stop()
        progressPanel.hide()
        angel.stopSearch()
        console.log("Accpeted. Connecting to device at " + root.selectedDevice)
        angel.setupNewDevice(root.selectedDevice)
    }

    SilicaListView {
        id: listView
        anchors.fill: parent
        model: angel.devices()
        header: DialogHeader { 
            acceptText: "Save"
            cancelText: "Cancel"
        }

        ViewPlaceholder {
            enabled: listView.count == 0
            text: "No devices found"
            hintText: "Press the button on your sensor" }

        delegate: BackgroundItem {
            id: listItem
            property bool isSelected: index === root.selectedDevice


            Image {
                id: deviceIcon
                x: Theme.horizontalPageMargin
                anchors.verticalCenter: parent.verticalCenter
                source: "image://theme/icon-m-bluetooth" + (listItem.isSelected ? "?" + Theme.highlightColor : "")
                opacity: listItem.matchesProfileHint || listItem.isSelected ? 1 : 0.5
            }

            Label {
                anchors {
                    left: deviceIcon.right
                    leftMargin: Theme.paddingMedium
                    right: parent.right
                    rightMargin: Theme.horizontalPageMargin
                    verticalCenter: parent.verticalCenter
                }
                text: model.name.length ? model.name : model.address
                truncationMode: TruncationMode.Fade
                color: listItem.isSelected
                       ? Theme.highlightColor
                       : Theme.rgba(Theme.primaryColor, listItem.matchesProfileHint ? 1.0 : 0.5)
            }

            onClicked: {
                root.selectedDevice = index
                root.deviceSelected = true
                console.log("Clicked " + index)
            }
        }
    }

    DockedPanel {
        id: progressPanel
        open: true
        width: root.isPortrait ? parent.width : Theme.itemSizeExtraLarge + Theme.paddingLarge
        height: root.isPortrait ? Theme.itemSizeExtraLarge + Theme.paddingLarge : parent.height

        dock: root.isPortrait ? Dock.Bottom : Dock.Right

        ProgressBar {
            id: discoveryProgressBar
            width: parent.width
            opacity: 1.0
            indeterminate: true
            label: "Searching for devices"

            Behavior on opacity { FadeAnimation {} }
        }
    }

    Timer {
        id: timer
        interval: 10000
        onTriggered: {
            progressPanel.hide()
            angel.stopSearch()
        }
    }
}
