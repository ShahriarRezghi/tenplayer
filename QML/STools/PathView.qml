import QtQuick 2.10
import QtQuick 2.10 as Q
import QtQuick.Controls 2.3

Q.PathView{
    id: root
    clip: true
    activeFocusOnTab: true
	preferredHighlightEnd: .5
    preferredHighlightBegin: .5

	pathItemCount: 15
	snapMode: PathView.SnapToItem

	property bool busy: false
    property alias emptyText: label.text

    states: [
		State {
            name: "busy"; when: root.busy
			PropertyChanges { target: root; model: undefined }
        }
    ]

	BusyIndicator{
		z: 1000
        running: busy
        anchors.centerIn: parent
    }

	Label {
		id: label
		z: 999
		padding: 10
		text: emptyText
		visible: root.count == 0 && !busy && text

		width: parent.width
		anchors.centerIn: parent

		horizontalAlignment: Text.AlignHCenter
		wrapMode: Text.WrapAtWordBoundaryOrAnywhere
	}

	path: Path{
        startX: 0; startY: root.height/2

		PathAttribute { name: "iconScale"; value: 0.5 }
		PathAttribute { name: "iconOpacity"; value: 0.5 }
		PathAttribute {name: "iconZ"; value: 0}
		PathAttribute {name: "iconRotation"; value: 75}
//        PathQuad {x: gridView.width/2; y: gridView.height*2/3; controlX: gridView.width/4; controlY: gridView.height*2/3}
		PathLine {x: root.width/2; y: root.height/2}
		PathAttribute { name: "iconScale"; value: 1 }
		PathAttribute { name: "iconOpacity"; value: 1 }
		PathAttribute {name: "iconZ"; value: 100}
		PathAttribute {name: "iconRotation"; value: 0}
//        PathQuad {x: gridView.width; y: gridView.height/3; controlX: gridView.width*3/4; controlY: gridView.height*2/3}
		PathLine {x: root.width; y: root.height/2}
		PathAttribute { name: "iconScale"; value: 0.5 }
		PathAttribute { name: "iconOpacity"; value: 0.5 }
		PathAttribute {name: "iconZ"; value: 0}
		PathAttribute {name: "iconRotation"; value: -75}
    }

    //    Canvas {
    //        anchors.fill: parent
    //        contextType: "2d"
    //        antialiasing: true
    //        smooth: true
    //        z: 101

    //            onPaint: {
    //                context.strokeStyle = Qt.rgba(.4,.6,.8);
    //                context.path = myPath;
    //                context.stroke();
    //            }
    //    }
}
