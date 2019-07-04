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
		leftPadding: 12
		rightPadding: 12
		Layout.fillWidth: true

		contentItem: RowLayout {
			spacing: 10

			Label {
				text: title
				elide: Text.ElideMiddle
				Layout.fillWidth: true
				Layout.alignment: Qt.AlignVCenter
				font.pointSize: consts.mediumFont
			}

			Button {
				flat: true
				text: "Add"
				onClicked: addClicked()
			}
		}
	}

	Rectangle {
		opacity: .5
		height: 1
		Layout.fillWidth: true
		Layout.leftMargin: 20
		Layout.rightMargin: 20
		color: theme.accentAlt
	}

	ListView {
		clip: true
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
