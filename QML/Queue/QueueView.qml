import QtQuick 2.10
import "../STools"

PathView {
	id: view
	emptyText: "Nothing Playing!"
	pathItemCount: 7
	currentIndex: ActiveInfo.queueRow
	onCurrentIndexChanged: if (flicking)
							   MainManager.loaderClicked(consts.queueLoader, currentIndex)

	property bool minView: false

	path: Path {
		id: path
		startX:0 ; startY: view.height/2

		PathAttribute { name: "iconScale"; value: 0.7 }
		PathAttribute {name: "iconZ"; value: 0}
		PathAttribute {name: "iconRotation"; value: 0}

		PathLine {x: view.width/2-view.width/15; y: view.height/2}

		PathAttribute { name: "iconScale"; value: 0.7 }
		PathAttribute {name: "iconZ"; value: 10}
		PathAttribute {name: "iconRotation"; value: 0}

		PathLine {x: view.width/2; y: view.height/2}

		PathAttribute { name: "iconScale"; value: 1 }
		PathAttribute { name: "iconOpacity"; value: 1 }
		PathAttribute {name: "iconZ"; value: 20}
		PathAttribute {name: "iconRotation"; value: 0}

		PathLine {x: view.width/2+view.width/15; y: view.height/2}

		PathAttribute { name: "iconScale"; value: 0.7 }
		PathAttribute {name: "iconZ"; value: 10}
		PathAttribute {name: "iconRotation"; value: 0}

		PathLine {x: view.width; y: view.height/2}

		PathAttribute { name: "iconScale"; value: 0.7 }
		PathAttribute {name: "iconZ"; value: 0}
		PathAttribute {name: "iconRotation"; value: 0}
	}

	model: QueueViewModel { }
}
