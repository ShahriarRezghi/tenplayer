import QtQuick 2.9
import MyControls 1.0
import QtQuick.Layouts 1.3

import "../Queue"

SwipeView {
	id: swipeView

	MinSubView {
	}

//	QueueView {
//		minView: true
//	}

	QueueListView {
		cellWidth: width
	}
}
