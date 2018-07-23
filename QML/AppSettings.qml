import QtQuick 2.10

Item {
	id: item
	property real imageOpacity: .2
	property int minViewSize

	property bool iconFromAccent: false
	property bool colorFromArtwork: true
	property bool backgroundFromArtwork: true

	property string backgroundSource: "qrc:/Images/background.jpg"
}
