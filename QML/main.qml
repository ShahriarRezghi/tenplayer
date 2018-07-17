import QtQuick 2.10
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3
import STools.Extras 1.0

import "Main"

ApplicationWindow {
	id: applicationWindow
	visible: true
	width: 640
	height: 480
	title: qsTr("Ten Player")

	// TODO find out where this function is used in the prev version
	function refresh() {
		if (StatusManager.needsRefresh)
		{
			StatusManager.needsRefresh = false
			MainManager.safeRefresh()
		}
	}

	Material.accent: theme.accent
	Material.primary: theme.background
	Material.background: theme.primary
	Material.foreground: theme.foreground
	Material.theme: ColorAlt.lightness(theme.primary) > .5 ?
						Material.Light:Material.Dark

	Consts {
		id: consts
	}

	Theme {
		id: theme
		accent: MaterialTheme.red
		primary: MaterialTheme.primary
		foreground: "black"
		background: MaterialTheme.teal
	}

	Settings {
		id: appSettings

		property alias accent: theme.accent
		property alias primary: theme.primary
		property alias background: theme.background
		property alias foreground: theme.foreground
	}

	MainView {
		id: mainView
		anchors.fill: parent
	}
}
