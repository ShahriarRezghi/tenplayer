import QtQuick 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import STools.Extras 1.0

import "../Tools"

ColumnLayout {
	id: column
	spacing: 0

	ImageButton {
		onClicked: popup.close()
		source: "qrc:/Images/Close.png"
	}

	CheckBox {
		text: "Dark Theme"
		checked: ColorAlt.lightness(appSettings.primary) < .5

		onClicked: {
			var prim = checked ? MaterialTheme.primaryDark:MaterialTheme.primary
			appSettings.foreground = checked ? "white":"black"
			appSettings.primary = prim
		}
	}

	CheckBox {
		text: "Color From Artwork"
		checked: appSettings.colorFromArtwork
		onClicked: appSettings.colorFromArtwork = checked
	}

	CheckBox {
		text: "Background From Artwork"
		checked: appSettings.backgroundFromArtwork
		onClicked: appSettings.backgroundFromArtwork = checked
	}

	CheckBox {
		text: "Icon Colors From Accent"
		checked: appSettings.iconFromAccent
		onClicked: appSettings.iconFromAccent = checked
	}

	RowLayout {
		Layout.fillHeight: false

		CheckBox {
			id: backgroundBox
			Layout.fillWidth: true
			text: "Background Image"

			// TODO uncomment
//			checked: backgroundSource != "qrc:/Images/background.jpg"
//			onClicked: if (!checked)
//								  backgroundSource = "qrc:/Images/background.jpg"
		}

		Button {
			text: "Choose"
			enabled: backgroundBox.checked

			onClicked: {
				fileDialog.selectBackground = true
				fileDialog.selectDir = false
				fileDialog.selectMultiple = false
				fileDialog.open()
			}
		}
	}
}
