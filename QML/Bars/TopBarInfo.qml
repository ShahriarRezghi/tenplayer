import QtQuick 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3

import "../Tools"

RowLayout {
	id: root

	Item {
		width: height
		height: control.height

		implicitWidth: width
		implicitHeight: height

		Image {
			source: control.infoImage
			anchors.fill: parent
//			sourceSize.width: width
//			sourceSize.height: height
			visible: status == Image.Ready
		}
	}

	Control {
		leftPadding: 10
		rightPadding: 10
		Layout.fillWidth: true
		Layout.alignment: Qt.AlignVCenter

		contentItem: Grid {
			id: grid
			rows: 2
			columns: 2
			columnSpacing: 6

			Label {
				visible: text
				text: control.infoText1
				elide: Text.ElideRight
				width: parent.width/2-3
			}

			Label {
				visible: text
				text: control.infoText2
				elide: Text.ElideRight
				width: parent.width/2-3
			}

			Label {
				visible: text
				text: control.infoText3
				elide: Text.ElideRight
				width: parent.width/2-3
			}

			Label {
				visible: text
				text: control.infoText4
				elide: Text.ElideRight
				width: parent.width/2-3
			}
		}
	}

	ImageButton {
		Layout.rightMargin: 5
		source: "qrc:/Images/Back.png"
		onClicked: openMusicView()
	}
}
