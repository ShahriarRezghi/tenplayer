import QtQuick 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3

Control {
	background: Rectangle {
		color: Material.primary
	}

	contentItem: RowLayout {
		Label {
			padding: 12
			text: MusicPlayer.positionString
			Layout.alignment: Qt.AlignVCenter
		}

		Slider {
			id: mainSlider
			Layout.fillWidth: true

			from: 0
			to: MusicPlayer.duration
			value: MusicPlayer.position
			onValueChanged: if (pressed) MusicPlayer.position = value
		}

		Label {
			padding: 12
			text: MusicPlayer.durationString
			Layout.alignment: Qt.AlignVCenter
		}
	}
}
