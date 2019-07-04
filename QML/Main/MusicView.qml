import QtQuick 2.10
import QtQuick.Controls 2.3

import "../Artist"
import "../Album"
import "../Song"
import "../Recent"
import "../Playlist"

StackView {
	id: stack
	initialItem: stackIndex == 0 ? currentView():null
//	onCurrentItemChanged: applicationWindow.refresh() TODO uncomment

	property int stackIndex: appSettings.currentLoader
	property int previousIndex

	function currentView() {
		var view

		if (stackIndex == 0)
			view = albumView
		else if (stackIndex == 1)
			view = artistView
		else if (stackIndex == 2)
			view = songView
		else if (stackIndex == 3)
			view = recentView
		else if (stackIndex == 4)
			view = playlistView

		return view
	}

	onStackIndexChanged: {
		var forward = stackIndex > previousIndex
		previousIndex = stackIndex

		if (stackIndex < 0) return

		var view = currentView()
		stack.replace(view, forward ?
						  StackView.PushTransition:StackView.PopTransition)
	}

	Component {
		id: albumView
		AlbumView { }
	}

	Component {
		id: artistView
		ArtistView { }
	}

	Component {
		id: songView
		SongView { }
	}

	Component {
		id: recentView
		RecentView { }
	}

	Component {
		id: playlistView
		PlaylistView { }
	}
}
