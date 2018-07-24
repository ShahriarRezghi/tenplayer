import QtQuick 2.10
import QtQuick.Window 2.2
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3

import "../Tools"
import "../ViewMenu"

SectionGridView {
	id: view
	emptyText: "Nothing Here"
	sectionTextIndex: 1
	cellHeight: cellWidth+6+consts.textSize

	cellWidth: {
		var DW = Screen.width
		var W = width
		return W/Math.max(Math.floor(W*7/DW), 5)
	}

	model: PlaylistViewModel {
		onMenuRequested: {
			menu.x = x-view.contentX
			menu.y = y-view.contentY
			menu.currentInd = index
			menu.open()
		}
	}

	ViewMenu {
		id: menu
		type: consts.playlistLoader
	}

	RoundButton {
		id: addButton
		icon.source: "qrc:/Images/Plus.png"
		Material.background: theme.primary

		implicitWidth: 80
		implicitHeight: 80

		anchors.rightMargin: 50
		anchors.bottomMargin: 50
		anchors.right: parent.right
		anchors.bottom: parent.bottom

		onClicked: addPlaylistDialog.open()
	}
}
