import QtQuick 2.10
import "../Tools"

VisualDataModel {
	id: vdmodel
	model: PlaylistModel

	signal menuRequested(real x, real y, int index)

	delegate: GridDelegate {
		id: del
		width: cellWidth
		model: [titleRole]
		image: artworkRole ? "file://"+artworkRole:"qrc:/Images/Note.png"

		onMenuRequested: vdmodel.menuRequested(xx+x, yy+y, index)

		onClicked: {
			MainManager.loaderClicked(consts.playlistLoader, index)
			openTrackView(artworkRole, "Title: " + titleRole) // TODO right?
		}
	}
}
