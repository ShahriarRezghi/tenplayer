import QtQuick 2.10
import STools.Extras 1.0 as E

E.GridDelegate {
	id: control

	spacing: 8
	horizontalAlignment: Text.AlignHCenter

	signal menuRequested(real xx, real yy)

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
