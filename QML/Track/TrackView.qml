import QtQuick 2.10
import QtQuick.Controls 2.3

import "../ViewMenu"

GridView {
	id: view

	property int type

	ScrollBar.vertical: ScrollBar { }

	cellWidth: width/2
	cellHeight: 16 + Math.max(consts.textSize*2, 48)

	model: TrackViewModel {
		onMenuRequested: {
			menu.x = x-view.contentX
			menu.y = y-view.contentY
			menu.currentInd = index
			menu.open()
		}
	}

	property var menu: TrackMenu {
		id: menu
		type: view.type
	}
}
