import QtQuick 2.10

import "../Tools"
import "../ViewMenu"

SectionGridView {
	id: view
	sectionTextIndex: 0

	cellHeight: 124
	cellWidth: width / 2

	model: ArtistViewModel {
		onMenuRequested: {
			menu.x = x-view.contentX
			menu.y = y-view.contentY
			menu.currentInd = index
			menu.open()
		}
	}

	ViewMenu {
		id: menu
		type: consts.artistLoader
	}
}
