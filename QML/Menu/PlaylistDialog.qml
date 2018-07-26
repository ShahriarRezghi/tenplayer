import QtQuick 2.10
import ExtraControls 1.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3

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

		// TODO this is here because the model is empty when opened. needs to be
		// reset but this is not a good fix
		view.model = null
		view.model = PlaylistModel
	}

	contentItem: ColumnLayout {
		spacing: 0

		Label {
			text: "Select A Playlist"
			padding: 12
			Layout.fillWidth: true
			font.pointSize: consts.largeFont
			horizontalAlignment: Text.AlignHCenter
		}

		Rectangle {
			height: 1
			opacity: .5
			Layout.fillWidth: true
			Layout.leftMargin: 18
			Layout.rightMargin: 18
			color: theme.background == theme.accent ? theme.primary:theme.accent
		}

		ListView {
			id: view
			Layout.fillWidth: true
			Layout.fillHeight: true
			emptyText: "You Have No Playlists"

			model: PlaylistModel

			delegate: ListDelegate {
				width: parent.width
				model: [titleRole]
				image: artworkRole ? "file://" + artworkRole:"qrc:/Images/Note.png"

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

		Rectangle {
			height: 1
			opacity: .5
			Layout.fillWidth: true
			Layout.leftMargin: 18
			Layout.rightMargin: 18
			color: theme.background == theme.accent ? theme.primary:theme.accent
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
				Material.accent: theme.background == theme.accent ? theme.primary:theme.accent
			}

			Button {
				flat: true
				text: "Add"
				onClicked: MainManager.addPlaylist(field.text)
			}
		}
	}
}
