import QtQuick 2.10
import QtQuick.Controls 2.3

RoundButton {
	id: control
	flat: true
	icon.width: large ? 40:24
	icon.height: large ? 40:24
	icon.color: "transparent"
	display: RoundButton.IconOnly

	onTextChanged: text = ""

	property bool large: false
	property alias name: control.icon.name
	property alias color: control.icon.color
	property alias source: control.icon.source
}
