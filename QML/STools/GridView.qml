import QtQuick 2.10
import QtQuick 2.10 as Q
import QtQuick.Controls 2.3

Q.GridView {
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

	BusyIndicator{
		z: 1000
		running: busy
		anchors.centerIn: parent
	}

	Label {
		z: 999
		padding: 10
		text: emptyText
		visible: root.count == 0 && !busy && text

		width: parent.width
		anchors.centerIn: parent

		horizontalAlignment: Text.AlignHCenter
		wrapMode: Text.WrapAtWordBoundaryOrAnywhere
	}
}
