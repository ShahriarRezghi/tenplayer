import QtQuick 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3
import STools.Utils 1.0

GridLayout {
	id: grid

	property bool expand: false
	property real delegateWidth: 50
	property string img: "qrc:/Images/Settings.png"

	property var images: [img, img, img, img, img, img]
	property var names: ["Library", "Settings", "About", "Exit"]

	property real duration: 750

	signal itemClicked(int index)

	Repeater {
		model: names

		delegate: TabButton {
			id: del
			padding: 10
			scale: expand ? 1:.5
			onClicked: itemClicked(index)

			Layout.fillWidth: true
			Layout.fillHeight: true

			Behavior on scale {
				NumberAnimation {
					duration: grid.duration
					easing.type: Easing.OutQuart

				}
			}

			transform: Translate {
				x: expand ? 0:grid.width/2 - (del.x + del.width/2)
				y: expand ? 0:grid.height/2 - (del.y + del.height/2)

				Behavior on x {
					NumberAnimation {
						duration: grid.duration
						easing.type: Easing.OutQuart
					}
				}

				Behavior on y {
					NumberAnimation {
						duration: grid.duration
						easing.type: Easing.OutQuart
					}
				}
			}

			contentItem: Column {
				spacing: 4

				ColoredImage {
					source: images[index]
					height: width
					width: delegateWidth
					colorized: true
					color: Material.foreground
//					sourceSize.width: width
//					sourceSize.height: height
					anchors.horizontalCenter: parent.horizontalCenter
				}

				Label {
					text: modelData
					anchors.horizontalCenter: parent.horizontalCenter
				}
			}
		}
	}
}
