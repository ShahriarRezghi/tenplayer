import QtQuick 2.10
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3

Popup {
    id: popup
	modal: true
	padding: 20

	x: (parent.width-width)/2
	y: (parent.height-height)/2

	implicitWidth: mv.implicitWidth + leftPadding + rightPadding
	implicitHeight: mv.implicitHeight + topPadding + bottomPadding

	MenuView {
		id: mv
		expand: popup.visible

		onItemClicked: {
			popup.close()

			if (index == 0)
				libraryDialog.open()
			else if (index == 1)
				settingsDialog.open()
			else if (index == 2)
				aboutDialog.open()
			else if (index == 3)
				Qt.quit()
		}
	}
}
