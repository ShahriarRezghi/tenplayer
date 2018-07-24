import QtQuick 2.10
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3

import "../Tools"

Page {
	id: page

	BackgroundImage {
		anchors.fill: parent
		parent: page.background
		source: backgroundImage.source
		opacity: appSettings.imageOpacity

	}

	contentItem: StackView {
		id: stack
		initialItem: pathView
		onCurrentItemChanged: applicationWindow.refresh()

		Component {
			id: pathView
			QueueView { }
		}

		Component {
			id: listView
			QueueListView { }
		}
	}

	footer: TabBar {
		id: tabbar
		position: TabBar.Footer
		Material.background: theme.primary

		Rectangle {
			height: 1
			opacity: .5
			width: parent.width
			color: theme.accent
			parent: tabbar.background
			anchors.bottom: parent.top
		}

		onCurrentIndexChanged: {
			stack.replace(currentIndex == 0 ? pathView:listView)
		}

		TabButton { text: "Path View" }
		TabButton { text: "List View" }
	}
}
