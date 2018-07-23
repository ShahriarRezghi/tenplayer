import QtQuick 2.10
import QtQuick.Controls 2.3
import ExtraControls 1.0
import QtQuick.Layouts 1.3

import "../Tools"

Popup {
	id: popup
	modal: true
	dim: false
	padding: 0
	rightPadding: -1

	width: parent.width*2/5
	height: parent.height*.8

	x: (parent.width-width)/2
	y: (parent.height-height)/2

	property int cat
	property int type
	property int currentIndex

	function openWith(c, t, i)
	{
		cat = c
		type = t
		currentIndex = i
		open()
	}

	contentItem: ColumnLayout {
		spacing: 0

		ListView {
			emptyText: "You Have No Playlists"
			Layout.fillWidth: true
			Layout.fillHeight: true

			model: VisualDataModel {
				model: PlaylistModel

				delegate: ListDelegate {
					width: parent.width
					model: [titleRole]
					image: artworkRole ? artworkRole:""

					onClicked: {
						popup.close()

						if (cat == 1)
							MainManager.loaderActionTriggered(type, 3, currentIndex, index)
						else if (cat == 2)
							MainManager.trackActionTriggered(type, 3, currentIndex, index)
						else if (cat == 3)
							MainManager.loaderSearchActionTriggered(type, 3, currentIndex, index)
					}
				}
			}
		}

		RowLayout {
			Layout.fillHeight: false
			Layout.topMargin: 6
			Layout.bottomMargin: 6
			Layout.leftMargin: 10
			Layout.rightMargin: 10

			TextField {
				id: field
				Layout.fillWidth: true
				placeholderText: "Add Playlist"
			}

			ImageButton {
				source: "qrc:/Images/Plus.png"
				onClicked: MainManager.addPlaylist(field.text)
			}
		}
	}
}
