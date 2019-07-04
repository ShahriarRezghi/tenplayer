import QtQuick 2.10
import QtQuick.Controls 2.3

ItemDelegate {
	id: control
	spacing: 10
	font.bold: true
	onTextChanged: text = ""

	topPadding: 10
	bottomPadding: 10
	leftPadding: 10
	rightPadding: 10

	property bool playingNow: false

	property string track
	property bool useTrack: false

	property string image
	property var model: []
	property real innerSpacing: 0
	property int horizontalAlignment: Text.AlignJustify

	signal menuRequested(real xx, real yy)

	onPressAndHold: menuRequested(width/2, height/2)

	contentItem.implicitWidth: 200
	contentItem.implicitHeight: Math.max(column.implicitHeight, 48)

	Row {
		parent: contentItem
		anchors.fill: parent
		spacing: control.spacing

		Image {
			id: img
			asynchronous: true
			source: useTrack ? "":control.image
			width: height
			height: parent.height

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
			width: parent.width - img.width - parent.spacing - (ldr.active ? (parent.spacing + ldr.width):0)

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

		Loader {
			id: ldr
			visible: active
			active: playingNow
			anchors.verticalCenter: parent.verticalCenter

			sourceComponent: ImageButton {
				enabled: false
				source: "qrc:/Images/Play.png"
				icon.color: theme.accentAlt
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
