import QtQuick 2.10
import "../Tools"

VisualDataModel {
	id: vdmodel
	model: loader == albumLoader ? AlbumSearchModel:
			(loader == artistLoader ? ArtistSearchModel:
				(loader == songLoader ? SongSearchModel:null))

	property int loader

	signal menuRequested(real x, real y, int index)

	delegate: ListDelegate {
		width: parent.width
		image: artworkRole ? "file://" + artworkRole:"qrc:/Images/Note.png"

		model: {
			loader == albumLoader ? [albumRole]:
				(loader == artistLoader ? [artistRole]:
					(loader == songLoader ? [titleRole]:null))
		}

		onMenuRequested: vdmodel.menuRequested(xx+x, yy+y, index)

		onClicked: {
			MainManager.loaderSearchClicked(vdmodel.loader, index)

			if (vdmodel.loader == albumLoader || vdmodel.loader == artistLoader)
			{
				var tel = (vdmodel.loader == albumLoader)

				openTrackView(artworkRole, tel ? albumRole:artistRole,
											tel ? albumartistRole:"",
												  tel ? genreRole:"",
														tel ? yearRole:"",
															  vdmodel.loader)
			}
		}
	}
}
