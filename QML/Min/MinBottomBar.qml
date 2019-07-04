import QtQuick 2.10
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3
import "../STools"
import QtQuick.Layouts 1.3

import "../Tools"

Control {
	id: control
	padding: 6
	leftPadding: 10
	rightPadding: 10
	height: expand ? implicitHeight:0

	property bool expand

	Behavior on height {
		NumberAnimation { }
	}

	background: Item {
		layer.enabled: true
		layer.effect: ElevationEffect {
			elevation: 8
		}

		Rectangle {
			anchors.fill: parent
			color: Material.primary
		}
	}

	contentItem: RowLayout {
		id: row

		ImageButton {
			source: "qrc:/Images/Min(off).png"
			onClicked: appStack.replace(mainView)
		}

		Item { Layout.fillWidth: true }

		ImageButton {
			onClicked: MusicPlayer.prev()
			source: "qrc:/Images/Previous.png"
		}

		Item { Layout.fillWidth: true }

		ImageButton {
			source: MusicPlayer.state == 1 ? "qrc:/Images/Pause.png":
											 "qrc:/Images/Play.png"
			onClicked: MusicPlayer.state == 1 ? MusicPlayer.pause():
												MusicPlayer.play()
		}

		Item { Layout.fillWidth: true }

		ImageButton {
			onClicked: MusicPlayer.next()
			source: "qrc:/Images/Next.png"
		}

		Item { Layout.fillWidth: true }

		ImageButton {
			source: "qrc:/Images/Menu.png"
			onClicked: swipeView.currentIndex = 1
		}
	}
}
