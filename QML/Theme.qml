import QtQuick 2.10

Item {
	property color accent
	property color primary
	property color foreground
	property color background

	Behavior on accent { ColorAnimation { duration: 100 } }
	Behavior on primary { ColorAnimation { duration: 100 } }
	Behavior on background { ColorAnimation { duration: 100 } }
	Behavior on foreground { ColorAnimation { duration: 100 } }
}
