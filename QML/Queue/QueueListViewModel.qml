import QtQuick 2.10
import "../Tools"

VisualDataModel {
	id: vdmodel
	model: QueueModel

	delegate: ListDelegate {
		width: cellWidth
		model: [titleRole, artistRole, albumRole]
		image: artworkRole ? "file://"+artworkRole:"qrc:/Images/Note.png"

		playingNow: ActiveInfo.idInfo == idRole

		onClicked: MainManager.loaderClicked(consts.queueLoader, index)
	}
}
