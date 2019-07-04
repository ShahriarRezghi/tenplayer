import QtQuick 2.10
import QtGraphicalEffects 1.0

Item {
	id: item

	property string source
	property alias image: img

	Image {
		id: img
		source: item.source
		anchors.fill: parent
//		sourceSize.width: width
//		sourceSize.height: height
		fillMode: Image.PreserveAspectCrop

		width: parent.width
		height: parent.height

//		visible: false
	}

//	GaussianBlur {
//		anchors.fill: parent
//		source: img
//		radius: 8
//		samples: 16
//	}
}
