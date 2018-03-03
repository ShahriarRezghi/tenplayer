import QtQuick 2.10
import QtQuick.Controls 2.3

ItemDelegate {
	id: control
	spacing: 10
	padding: 10
	onTextChanged: text = ""

	property string track
	property bool useTrack: false

	property string image
	property var model: []
	property real innerSpacing: 0
	property int horizontalAlignment: Text.AlignJustify

	signal menuRequested(real xx, real yy)

	contentItem.implicitWidth: 200
	contentItem.implicitHeight: Math.max(column.implicitHeight, 48)

	Row {
		parent: contentItem
		anchors.fill: parent
		spacing: control.spacing

		Image {
			id: img
			source: useTrack ? "":control.image
			width: height
			height: parent.height
			sourceSize.width: width
			sourceSize.height: height

			Label {
				text: track
				visible: useTrack
				anchors.fill: parent
				verticalAlignment: Text.AlignVCenter
				horizontalAlignment: Text.AlignHCenter
			}
		}

		Column {
			id: column
			spacing: innerSpacing
			anchors.verticalCenter: parent.verticalCenter
			width: parent.width - img.width - parent.spacing

			Repeater {
				model: control.model

				delegate: Label {
					text: modelData
					width: parent.width
					font: control.font
					elide: Text.ElideRight
					horizontalAlignment: control.horizontalAlignment
				}
			}
		}
	}

	MouseArea {
		id: ma
		parent: control
		anchors.fill: parent
		propagateComposedEvents: true
		acceptedButtons: Qt.LeftButton | Qt.RightButton

		onPressed: {
			if (pressedButtons & Qt.RightButton)
				menuRequested(mouseX, mouseY)

			mouse.accepted = false
		}
	}
}
