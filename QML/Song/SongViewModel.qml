import QtQuick 2.10
import "../Tools"

VisualDataModel {
	id: vdmodel
	model: SongModel

	signal menuRequested(real x, real y, int index)

	delegate: ListDelegate {
		id: del
		spacing: 10
		width: cellWidth
		model: [titleRole, albumRole, artistRole]
		image: artworkRole ? "file://"+artworkRole:"qrc:/Images/Note.png"

		contentItem.implicitHeight: 80
		playingNow: ActiveInfo.idInfo == idRole

		onMenuRequested: vdmodel.menuRequested(xx+x, yy+y, index)
		onClicked: MainManager.loaderClicked(consts.songLoader, index)
	}
}
