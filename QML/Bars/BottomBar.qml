import QtQuick 2.10
import QtQuick.Controls 2.3

ToolBar {
	id: control
	height: 48
	state: "down"

	MouseArea {
		id: mouseArea
		parent: background
		anchors.fill: parent
		drag.axis: Drag.YAxis
		drag.target: control
		drag.minimumY: 0
		drag.maximumY: control.parent.height-control.height

		onPressed: control.state = "held"

		onReleased: {
			var up = control.y < (control.parent.height - control.height)/2
			control.state = up ? "up":"down"
		}
	}

	states: [
		State {
			name: "up"
			PropertyChanges { target: control; y: 0 }
		},
		State {
			name: "down"
			PropertyChanges {
				target: control; y: control.parent.height - control.height
			}
		},
		State {
			name: "held"
			PropertyChanges { target: control; y: y }
		}
	]

	transitions: [
		Transition {
			from: "held"
			to: "up"

			NumberAnimation {
				property: "y"
				target: control
				duration: 400
				easing.type: Easing.OutCubic
			}
		},
		Transition {
			from: "held"
			to: "down"

			NumberAnimation {
				property: "y"
				target: control
				duration: 400
				easing.type: Easing.OutCubic
			}
		}
	]

	 contentItem: BottomBarContents {
		title: ActiveInfo.titleInfo
		artist: ActiveInfo.artistInfo
		artwork: ActiveInfo.artworkInfo ? "file://" + ActiveInfo.artworkInfo:""
	 }
}
