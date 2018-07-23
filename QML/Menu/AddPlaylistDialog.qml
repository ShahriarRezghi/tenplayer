import QtQuick 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3

import "../Tools"

Popup {
	id: popup
	modal: true

	x: (parent.width-width)/2
	y: (parent.height-height)/2

	contentItem: RowLayout {
		Layout.fillHeight: false
		Layout.topMargin: 6
		Layout.bottomMargin: 6
		Layout.leftMargin: 10
		Layout.rightMargin: 10

		TextField {
			id: field
			implicitWidth: 250
			Layout.fillWidth: true
			placeholderText: "Add Playlist"
		}

		ImageButton {
			source: "qrc:/Images/Plus.png"
			onClicked: MainManager.addPlaylist(field.text)
		}
	}
}
