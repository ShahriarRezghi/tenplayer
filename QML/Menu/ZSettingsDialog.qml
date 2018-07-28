import QtQuick 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3
import STools.Extras 1.0

Popup {
	id: popup
	modal: true
	topPadding: 8
	bottomPadding: 8
	leftPadding: 24
	rightPadding: 24

	x: (parent.width-width)/2
	y: (parent.height-height)/2

	Material.accent: {
		var p = MaterialTheme.primary
		var pd = MaterialTheme.primaryDark

		var x = (p == theme.accent) || (pd == theme.accent)
		var y = (p == theme.primary) || (pd == theme.primary)

		x ? (y ? "grey":theme.primary):theme.accent
	}

	contentItem: RowLayout {
		spacing: 15

		ColumnLayout {
			ColumnLayout {
				spacing: 15
				Layout.topMargin: 8
				Layout.bottomMargin: 8

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
						color: appSettings.background
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
						color: appSettings.primary
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
						color: appSettings.accent
					}
				}

				Item {
					Layout.fillWidth: true
					Layout.fillHeight: true
				}

				Button {
					text: "Change Theme"
					Layout.fillWidth: true
					Material.background: theme.primary
					implicitWidth: 200

					onClicked: themeDialog.open()
				}
			}
		}

		Rectangle {
			color: popup.Material.accent
			width: 1
			Layout.fillHeight: true
			Layout.topMargin: 10
			Layout.bottomMargin: 10
		}

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
				Layout.alignment: Qt.AlignRight

				onClicked: popup.close()
			}
		}
	}
}
