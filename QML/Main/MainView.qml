import QtQuick 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import QtQuick.Dialogs 1.2

import "../Bars"
import "../Menu"
import "../Tools"

Page {
	id: page

	background: BackgroundImage {
		id: backgroundImage
		anchors.fill: parent
		opacity: appSettings.imageOpacity

		source: appSettings.backgroundFromArtwork && ActiveInfo.artworkInfo ?
					"file://"+ActiveInfo.artworkInfo:
					appSettings.backgroundSource
	}


	contentItem: MainContents {	}

	MenuDialog {
		id: mainMenu
	}

	LibraryDialog {
		id: libraryDialog
	}

	AboutDialog {
		id: aboutDialog
	}

	FileDialog {
		id: fileDialog

		onAccepted: {
			if (selectFolder) PathManager.addDir(folder)
			else PathManager.addFiles(fileUrls)
		}
	}

	LoadDialog {
		id: loadDialog
	}

	DetailsDialog {
		id: detailsDialog
	}

	PlaylistDialog {
		id: playlistDialog
	}

	AddPlaylistDialog {
		id: addPlaylistDialog
	}

//	SettingsDialog {
//		id: settingsDialog
//	}

	ZSettingsDialog {
		id: settingsDialog
	}

	ZThemeDialog {
		id: themeDialog
	}
}
