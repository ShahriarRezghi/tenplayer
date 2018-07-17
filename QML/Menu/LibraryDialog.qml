import QtQuick 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3

Popup {
	id: popup
	modal: true
	dim: false
	padding: 0

	width: parent.width/2
	height: parent.height*3/4

	x: (parent.width-width)/2
	y: (parent.height-height)/2

	contentItem: ColumnLayout {
		spacing: 0

		LibraryComponent {
			title: "Directories"
			model: PathManager.dirs

			onAddClicked: {
				fileDialog.selectFolder = true
				fileDialog.selectMultiple = false
				fileDialog.open()
			}
		}

		LibraryComponent {
			title: "Files"
			model: PathManager.files

			onAddClicked: {
				fileDialog.selectFolder = false
				fileDialog.selectMultiple = true
				fileDialog.open()
			}
		}

		RowLayout {
			Layout.leftMargin: 6
			Layout.rightMargin: 6
			Layout.bottomMargin: 6
			Layout.fillHeight: false

			Button {
				text: "Reload"
				Layout.fillWidth: true
				Material.background: Material.primary

				onClicked: {
					popup.close()
					MainManager.safeLoad()
					loadDialog.open()
				}
			}

			Button {
				text: "Confirm"
				Layout.fillWidth: true
				Material.background: Material.primary
				onClicked: popup.close()
			}
		}
	}
}
