import QtQuick 2.10
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3
import "../STools" as E

E.ImageButton {
	id: control
	padding: 8
	color: appSettings.iconFromAccent ? theme.accent:Material.foreground
}
