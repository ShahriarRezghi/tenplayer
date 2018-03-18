import QtQuick 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3

import "../Tools"

ColumnLayout {
	id: column
	spacing: 0

	property var model
	property string title

	signal addClicked()
	signal removeClicked(int index)

	Control {
		Layout.fillWidth: true

		background: Rectangle {
			color: Material.primary
		}

		contentItem: RowLayout {
			Label {
				text: title
				leftPadding: 6
				rightPadding: 6
				elide: Text.ElideMiddle
				Layout.fillWidth: true
				Layout.alignment: Qt.AlignVCenter
				font.pointSize: consts.mediumFont
			}

			ImageButton {
				source: "qrc:/Images/Plus.png"
				onClicked: addClicked()
				implicitWidth: 36
				implicitHeight: 36
			}
		}
	}

	ListView {
		model: column.model
		Layout.fillWidth: true
		Layout.fillHeight: true

		delegate: ItemDelegate {
			padding: 8
			text: modelData
			width: parent.width
			onClicked: removeClicked(index)
		}
	}
}
