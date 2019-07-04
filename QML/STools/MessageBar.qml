import QtQuick 2.10
import QtQuick.Controls 2.3

Popup {
	id: control
	padding: 0

	property alias text: label.text
	property alias interval: timer.interval
	property var horizontalAlignment: Text.AlignLeft

	contentItem: ToolBar {
		padding: 10
		topPadding: 8
		bottomPadding: 8

		contentItem: Label {
			id: label
			clip: true
			font: control.font
			verticalAlignment: Text.AlignVCenter
			wrapMode: Text.WrapAtWordBoundaryOrAnywhere
			horizontalAlignment: control.horizontalAlignment
		}
	}

	enter: Transition {
		NumberAnimation { property: "height"; to: control.implicitHeight; easing.type: Easing.OutQuint; duration: 220 }
	}

	exit: Transition {
		NumberAnimation { property: "height"; to: 0; easing.type: Easing.OutQuint; duration: 220 }
	}

	Timer {
		id: timer
		repeat: false
		interval: 1500
		onTriggered: control.visible = false
		running: control.visible && interval > 0
	}
}
