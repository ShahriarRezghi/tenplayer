import QtQuick 2.10
import "../Tools"

VisualDataModel {
	id: vdmodel
	model: TrackModel

	signal menuRequested(real x, real y, int index)

	delegate: ListDelegate {
		useTrack: true
		track: trackRole != 0 ? trackRole:"?"
		width: parent.width/2
		model: [titleRole, artistRole]

		onMenuRequested: vdmodel.menuRequested(xx+x, yy+y, index)
		onClicked: MainManager.trackClicked(index)
	}
}
