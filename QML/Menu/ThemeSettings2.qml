import QtQuick 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import STools.Extras 1.0

import "../Tools"

ColumnLayout {
	id: column
	spacing: 0

	property var colors: [
		MaterialTheme.amber, MaterialTheme.blue, MaterialTheme.blueGrey,
		MaterialTheme.brown, MaterialTheme.cyan, MaterialTheme.deepOrange,
		MaterialTheme.deepPurple, MaterialTheme.green, MaterialTheme.grey,
		MaterialTheme.indigo, MaterialTheme.lightBlue, MaterialTheme.lightGreen,
		MaterialTheme.lime, MaterialTheme.orange, MaterialTheme.pink,
		MaterialTheme.purple, MaterialTheme.red, MaterialTheme.teal,
		MaterialTheme.yellow, MaterialTheme.primary, MaterialTheme.primaryDark
	]

	RowLayout {
		Layout.fillHeight: false

		Label {
			padding: 6
			Layout.fillWidth: true
			text: "Background Opacity"
		}

		Slider {
			Layout.fillWidth: true
			value: imageOpacity
			onValueChanged: imageOpacity = value
		}
	}

	RowLayout {
		Layout.fillHeight: false

		Label {
			padding: 6
			Layout.fillWidth: true
			text: "Blur Opacity"
		}

		Slider {
			Layout.fillWidth: true
			value: blurOpacity
			onPositionChanged: blurOpacity = value
		}
	}

	RowLayout {
		Layout.fillHeight: false

		Label {
			padding: 6
			Layout.fillWidth: true
			text: "Min View Size"
		}

		Slider {
			Layout.fillWidth: true
		}
	}

	ColorSelector {
		model: colors
		text: "Theme Color"
		Layout.fillWidth: true
		Layout.bottomMargin: 12

		currentIndex: model.indexOf(appSettings.background)
		onCurrentColorChanged: appSettings.background = currentColor
	}

	ColorSelector {
		model: colors
		text: "Accent Color"
		Layout.fillWidth: true

		currentIndex: model.indexOf(appSettings.accent)
		onCurrentColorChanged: appSettings.accent = currentColor
	}
}
