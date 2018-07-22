import QtQuick 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3
import STools.Extras 1.0

import "../ViewMenu"

Page {
	id: page
	Layout.fillWidth: true
	Layout.fillHeight: true

	title: "Recently Played"

	background: Item { }

	header: Label {
		padding: 10
		text: title
		elide: Text.ElideRight
		horizontalAlignment: Text.AlignHCenter
		font.pointSize: Extras.mediumFont

		background: Rectangle {
			color: Material.primary
		}
	}

	ListView {
		id: view
		anchors.fill: parent
		emptyText: "Nothing Played Recently!"

		model: RecentModel {
			modelType: false

			onMenuRequested: {
				menu.x = x-view.contentX
				menu.y = y-view.contentY
				menu.currentInd = index
				menu.open()
			}
		}
	}

	ViewMenu {
		id: menu
		type: consts.recentlyPlayedLoader
	}
}
