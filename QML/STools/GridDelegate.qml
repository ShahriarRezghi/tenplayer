import QtQuick 2.10
import QtQuick.Controls 2.3

ItemDelegate {
	id: control

	onTextChanged: text = ""

	property string image
	property var model: []
	property real innerSpacing: 0
	property bool asynchronous: false
	property int horizontalAlignment: Text.AlignJustify

	contentItem.implicitWidth: 100
	contentItem.implicitHeight: column.implicitHeight

	Column {
		id: column
		parent: contentItem
		width: parent.width
		spacing: control.spacing

		Image {
			source: control.image
			height: width
			width: parent.width
			asynchronous: control.asynchronous
		}

		Column {
			width: parent.width
			spacing: innerSpacing

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
}
