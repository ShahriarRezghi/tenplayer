import QtQuick 2.10
import QtQuick.Controls.Material 2.3

Item {
	id: item

	// TODO make delegate scaling work

	property int currentLoader: 0

    property int appWidth: 1000
    property int appHeight: 600

	property int minViewSize: 300
	property real imageOpacity: .2
	property real delegatesScale: 1

	property bool iconFromAccent: false
	property bool colorFromArtwork: true
	property bool backgroundFromArtwork: true

	property string backgroundSource: "qrc:/Images/background.jpg"

	property color accent: consts.primaryColor
	property color primary: Material.color(Material.Teal)
	property color background: consts.primaryColor
}
