import QtQuick 2.10
import "../Tools"

Item {
	id: item
	clip: true

	BackgroundImage {
		anchors.fill: parent
		source: ActiveInfo.activeArtworkInfo ?
					"file://"+ActiveInfo.activeArtworkInfo:
					appSettings.backgroundSource
	}

	MinBottomBar {
		expand: true
		width: parent.width
		height: parent.height/5
		anchors.bottom: parent.bottom
	}
}
