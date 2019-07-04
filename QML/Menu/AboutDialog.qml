import QtQuick 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3

import "../Tools"

Popup {
    id: popup
	modal: true

	topPadding: 12
	bottomPadding: 24
	leftPadding: 24
	rightPadding: 24

	x: (parent.width-width)/2
	y: (parent.height-height)/2

	property string aboutText:
		"This is an open-source software written by Shahriar Rezghi.
The github page for this project is https://shahriarss.github.io/TenPlayer/
Any issues or suggestions are welcome.
My Email address is shahriar25.ss@gmail.com"

	contentItem: Item {
		implicitHeight: column.implicitHeight
		implicitWidth: label.contentWidth

		Column {
			id: column
			spacing: 10
			anchors.fill: parent

			Label {
				text: "About"
				font.pointSize: consts.largeFont
				anchors.horizontalCenter: parent.horizontalCenter
				color: theme.accentAlt
			}

			Label {
				id: label
				text: aboutText
				wrapMode: Text.WrapAtWordBoundaryOrAnywhere
			}
		}
	}
}
