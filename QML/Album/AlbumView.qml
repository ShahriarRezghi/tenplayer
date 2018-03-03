import QtQuick 2.10
import QtQuick.Window 2.2

import "../Tools"

SectionGridView {
	id: view
	sectionTextIndex: 1

	cellWidth: {
		var DW = Screen.width
		var W = width
		return W/Math.max(Math.floor(W*7/DW), 5)
	}

	cellHeight: cellWidth+6+consts.textSize*2

	model: AlbumViewModel {
		onMenuRequested: {
			menu.x = x-view.contentX
			menu.y = y-view.contentY
			menu.currentInd = index
			menu.open()
		}
	}
}
