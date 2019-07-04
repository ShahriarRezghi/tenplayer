import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3

RowLayout {

	property string title: ActiveInfo.titleInfo
	property string artist: ActiveInfo.artistInfo
	property string artwork: ActiveInfo.artworkInfo ? "file://" + ActiveInfo.artworkInfo:""

	Item {
		id: item
		clip: true

		implicitWidth: width
		implicitHeight: height

		height: control.height
		width: artwork ? height:0

		Behavior on width { SmoothedAnimation { } }

		Image {
			source: artwork

			width: height
			height: parent.height

			//				sourceSize.width: width
			//				sourceSize.height: height
		}
	}

	Column {
		Layout.fillWidth: true
		Layout.alignment: Qt.AlignVCenter

		Label {
			text: title
			width: parent.width
			elide: Text.ElideRight
		}

		Label {
			text: artist
			width: parent.width
			elide: Text.ElideRight
		}
	}
}
