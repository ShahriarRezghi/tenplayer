import QtQuick 2.10
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3

import "../Album"
import "../Artist"
import "../Song"

RowLayout {
	id: row
	spacing: 0

	SubSearchView {
		title: "Album"
		loader: consts.albumLoader
	}

	Rectangle {
		width: 1
		Layout.fillHeight: true
		color: Material.accent
	}

	SubSearchView {
		title: "Artist"
		loader: consts.artistLoader
	}

	Rectangle {
		width: 1
		Layout.fillHeight: true
		color: Material.accent
	}

	SubSearchView {
		title: "Song"
		loader: consts.songLoader
	}
}
