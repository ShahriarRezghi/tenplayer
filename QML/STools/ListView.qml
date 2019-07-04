import QtQuick 2.10
import QtQuick 2.10 as Q
import QtQuick.Controls 2.3

Q.ListView {
	id: root
	clip: true
	activeFocusOnTab: true

	property bool busy: false
	property string emptyText

	states: [
		State {
			name: "busy"; when: root.busy
			PropertyChanges { target: root; model: undefined }
		}
	]

	ScrollBar.vertical: ScrollBar { }

	BusyIndicator {
		z: 1000
		running: busy
		anchors.centerIn: parent
	}

	Label {
		id: lbl
		z: 998
		padding: 10
		text: emptyText
		visible: root.count == 0 && !busy && text

		width: parent.width
		anchors.centerIn: parent

		horizontalAlignment: Text.AlignHCenter
		wrapMode: Text.WrapAtWordBoundaryOrAnywhere
	}

	property bool hasSectionLabel: false
	property real sectionLabelFontPointSize: lbl.font.pointSize*3

	Label {
		id: label
		z: 999
		padding: 10
		text: currentSection
		visible: opacity != 0 && hasSectionLabel
		anchors.centerIn: parent

		font.pointSize: sectionLabelFontPointSize
		opacity: !root.ScrollBar.vertical ? 0:root.ScrollBar.vertical.pressed ? 1:0

		background: Rectangle {
			// TODO Assign color
			color: label.linkColor
		}

		Behavior on opacity {
			NumberAnimation {
				duration: 200
			}
		}
	}
}
