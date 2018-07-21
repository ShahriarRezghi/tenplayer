import QtQuick 2.10

import "../Tools"

SectionGridView {
	id: view
	sectionTextIndex: 0

	cellWidth: width/2
	cellHeight: 13 + consts.textSize * 3

	model: SongViewModel {
		onMenuRequested: {
			menu.x = x-view.contentX
			menu.y = y-view.contentY
			menu.currentInd = index
			menu.open()
		}
	}
}
