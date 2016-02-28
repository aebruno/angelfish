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

			SectionHeader {
				text: qsTr("Information")
			}
			Label {
				text: qsTr("AngelFish Health Monitor")
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

