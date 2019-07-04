import QtQuick 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3

import "../Tools"

RowLayout {
	spacing: 0

	TabBar {
		background: null
		Layout.fillWidth: true
		currentIndex: appSettings.currentLoader
		onCurrentIndexChanged: appSettings.currentLoader = currentIndex

		Repeater {
			model: tabs
			delegate: TabButton { text: modelData }
		}
	}

	ImageButton {
		Layout.leftMargin: 5
		Layout.rightMargin: 5
		source: "qrc:/Images/search.png"
		onClicked: openSearchView()
	}
}
