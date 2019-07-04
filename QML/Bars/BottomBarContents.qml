import QtQuick 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3

import "../Tools"

RowLayout {
	id: rowLayout

	TrackInfoView {

	}

	Control {
		leftPadding: 20
		rightPadding: 20
		Layout.alignment: Qt.AlignVCenter

		contentItem: RowLayout {
			ImageButton {
				source: MusicPlayer.volume == 0 ? "qrc:/Images/Volume(mute).png":
												  "qrc:/Images/Volume(max).png"

				onClicked: MusicPlayer.realVolume = MusicPlayer.realVolume == 0 ? 50:0
			}

			Slider {
				from: 0
				to: 100
				value: MusicPlayer.realVolume
				onValueChanged: MusicPlayer.realVolume = value
			}
		}
	}

	Control {
		rightPadding: 20
		Layout.alignment: Qt.AlignVCenter

		contentItem: RowLayout {
			spacing: 0

			ImageButton {
				source: "qrc:/Images/Min(on).png"

				onClicked: {
					applicationWindow.visibility = ApplicationWindow.Windowed
					appStack.replace(minView)
				}
			}

			ImageButton {
				checkable: true
				source: "qrc:/Images/FullScreen(off).png"

				onClicked: applicationWindow.visibility = checked ?
							   ApplicationWindow.FullScreen:
							   ApplicationWindow.Windowed
			}

			ImageButton {
				checkable: true
				checked: ActiveInfo.shufflable
				source: "qrc:/Images/Shuffle.png"
				onCheckedChanged: ActiveInfo.shufflable = checked
			}

			ImageButton {
				checkable: true
				checked: ActiveInfo.repeatable
				source: "qrc:/Images/Repeat.png"
				onCheckedChanged: ActiveInfo.repeatable = checked
			}
		}
	}

	Control {
		rightPadding: 12
		Layout.alignment: Qt.AlignVCenter

		contentItem: RowLayout {
			spacing: 0

			ImageButton {
				Layout.alignment: Qt.AlignVCenter
				onClicked: MusicPlaylist.previous()
				source: "qrc:/Images/Previous.png"
			}

			ImageButton {
				Layout.alignment: Qt.AlignVCenter

				source: MusicPlayer.state == 1 ? "qrc:/Images/Pause.png":
												 "qrc:/Images/Play.png"

				onClicked: MusicPlayer.state == 1 ? MusicPlayer.pause():
													MusicPlayer.play()
			}

			ImageButton {
				Layout.alignment: Qt.AlignVCenter
				onClicked: MusicPlaylist.next()
				source: "qrc:/Images/Next.png"
			}
		}
	}

	BottomBarController {
		rightPadding: 12
		itemIndex: 1
		Layout.alignment: Qt.AlignVCenter
	}
}
