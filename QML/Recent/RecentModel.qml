import QtQuick 2.10
import "../Tools"

VisualDataModel {
	id: vdmodel
	property bool modelType // true: added, false: played
	model: modelType ? RecentlyAddedModel:RecentlyPlayedModel

	signal menuRequested(real x, real y, int index)

	delegate: ListDelegate {
		width: parent.width
		model: [titleRole, artistRole, albumRole]
		image: artworkRole ? "file://" + artworkRole:"qrc:/Images/Note.png"

		onMenuRequested: vdmodel.menuRequested(xx+x, yy+y, index)
		onClicked: MainManager.loaderClicked(modelType ? raLoader:rpLoader, index)
	}
}
