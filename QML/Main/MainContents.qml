import QtQuick 2.10
import QtQuick.Controls 2.3

import "../Bars"
import "../Queue"

Page {
	id: page
	background: null

	function openTrackView(artwork, text1, text2, text3, text4, type) {
		var A = artwork ? "file://" + artwork:""
		appTopBar.infoImage = A
		appTopBar.infoText1 = text1
		appTopBar.infoText2 = text2
		appTopBar.infoText3 = text3
		appTopBar.infoText4 = text4
		appTopBar.stackIndex = 1
		mainStack.stackIndex = 1
		mainStack.trackType = type
	}

	function openPlaylistTrackView(artwork, title) {
		var A = artwork ? "file://" + artwork:""
		appTopBar.infoImage = A
		appTopBar.infoText1 = title
		appTopBar.infoText2 = ""
		appTopBar.infoText3 = ""
		appTopBar.infoText4 = ""
		appTopBar.stackIndex = 1
		mainStack.stackIndex = 3
	}

	function openSearchView() {
		appTopBar.stackIndex = 2
		mainStack.stackIndex = 2
	}

	function openMusicView() {
		appTopBar.stackIndex = 0
		mainStack.stackIndex = 0
	}

	TopBar {
		id: appTopBar
		z: 1
		width: parent.width
	}

	MainStackView {
		id: mainStack
		anchors.fill: parent
		anchors.topMargin: appTopBar.height
		anchors.bottomMargin: appBottomBar.height
	}

	BottomBar {
		id: appBottomBar
		z: 2
		width: parent.width
	}

	Item {
		z: 1
		clip: true
		width: parent.width
		anchors.bottom: parent.bottom
		anchors.top: appBottomBar.bottom

		ActiveView {
			id: activeView
			anchors.centerIn: parent
			width: page.width
			height: page.height-appBottomBar.height
		}
	}
}
