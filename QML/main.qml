import QtQuick 2.10
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3
import ColorExtractor 1.0
import Qt.labs.settings 1.0

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
    Material.primary: theme.primary
    Material.background: theme.background
	Material.foreground: theme.foreground
	Material.theme: ColorAlt.lightness(theme.background) > .5 ?
						Material.Light:Material.Dark

	Consts {
		id: consts
	}

	Theme {
		id: theme

		foreground: ColorAlt.lightness(theme.background) > .5 ? "black":"white"

		accent: !appSettings.colorFromArtwork || !ActiveInfo.artworkInfo
				? appSettings.accent:(ColorAlt.areDistant(colorExtractor.secondColor, colorExtractor.firstColor) ?
										  colorExtractor.secondColor:ColorAlt.invert(colorExtractor.secondColor)) // TODO is inverting the answer?

		primary: !appSettings.colorFromArtwork || !ActiveInfo.artworkInfo
					? appSettings.primary:colorExtractor.firstColor

		background: !appSettings.colorFromArtwork || !ActiveInfo.artworkInfo
				? appSettings.background:(ColorAlt.lightness(colorExtractor.firstColor)>.5 ?
											  consts.primaryColor:consts.primaryDarkColor)
	}

	AppSettings {
		id: appSettings
	}

	Settings {
		property alias delegatesScale: appSettings.delegatesScale
		property alias currentLoader: appSettings.currentLoader

		property alias imageOpacity: appSettings.imageOpacity
		property alias minViewSize: appSettings.minViewSize

		property alias iconFromAccent: appSettings.iconFromAccent
		property alias colorFromArtwork: appSettings.colorFromArtwork
		property alias backgroundFromArtwork: appSettings.backgroundFromArtwork

		property alias backgroundSource: appSettings.backgroundSource

		property alias accent: appSettings.accent
		property alias primary: appSettings.primary
		property alias background: appSettings.background

		property alias x: applicationWindow.x
		property alias y: applicationWindow.y

        property alias width: appSettings.appWidth
        property alias height: appSettings.appHeight
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
//    flags: isInMin ? Qt.Window | Qt.FramelessWindowHint:Qt.Window

    width: isInMin ? appSettings.minViewSize:appSettings.appWidth
    height: isInMin ? appSettings.minViewSize:appSettings.appHeight

    onWidthChanged: if (!isInMin) appSettings.appWidth = width
    onHeightChanged: if (!isInMin) appSettings.appHeight = height

    minimumWidth: isInMin ? appSettings.minViewSize:480
    minimumHeight: isInMin ? appSettings.minViewSize:360
}
