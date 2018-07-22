import QtQuick 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3
import ExtraControls 1.0

import "../Tools"

Popup {
	id: dial
	modal: true
	dim: false
	padding: 0

	width: parent.width*.4
	height: parent.height*.8

	x: (parent.width-width)/2
	y: (parent.height-height)/2

	contentItem: ColumnLayout {
		spacing: 0

		ListView {
			id: lview
			Layout.fillWidth: true
			Layout.fillHeight: true
			orientation: Qt.Horizontal
			snapMode: ListView.SnapOneItem
			boundsBehavior: Flickable.StopAtBounds

			highlightRangeMode: ListView.StrictlyEnforceRange
			preferredHighlightBegin: 0
			preferredHighlightEnd: 0
			highlightMoveDuration: 250

			model: DetailsModel

			delegate: ListView {
				id: col
				width: lview.width
				height: lview.height
				property int lindex: index
				// boundsBehavior: Flickable.StopAtBounds

				property var tops: ["Title", "ID", "Track", "Album", "Artist", "Genre", "Year", "Path", "Artwork"]
				property var contents: [titleRole, idRole, trackRole, albumRole, artistRole, genreRole, yearRole, pathRole, artworkRole]

				model: 9

				delegate: Control {
					padding: 8
					width: parent.width-2
					anchors.horizontalCenter: parent.horizontalCenter

					background: Rectangle {
						color: index == 0 ? Material.primary:"transparent"
					}

					Rectangle {
						visible: index != 0 && index != col.count - 1
						height: 1
						width: parent.width
						color: Material.accent
						anchors.bottom: parent.bottom
					}

					contentItem: RowLayout {
						Column {
							spacing: 2
							Layout.fillWidth: true

							Label {
								width: parent.width
								text: col.tops[index]
							}

							Label {
								width: parent.width
								text: col.contents[index]
								wrapMode: Text.WrapAtWordBoundaryOrAnywhere
							}
						}

						Label {
							text: col.lindex+1 + "/" + lview.count
							leftPadding: 6
							rightPadding: 6
							visible: index == 0
							Layout.fillHeight: true
							verticalAlignment: Text.AlignVCenter
							horizontalAlignment: Text.AlignHCenter
						}
					}
				}
			}
		}

		Button {
			text: "Close"
			Layout.fillWidth: true
			Material.background: Material.primary

			onClicked: dial.close()
		}
	}
}
