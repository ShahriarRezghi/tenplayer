import QtQuick 2.10
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

Control {
	id: control
	padding: 6

	property string text
	property var model: []

	property color currentColor: model[currentIndex]
	property alias currentIndex: pathview.currentIndex

	contentItem: ColumnLayout {
		clip: true

		Label {
			id: label
			text: control.text
		}

		Item {
			id: item
			height: 40
			implicitHeight: 40
			Layout.fillWidth: true

			PathView {
				id: pathview

				pathItemCount: width/height
				model: control.model
				height: parent.height
				anchors.centerIn: parent
				preferredHighlightBegin: .5
				preferredHighlightEnd: .5
				snapMode: PathView.SnapToItem

				width: Math.min(model.length*item.height, item.width)

				path: Path {
					startX: 0; startY: pathview.height/2
					PathLine { x: pathview.width; y: pathview.height/2 }
				}

				delegate: Rectangle {
					width: item.height
					height: item.height
					color: modelData

					MouseArea {
						anchors.fill: parent
						onClicked: pathview.currentIndex = index
					}
				}
			}

			Rectangle {
				width: 4
				color: "white"
				height: parent.height
				anchors.centerIn: parent

				Rectangle {
					width: 2
					color: "black"
					height: parent.height
					anchors.centerIn: parent
				}
			}
		}
	}
}
