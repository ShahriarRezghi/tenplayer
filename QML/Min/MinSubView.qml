import QtQuick 2.10
import "../Tools"

Item {
	id: item
	clip: true

	BackgroundImage {
		anchors.fill: parent
		source: ActiveInfo.artworkInfo ?
					"file://"+ActiveInfo.artworkInfo:
					appSettings.backgroundSource
	}

	MinBottomBar {
		expand: true
		width: parent.width
		height: parent.height/5
		anchors.bottom: parent.bottom
	}
}
