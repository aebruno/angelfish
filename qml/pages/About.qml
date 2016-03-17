import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
	id: aboutpage
	SilicaFlickable {
		anchors.fill: parent
		contentWidth: parent.width
		contentHeight: col.height + Theme.paddingLarge

		VerticalScrollDecorator {}

		Column {
			id: col
			spacing: Theme.paddingLarge
			width: parent.width
			PageHeader {
				title: qsTr("About AngelFish")
			}

			Image {
				anchors.horizontalCenter: parent.horizontalCenter
				source: "/usr/share/icons/hicolor/86x86/apps/harbour-angelfish.png"
			}

            Label {
                anchors.horizontalCenter: parent.horizontalCenter
                font.bold: true
                text: "AngelFish v" + Qt.application.version
            }

            TextArea {
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width
                horizontalAlignment: TextEdit.Center
                readOnly: true
                text: qsTr("Sailfish app for the Angel Sensor")
            }

            TextArea {
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width
                horizontalAlignment: TextEdit.Center
                readOnly: true
                text: qsTr("Copyright: Andrew E. Bruno\nLicense: GPLv3")
            }

            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "<a href=\"https://github.com/aebruno/angelfish\">Source Code</a>"
                onClicked: {
                    Qt.openUrlExternally("https://github.com/aebruno/angelfish")
                }
            }

            SectionHeader {
                text: qsTr("Additional Copyright")
            }

            Label {
                text: qsTr("AngelFish uses <a href=\"https://git.javispedro.com/cgit/libgato.git/tree/\">libgato</a>, a GATT/ATT library (C) Javier S. Pedro.")
                anchors.horizontalCenter: parent.horizontalCenter
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                width: (parent ? parent.width : Screen.width) - Theme.paddingLarge * 2
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                x: Theme.paddingLarge
            }
		}
	}
}
