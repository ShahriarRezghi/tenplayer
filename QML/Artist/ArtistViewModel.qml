import QtQuick 2.10
import "../Tools"

VisualDataModel {
	id: vdmodel
	model: ArtistModel

	signal menuRequested(real x, real y, int index)

	delegate: ListDelegate {
		id: del
		spacing: 10
		width: cellWidth
		model: [artistRole]
		image: artworkRole ? "file://"+artworkRole:"qrc:/Images/Note.png"

		onMenuRequested: vdmodel.menuRequested(xx+x, yy+y, index)

		onClicked: {
			MainManager.loaderClicked(consts.artistLoader, index)
			openTrackView(artworkRole, "Artist: " + artistRole,
						  "", "", "", consts.artistLoader)
		}
	}
}
