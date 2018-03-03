import QtQuick 2.10
import QtQuick.Controls 2.3

import "Main"

ApplicationWindow {
	id: applicationWindow
	visible: true
	width: 640
	height: 480
	title: qsTr("Ten Player")

	function refresh() {
		if (StatusManager.needsRefresh)
		{
			StatusManager.needsRefresh = false
			MainManager.safeRefresh()
		}
	}

	Consts {
		id: consts
	}

	Theme {
		id: theme
	}

	MainView {
		id: mainView
		anchors.fill: parent
	}
}
