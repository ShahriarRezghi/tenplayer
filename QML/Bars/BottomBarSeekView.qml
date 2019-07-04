import QtQuick 2.0
import QtQuick 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3

RowLayout {
	id: rowLayout

	TrackInfoView {
		Layout.minimumWidth: rowLayout.width/3
		Layout.maximumWidth: rowLayout.width/3
	}

	MainSliderView {
		Layout.fillWidth: true
	}

	BottomBarController {
		rightPadding: 12
		itemIndex: 0
		Layout.alignment: Qt.AlignVCenter
	}
}
