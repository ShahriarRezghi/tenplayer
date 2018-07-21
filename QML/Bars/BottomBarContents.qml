import QtQuick 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3

// contents of playbar
import "../Tools"

Item {
	property string artwork
	property string title
	property string artist

//	Slider {
//		id: slider
//		z: 1
//		width: parent.width
//		anchors.top: parent.top
//	}

	RowLayout {
		id: rowLayout
		anchors.fill: parent

		// this is the artwork shown in the left corner.
		// it can open and close
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

		// this is the column that holds texts like title and artist
		// this is shown on the right side of the artwork
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

		// volume controls. a slider and a button
		Control {
			leftPadding: 20
			rightPadding: 20
			Layout.alignment: Qt.AlignVCenter

			contentItem: RowLayout {
				ImageButton {
					source: MusicPlayer.volume == 0 ? "qrc:/Images/Volume(mute).png":
													  "qrc:/Images/Volume(max).png"

					onClicked: MusicPlayer.volume = MusicPlayer.volume == 0 ? 50:0
				}

				Slider {
					from: 0
					to: 100
					value: MusicPlayer.volume
					onPositionChanged: if (pressed)
										   MusicPlayer.setVolume(position*to)
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

		// play controls. play and pause and ...
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
	}
}
