import QtQuick 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3

Popup {
	id: popup
	modal: true

	x: (parent.width-width)/2
	y: (parent.height-height)/2

	contentItem: RowLayout {
		spacing: 15

		ColumnLayout {
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
				text: "Icons Color From Accent"
				checked: appSettings.iconFromAccent
				onClicked: appSettings.iconFromAccent = checked
			}

			ColumnLayout {
				Layout.fillHeight: false

				RowLayout {
					Layout.fillHeight: false

					Label {
						text: "Background"
						Layout.fillWidth: true
					}

					Rectangle {
						border.width: 1
						border.color: "grey"

						implicitWidth: 40
						implicitHeight: 40
						color: theme.background
					}
				}

				RowLayout {
					Layout.fillHeight: false

					Label {
						text: "Primary"
						Layout.fillWidth: true
					}

					Rectangle {
						border.width: 1
						border.color: "grey"

						implicitWidth: 40
						implicitHeight: 40
						color: theme.primary
					}
				}

				RowLayout {
					Layout.fillHeight: false

					Label {
						text: "Accent"
						Layout.fillWidth: true
					}

					Rectangle {
						border.width: 1
						border.color: "grey"

						implicitWidth: 40
						implicitHeight: 40
						color: theme.accent
					}
				}

				Button {
					flat: true
					text: "Change Theme"
					Layout.fillWidth: true

					onClicked: themeDialog.open()
				}
			}
		}

		Rectangle {
			color: theme.accent
			width: 1
			Layout.fillHeight: true
			Layout.topMargin: 10
			Layout.bottomMargin: 10
		}

		ColumnLayout {
			RowLayout {
				Layout.fillHeight: false

				Label {
					padding: 6
					Layout.fillWidth: true
					text: "Background Opacity"
				}

				Slider {
					Layout.fillWidth: true
					value:appSettings.imageOpacity
					onValueChanged: appSettings.imageOpacity = value
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
					value: appSettings.minViewSize
					onValueChanged: appSettings.minViewSize = value
				}
			}

			Item {
				Layout.fillWidth: true
				Layout.fillHeight: true
			}

			Button {
				flat: true
				text: "Close"
				Layout.fillWidth: true
				onClicked: popup.close()
			}
		}
	}
}
