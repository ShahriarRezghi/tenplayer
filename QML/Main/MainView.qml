import QtQuick 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3

import "../Bars"
import "../Menu"

Page {
	id: page

	contentItem: MainContents {	}

	MenuDialog {
		id: mainMenu
	}

	LibraryDialog {
		id: libraryDialog
	}

	SettingsDialog {
		id: settingsDialog
	}

	AboutDialog {
		id: aboutDialog
	}
}
