import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3

import "../Tools"

Control {
	property int itemIndex

	contentItem: RowLayout {
		spacing: 0

		ImageButton {
			rotation: 90
			Layout.alignment: Qt.AlignVCenter
			onClicked: bottomBarStack.stackIndex = itemIndex
			source: "qrc:/Images/change.png"
		}

		ImageButton {
			rotation: barDown ? 180:0
			Layout.alignment: Qt.AlignVCenter
			source: "qrc:/Images/Expand.png"
			property bool barDown: appBottomBar.state == "down"

			onClicked: {
				if (barDown) appBottomBar.state = "up"
				else appBottomBar.state = "down"
			}
		}
	}
}
