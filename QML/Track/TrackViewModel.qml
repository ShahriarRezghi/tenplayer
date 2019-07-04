import QtQuick 2.10
import "../Tools"

VisualDataModel {
	id: vdmodel
	model: TrackModel

	signal menuRequested(real x, real y, int index)

	delegate: ListDelegate {
		property string trackText: discRole != 0 ? trackRole + " / " + discRole:trackRole
		track: trackRole != 0 ? trackText:"?"
		useTrack: isAlbumType
		image: artworkRole ? "file://"+artworkRole:"qrc:/Images/Note.png"

		width: parent.width/2
		model: isAlbumType ? [titleRole, artistRole]:[titleRole, albumRole, artistRole]

		contentItem.implicitHeight: isAlbumType ? 48:80

		playingNow: ActiveInfo.idInfo == idRole

		onMenuRequested: vdmodel.menuRequested(xx+x, yy+y, index)
		onClicked: MainManager.trackClicked(index)
	}
}
