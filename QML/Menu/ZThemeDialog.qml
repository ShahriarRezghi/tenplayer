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

	// primary
	property var modelPrimary1: [
		MaterialTheme.primary,
		MaterialTheme.amber, MaterialTheme.blue, MaterialTheme.blueGrey,
		MaterialTheme.brown, MaterialTheme.cyan, MaterialTheme.deepOrange,
		MaterialTheme.deepPurple, MaterialTheme.green, MaterialTheme.grey,
		MaterialTheme.indigo, MaterialTheme.lightBlue, MaterialTheme.lightGreen,
		MaterialTheme.lime, MaterialTheme.orange, MaterialTheme.pink,
		MaterialTheme.purple, MaterialTheme.red, MaterialTheme.teal
	]

	// primary dark
	property var modelPrimary2: [
		MaterialTheme.yellow, MaterialTheme.primaryDark,
		MaterialTheme.amber, MaterialTheme.blue, MaterialTheme.blueGrey,
		MaterialTheme.brown, MaterialTheme.cyan, MaterialTheme.deepOrange,
		MaterialTheme.deepPurple, MaterialTheme.green, MaterialTheme.grey,
		MaterialTheme.indigo, MaterialTheme.lightBlue, MaterialTheme.lightGreen,
		MaterialTheme.lime, MaterialTheme.orange, MaterialTheme.pink,
		MaterialTheme.purple, MaterialTheme.red, MaterialTheme.teal
	]

	// non-primary primary color
	property var modelAccent1: [
		MaterialTheme.primary, MaterialTheme.primaryDark
	]

	// primary primary color
	property var modelAccent2: [
		MaterialTheme.amber, MaterialTheme.blue, MaterialTheme.blueGrey,
		MaterialTheme.brown, MaterialTheme.cyan, MaterialTheme.deepOrange,
		MaterialTheme.deepPurple, MaterialTheme.green, MaterialTheme.grey,
		MaterialTheme.indigo, MaterialTheme.lightBlue, MaterialTheme.lightGreen,
		MaterialTheme.lime, MaterialTheme.orange, MaterialTheme.pink,
		MaterialTheme.purple, MaterialTheme.red, MaterialTheme.teal,
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

				if (c == MaterialTheme.primary)
					primarySelector.model = modelPrimary1
				else if (c == MaterialTheme.primaryDark)
					primarySelector.model = modelPrimary2
			}
		}

		ThemeMainView {
			id: primarySelector
			topText: "Select Primary Color"

			onClicked: {
				selectedPrimary = c
				swipe.currentIndex = 2

				if (c == MaterialTheme.primary)
					accentSelector.model = modelAccent2
				else if (c == MaterialTheme.primaryDark)
					accentSelector.model = modelAccent2
				else
					accentSelector.model = modelAccent1
			}
		}

		ThemeMainView {
			id: accentSelector
			topText: "Select Accent Color"

			onClicked: {
				popup.close()
				selectedAccent = c
				colorsSelected()
			}
		}
	}
}
