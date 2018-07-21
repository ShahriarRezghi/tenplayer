import QtQuick 2.10

import "../Tools"

SectionGridView {
	id: view
	sectionTextIndex: 0

	cellHeight: 64
	cellWidth: width / 3

	model: ArtistViewModel {
		onMenuRequested: {
			menu.x = x-view.contentX
			menu.y = y-view.contentY
			menu.currentInd = index
			menu.open()
		}
	}
}
