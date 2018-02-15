import QtQuick 2.10
import QtQuick.Controls 2.3

ApplicationWindow {
	visible: true
	width: 640
	height: 480
	title: qsTr("Tabs")

	SwipeView {
		id: swipeView
		anchors.fill: parent
		currentIndex: tabBar.currentIndex

		Page1Form {
		}

		Page2Form {
		}
	}

	footer: TabBar {
		id: tabBar
		currentIndex: swipeView.currentIndex

		TabButton {
			text: qsTr("Page 1")
		}
		TabButton {
			text: qsTr("Page 2")
		}
	}
}
