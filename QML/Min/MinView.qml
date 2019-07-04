import QtQuick 2.9
import "../STools"
import QtQuick.Controls 2.3
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
