import QtQuick 2.10
import QtQuick 2.10 as Q
import QtQuick.Controls 2.3
import "."

GridView {
	id: gridView

	property string sectionText
	property alias sectionLabel: label
	property color sectionBackgroundColor: label.linkColor

	signal updateSectionText(var item)

	onContentYChanged: {
		var item = itemAt(1, contentY + 1)
		updateSectionText(item)
	}

	Label {
		id: test
		visible: false
	}

	Label {
		id: label
		z: 10
		padding: 6
		text: sectionText
		anchors.centerIn: parent
		visible: opacity != 0
		opacity: gridView.ScrollBar.vertical.pressed ? 1:0
		horizontalAlignment: Text.AlignHCenter
		font.pointSize: test.font.pointSize*3
		width: Math.max(implicitHeight, implicitWidth)

		background: Rectangle {
			color: sectionBackgroundColor
		}

		Behavior on opacity {
			NumberAnimation {
				easing.type: Easing.OutQuad
				duration: 150
			}
		}
	}
}
