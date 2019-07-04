import QtQuick 2.10

QtObject {
	id: root

	property color primaryColor: "#e5e5e5"
	property color primaryDarkColor: "#303030"

	property Text text: Text { text: "Hi" }
	property real textSize: text.height

	property real smallFont: text.font.pointSize
	property real mediumFont: text.font.pointSize + 2
	property real largeFont: text.font.pointSize + 4

	property int albumLoader: 0
	property int artistLoader: 1
	property int songLoader: 2
	property int queueLoader: 3
	property int recentlyAddedLoader: 4
	property int recentlyPlayedLoader: 5
	property int playlistLoader: 6
}
