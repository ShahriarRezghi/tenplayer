import QtQuick 2.10
import "../STools" as E

E.GridDelegate {
	id: control
	spacing: 8

	topPadding: 16
	bottomPadding: 16

	leftPadding: 12
	rightPadding: 12

	font.bold: true
	asynchronous: true
	horizontalAlignment: Text.AlignHCenter

	signal menuRequested(real xx, real yy)

	onPressAndHold: menuRequested(width/2, height/2)

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
