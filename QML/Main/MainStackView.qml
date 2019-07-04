import QtQuick 2.10
import QtQuick.Controls 2.3

import "../Playlist"
import "../Track"
import "../Search"

StackView {
	id: stack
	initialItem: musicView
	//	onCurrentItemChanged: applicationWindow.refresh() TODO uncomment

	property int trackType
	property int stackIndex

	onStackIndexChanged: {
		if (stackIndex == 0)
			stack.pop()
		else if (stackIndex == 1)
			stack.depth != 1 ? stack.replace(trackView):stack.push(trackView)
		else if (stackIndex == 2)
			stack.depth != 1 ? stack.replace(searchView):stack.push(searchView)
		else if (stackIndex == 3)
			stack.depth != 1 ?
						stack.replace(playlistTrackView):stack.push(playlistTrackView)
	}

	Component {
		id: musicView
		MusicView { }
	}

	Component {
		id: trackView
		TrackView { }
	}

	Component {
		id: searchView
		SearchView { }
	}

	Component {
		id: playlistTrackView
		PLaylistTrackView { }
	}
}
