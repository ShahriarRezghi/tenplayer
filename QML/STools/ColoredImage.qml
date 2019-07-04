import QtQuick 2.7
import QtGraphicalEffects 1.0

Item {
	id: item
	implicitWidth: image.implicitWidth
	implicitHeight: image.implicitHeight

	property color color
	property bool colorized: false

	property alias image: image
	property alias colorize: colorize

	property alias source: image.source

	property real padding: 0
	property alias sourceSize: image.sourceSize

	Image {
		id: image
		visible: !colorized
		anchors.fill: parent
		anchors.margins: item.padding
	}

	Colorize {
		id: colorize
		source: image
		visible: colorized
		anchors.fill: image

		hue: ColorAlt.hue(item.color)
		saturation: ColorAlt.saturation(item.color)
		lightness: ColorAlt.lightness(item.color)*2-1
	}
}
