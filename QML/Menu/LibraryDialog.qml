import QtQuick 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3

Popup {
    id: popup
	modal: true

	topPadding: 8
	bottomPadding: 8
	leftPadding: 0
	rightPadding: 0

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

			onRemoveClicked: PathManager.removeDir(index)
		}

		Rectangle {
			height: 1
			Layout.fillWidth: true
			Layout.leftMargin: 12
			Layout.rightMargin: 12
			color: theme.accentAlt
		}

		LibraryComponent {
			title: "Files"
			model: PathManager.files

			onAddClicked: {
				fileDialog.selectFolder = false
				fileDialog.selectMultiple = true
				fileDialog.open()
			}

			onRemoveClicked: PathManager.removeFile(index)
		}

		RowLayout {
			Layout.rightMargin: 18
			Layout.fillHeight: false
			Layout.alignment: Qt.AlignRight

			Button {
				flat: true
				text: "Reload"

				onClicked: {
					popup.close()
					MainManager.safeLoad()
				}
			}

			Button {
				flat: true
				text: "Close"

				onClicked: popup.close()
			}
		}
	}
}
