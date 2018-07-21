import QtQuick 2.10
import Qt.labs.settings 1.0 as S

S.Settings {
	property real imageOpacity: .2
	property int minViewSize

	property bool iconFromAccent: false
	property bool colorFromArtwork: true
	property bool backgroundFromArtwork: true

	property string backgroundSource: "qrc:/Images/background.jpg"
}
