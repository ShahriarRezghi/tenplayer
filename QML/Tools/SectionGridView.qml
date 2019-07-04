import QtQuick 2.10
import QtQuick.Controls.Material 2.0

import "../STools" as M

M.SectionGridView {
	sectionBackgroundColor: theme.primary
	emptyText: "Nothing Here!"
	property int sectionTextIndex: 0
	onUpdateSectionText: sectionText = item ? item.model[sectionTextIndex][0]:""
}
