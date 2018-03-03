import QtQuick 2.10
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3

RowLayout {
	spacing: 0

	RecentlyAddedView {
		Layout.fillWidth: true
		Layout.fillHeight: true
	}

	Rectangle {
		width: 1
		Layout.fillHeight: true
		color: Material.accent
	}

	RecentlyPlayedView {
		Layout.fillWidth: true
		Layout.fillHeight: true
	}
}
