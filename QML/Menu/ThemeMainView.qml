import QtQuick 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3

ColumnLayout {
	id: column

	signal clicked(color c)

	property var model
	property string topText

	Label {
        id: label
		padding: 8
		text: topText
		elide: Text.ElideRight

		Layout.fillWidth: true
		verticalAlignment: Text.AlignVCenter
		horizontalAlignment: Text.AlignHCenter

    }

    Rectangle {
        opacity: .5
        height: 1
        Layout.fillWidth: true
        Layout.leftMargin: 10
        Layout.rightMargin: 10
        color: theme.accentAlt
    }

	Flickable {
		clip: true
		Layout.fillWidth: true
		Layout.fillHeight: true

		contentWidth: width
		contentHeight: grid.height

		ScrollBar.vertical: ScrollBar { }

		Grid {
			id: grid
			columns: width/48
			width: parent.width

			Repeater {
				model: column.model

				delegate: AbstractButton {
					padding: 5
					implicitWidth: 54
					implicitHeight: 54

					contentItem: Rectangle {
						color: modelData
						border.width: 1
						border.color: "grey"
					}

                    onClicked: label.parent.clicked(modelData)
				}
			}
		}
	}
}
