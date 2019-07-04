import QtQuick 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3

import "../Tools"

ToolBar {
	id: control

	property int stackIndex
	property var tabs: ["Albums", "Artists", "Songs", "Recent", "Playlists"]

	property string infoImage
	property string infoText1
	property string infoText2
	property string infoText3
	property string infoText4

	onStackIndexChanged: {
		if (stackIndex == 0)
			stack.replace(tabBar, StackView.PopTransition)
		else if (stackIndex == 1)
			stack.replace(infoBar, StackView.ReplaceTransition)
		else if (stackIndex == 2)
			stack.replace(searchBar, StackView.ReplaceTransition)
	}

	contentItem: RowLayout {
		visible: opacity

		Behavior on opacity {
			NumberAnimation { }
		}

		spacing: 0

		StackView {
			id: stack
			clip: true
			initialItem: tabBar
			Layout.fillWidth: true
			Layout.fillHeight: true

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
				id: infoBar
				TopBarInfo { }
			}

			Component {
				id: tabBar
				TopBarTabbar { }
			}

			Component {
				id: searchBar
				TopBarSearch { }
			}
		}

		ImageButton {
			source: "qrc:/Images/Menu.png"
			onClicked: mainMenu.open()
		}
	}

	property string dialMessage

	Label {
		id: dial
		opacity: 0
		visible: opacity
		text: dialMessage
		font.pointSize: consts.mediumFont

		parent: control
		anchors.fill: parent

		horizontalAlignment: Text.AlignHCenter
		verticalAlignment: Text.AlignVCenter

		Behavior on opacity {
			NumberAnimation { }
		}
	}

	Timer {
		id: timer
		interval: 1500
		repeat: false
		running: false

		onTriggered: {
			dial.opacity = 0
			control.contentItem.opacity = 1
		}
	}

	function showMessage(type) {
		timer.restart()
		dialMessage = "Track File Not Found!"
		dial.opacity = 1
		control.contentItem.opacity = 0
	}

	Connections {
		target: ActiveInfo
		onShowMessage: showMessage(value)
	}
}
