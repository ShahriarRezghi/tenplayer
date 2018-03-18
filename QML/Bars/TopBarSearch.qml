import QtQuick 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3

import "../Tools"

RowLayout {
	id: root
	spacing: 6

	TextField {
		id: searchField
		Layout.fillWidth: true
		Layout.leftMargin: 10
		placeholderText: "Enter Title, Album Or Artist To Search"

		onTextChanged: MainManager.search(text)
	}

	ImageButton {
		source: "qrc:/Images/Close.png"
		onClicked: searchField.clear()
	}

	ImageButton {
		Layout.rightMargin: 5
		source: "qrc:/Images/Back.png"

		onClicked: {
			openMusicView()
			MainManager.search("")
		}
	}
}
