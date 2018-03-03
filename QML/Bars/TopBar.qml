import QtQuick 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3

ToolBar {
	id: control

	property int currentTab
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
		spacing: 0

		StackView {
			id: stack
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

		ToolButton {
			text: "Menu"
			leftPadding: 12
			rightPadding: 12
			Layout.fillHeight: true
			onClicked: mainMenu.open()
		}
	}
}
