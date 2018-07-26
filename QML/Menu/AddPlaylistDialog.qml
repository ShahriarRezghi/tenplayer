import QtQuick 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3

import "../Tools"

Popup {
	id: popup
	modal: true

	topPadding: 12
	bottomPadding: 12
	leftPadding: 18
	rightPadding: 18

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
			placeholderText: "Playlist Name"
			Material.accent: theme.background == theme.accent ? theme.primary:theme.accent
		}

		Button {
			text: "Add"
			flat: true

			onClicked: {
				popup.close()
				MainManager.addPlaylist(field.text)
			}
		}
	}
}
