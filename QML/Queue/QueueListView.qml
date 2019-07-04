import QtQuick 2.10
import "../STools"

GridView {
	id: view
	emptyText: "Nothing Playing!"

	cellWidth: width/2
	cellHeight: 20 + consts.textSize*3

	model: QueueListViewModel {}
}
