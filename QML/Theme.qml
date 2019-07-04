import QtQuick 2.10

Item {
	property color accentAlt: theme.accent == theme.background ? theme.primary:theme.accent

	property color accent
	property color primary
	property color background
	property color foreground

	Behavior on accent { ColorAnimation { duration: 100 } }
	Behavior on primary { ColorAnimation { duration: 100 } }
	Behavior on foreground { ColorAnimation { duration: 100 } }
	Behavior on background { ColorAnimation { duration: 100 } }
}
