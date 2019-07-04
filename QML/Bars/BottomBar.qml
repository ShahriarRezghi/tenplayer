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
		},
		Transition {
			from: "up"
			to: "down"

			NumberAnimation {
				property: "y"
				target: control
				duration: 400
				easing.type: Easing.OutCubic
			}
		},
		Transition {
			from: "down"
			to: "up"

			NumberAnimation {
				property: "y"
				target: control
				duration: 400
				easing.type: Easing.OutCubic
			}
		}
	]

	contentItem: StackView {
		id: bottomBarStack
		clip: true
		initialItem: mainBar

		property int stackIndex

		onStackIndexChanged: {
			if (stackIndex == 0)
				bottomBarStack.replace(mainBar, StackView.PopTransition)
			else if (stackIndex == 1)
				bottomBarStack.replace(seekBar, StackView.ReplaceTransition)
		}

		popEnter: Transition {
			NumberAnimation { property: "y"; from: -control.height; to: 0; duration: 200; easing.type: Easing.OutCubic }
		}

		popExit: Transition {
			NumberAnimation { property: "y"; from: 0; to: control.height; duration: 200; easing.type: Easing.OutCubic }
		}

		replaceEnter: Transition {
			NumberAnimation { property: "y"; from: control.height; to: 0; duration: 200; easing.type: Easing.OutCubic }
		}

		replaceExit: Transition {
			NumberAnimation { property: "y"; from: 0; to: -control.height; duration: 200; easing.type: Easing.OutCubic }
		}

		Component {
			id: mainBar

			BottomBarContents { }
		}

		Component {
			id: seekBar
			BottomBarSeekView { }
		}
	}
}
