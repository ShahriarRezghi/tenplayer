import QtQuick 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3

Popup {
    id: popup
	modal: true

	width: 300
	height: 300

	x: (parent.width-width)/2
	y: (parent.height-height)/2

	function c(c) {
		return Material.color(c)
	}

	property color selectedAccent
	property color selectedPrimary
	property color selectedBackground

	property var modelBackground: [
		consts.primaryColor, consts.primaryDarkColor
	]

	// primary
	property var modelPrimary1: [
		consts.primaryColor,
		c(Material.Amber), c(Material.Blue), c(Material.BlueGrey),
		c(Material.Brown), c(Material.Cyan), c(Material.DeepOrange),
		c(Material.DeepPurple), c(Material.Green), c(Material.Grey),
		c(Material.Indigo), c(Material.LightBlue), c(Material.LightGreen),
		c(Material.Lime), c(Material.Orange), c(Material.Pink),
		c(Material.Purple), c(Material.Red), c(Material.Teal)
	]

	// primary dark
	property var modelPrimary2: [
		c(Material.Yellow), consts.primaryDarkColor,
		c(Material.Amber), c(Material.Blue), c(Material.BlueGrey),
		c(Material.Brown), c(Material.Cyan), c(Material.DeepOrange),
		c(Material.DeepPurple), c(Material.Green), c(Material.Grey),
		c(Material.Indigo), c(Material.LightBlue), c(Material.LightGreen),
		c(Material.Lime), c(Material.Orange), c(Material.Pink),
		c(Material.Purple), c(Material.Red), c(Material.Teal)
	]

	// non-primary primary color
	property var modelAccent1: [
		consts.primaryColor, consts.primaryDarkColor
	]

	// primary primary color
	property var modelAccent2: [
		c(Material.Amber), c(Material.Blue), c(Material.BlueGrey),
		c(Material.Brown), c(Material.Cyan), c(Material.DeepOrange),
		c(Material.DeepPurple), c(Material.Green), c(Material.Grey),
		c(Material.Indigo), c(Material.LightBlue), c(Material.LightGreen),
		c(Material.Lime), c(Material.Orange), c(Material.Pink),
		c(Material.Purple), c(Material.Red), c(Material.Teal),
	]

	onClosed: swipe.currentIndex = 0

	signal colorsSelected()

	onColorsSelected: {
		appSettings.accent = selectedAccent
		appSettings.primary = selectedPrimary
		appSettings.background = selectedBackground
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

				if (c == consts.primaryColor)
					primarySelector.model = modelPrimary1
				else if (c == consts.primaryDarkColor)
					primarySelector.model = modelPrimary2
			}
		}

		ThemeMainView {
			id: primarySelector
			topText: "Select Primary Color"

			onClicked: {
				selectedPrimary = c
				swipe.currentIndex = 2

				if (c == consts.primaryColor)
					accentSelector.model = modelAccent2
				else if (c == consts.primaryDarkColor)
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
