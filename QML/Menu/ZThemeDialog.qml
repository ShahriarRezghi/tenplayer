import QtQuick 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3
import STools.Extras 1.0

Popup {
	id: popup
	modal: true

	width: 300
	height: 300

	x: (parent.width-width)/2
	y: (parent.height-height)/2

	property color selectedAccent
	property color selectedPrimary
	property color selectedBackground

	property var modelBackground: [
		MaterialTheme.primary, MaterialTheme.primaryDark
	]

	property var modelPrimary: [
		MaterialTheme.amber, MaterialTheme.blue, MaterialTheme.blueGrey,
		MaterialTheme.brown, MaterialTheme.cyan, MaterialTheme.deepOrange,
		MaterialTheme.deepPurple, MaterialTheme.green, MaterialTheme.grey,
		MaterialTheme.indigo, MaterialTheme.lightBlue, MaterialTheme.lightGreen,
		MaterialTheme.lime, MaterialTheme.orange, MaterialTheme.pink,
		MaterialTheme.purple, MaterialTheme.red, MaterialTheme.teal,
		MaterialTheme.yellow, MaterialTheme.primary, MaterialTheme.primaryDark
	]

	property var modelAccent: [
		MaterialTheme.amber, MaterialTheme.blue, MaterialTheme.blueGrey,
		MaterialTheme.brown, MaterialTheme.cyan, MaterialTheme.deepOrange,
		MaterialTheme.deepPurple, MaterialTheme.green, MaterialTheme.grey,
		MaterialTheme.indigo, MaterialTheme.lightBlue, MaterialTheme.lightGreen,
		MaterialTheme.lime, MaterialTheme.orange, MaterialTheme.pink,
		MaterialTheme.purple, MaterialTheme.red, MaterialTheme.teal,
		MaterialTheme.yellow, MaterialTheme.primary, MaterialTheme.primaryDark
	]

	onClosed: swipe.currentIndex = 0

	signal colorsSelected()

	onColorsSelected: {
		appSettings.accent = selectedAccent
		appSettings.primary = selectedPrimary
		appSettings.background = selectedBackground
		appSettings.foreground = selectedBackground == MaterialTheme.primaryDark ? "white":"black"
	}

	contentItem: SwipeView {
		id: swipe
		clip: true
		interactive: false

		ThemeMainView {
			model: modelBackground
			topText: "Select Background Color"

			onClicked: {
				selectedBackground = c
				swipe.currentIndex = 1
			}
		}

		ThemeMainView {
			model: modelPrimary
			topText: "Select Primary Color"

			onClicked: {
				selectedPrimary = c
				swipe.currentIndex = 2
			}
		}

		ThemeMainView {
			model: modelAccent
			topText: "Select Accent Color"

			onClicked: {
				popup.close()
				selectedAccent = c
				colorsSelected()
			}
		}
	}
}
