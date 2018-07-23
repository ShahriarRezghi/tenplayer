import QtQuick 2.10

import "../Tools"
import "../ViewMenu"

SectionGridView {
	id: view
	sectionTextIndex: 0

	cellWidth: width/2
	cellHeight: 100

	model: SongViewModel {
		onMenuRequested: {
			menu.x = x-view.contentX
			menu.y = y-view.contentY
			menu.currentInd = index
			menu.open()
		}
	}

	ViewMenu {
		id: menu
		type: consts.songLoader
	}
}
