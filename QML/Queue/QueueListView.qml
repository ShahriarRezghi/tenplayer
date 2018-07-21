import QtQuick 2.10
import ExtraControls 1.0

GridView {
	id: view
	emptyText: "Nothing Playing!"

	cellWidth: width/2
	cellHeight: 20 + ExtraControls.textSize*3

	model: QueueListViewModel {}
}
