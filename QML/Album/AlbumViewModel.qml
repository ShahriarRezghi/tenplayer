import QtQuick 2.10
import "../Tools"

VisualDataModel {
	id: vdmodel
	model: AlbumModel

	signal menuRequested(real x, real y, int index)

	delegate: GridDelegate {
		id: del
		width: cellWidth
		model: [albumRole, albumartistRole]
		image: artworkRole ? "file://"+artworkRole:"qrc:/Images/Note.png"

		onMenuRequested: vdmodel.menuRequested(xx+x, yy+y, index)

		onClicked: {
			MainManager.loaderClicked(consts.albumLoader, index)
			openTrackView(artworkRole, "Album: " + albumRole,
						  "Artist: " + albumartistRole, "Genre: " + genreRole,
						  "Year: " + yearRole, consts.albumLoader)
		}
	}
}
