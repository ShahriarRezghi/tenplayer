import QtQuick 2.10
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3
import STools.Extras 1.0
import STools.Utils 1.0

import "Main"
import "Min"

ApplicationWindow {
	id: applicationWindow
	visible: true
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
		primary: appSettings.primary
		foreground: appSettings.foreground

		accent: !appSettings.colorFromArtwork || !ActiveInfo.artworkInfo
				? appSettings.accent:colorExtractor.secondColor

		background: !appSettings.colorFromArtwork || !ActiveInfo.artworkInfo
					? appSettings.background:colorExtractor.firstColor
	}

	Settings {
		id: appSettings

		property color foreground: "black"
		property color accent: MaterialTheme.purple
		property color primary: MaterialTheme.primary
		property color background: MaterialTheme.teal
	}

	Connections {
		target: ActiveInfo

		onRowChanged: if (appSettings.backgroundFromArtwork && ActiveInfo.artworkInfo)
								colorExtractor.extractImage(ActiveInfo.artworkInfo)
	}

	ColorExtractor {
		id: colorExtractor
	}

	StackView {
		id: appStack
		visible: !busy
		anchors.fill: parent
		initialItem: mainView

		Component {
			id: mainView
			MainView { objectName: "Main" }
		}

		Component {
			id: minView
			MinView { objectName: "Min" }
		}
	}

	BusyIndicator {
		running: appStack.busy
		anchors.centerIn: appStack
	}

	property bool isInMin: appStack.currentItem.objectName == "Min"
	flags: isInMin ? Qt.Window | Qt.FramelessWindowHint:Qt.Window
	property real minModeSize: 300

	height: isInMin ? minModeSize:600
	width: isInMin ? minModeSize:600*16/9

	minimumWidth: isInMin ? minModeSize:480
	minimumHeight: isInMin ? minModeSize:360
}
