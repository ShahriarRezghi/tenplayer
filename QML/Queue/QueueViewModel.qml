import QtQuick 2.10
import "../Tools"
import ".."

VisualDataModel {
	id: vdmodel
	model: QueueModel

	delegate: GridDelegate {
		padding: 0
		antialiasing: true
		width: minView ? PathView.view.height*.5:PathView.view.width/5
		background.scale: (width+20)/width

		z: PathView.iconZ
		scale: PathView.iconScale

		model: [titleRole, artistRole, albumRole]
		image: artworkRole ? "file://"+artworkRole:"qrc:/Images/Note.png"

		onClicked: MainManager.loaderClicked(consts.queueLoader, index)
	}
}
