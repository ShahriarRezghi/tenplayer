import QtQuick 2.10
import "../Tools"
import ".."

VisualDataModel {
	id: root
	model: TrackModel

	signal menuRequested(real x, real y, int index)

	delegate: Item {
		id: item
		height: del.height
		width: cellWidth
		property int itemRow: rowRole

		function setRowRole(row) { rowRole = row }

		DropArea {
			anchors.fill: parent

			onEntered: {
				var temp = drag.source.itemRow
				drag.source.setRowRole(rowRole)
				rowRole = temp

				var ind1 = item.VisualDataModel.itemsIndex;
				var ind2 = drag.source.VisualDataModel.itemsIndex;

				if (ind1 == ind2)
					return;

				root.items.move(ind2, ind1)
			}
		}

		MouseArea {
			id: ma
			drag.axis: Drag.YAxis
			drag.target: pressed ? del : undefined

			x: item.width-width
			height: item.height
			width: height
			anchors.verticalCenter: del.verticalCenter

			states: State {
				when: ma.pressed
				ParentChange { target: ma; parent: del  }
			}

			ImageButton {
				enabled: false
				anchors.centerIn: parent
				source: "qrc:/Images/Menu.png"
			}
		}

		ListDelegate {
			id: del
			width: item.width-ma.width
			anchors.verticalCenter: ma.pressed ? undefined:parent.verticalCenter

			states: State {
				when: ma.pressed
				ParentChange { target: del; parent: pitem }
			}

			Drag.active: ma.pressed
			Drag.source: item
			Drag.hotSpot.x: width / 2
			Drag.hotSpot.y: height / 2

			image: artworkRole ? "file://"+artworkRole:"qrc:/Images/Note.png"

			useTrack: trackRole != 0
			track: trackRole != 0 ? trackRole:""
			model: [titleRole, albumRole, artistRole]

			onClicked: {
				MainManager.sortTracksByRow()
				MainManager.trackClicked(index)
			}

			onMenuRequested: root.menuRequested(xx+x, yy+y, index)
		}
	}
}
