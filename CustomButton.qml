import QtQuick

Rectangle {
    property alias txt: txt
    signal buttonClicked()

    width: txt.width
    height: txt.height
    anchors.margins: 8
    radius: 5
    border.width: 2
    border.color: activeFocus ? Qt.darker(color, 1.5) : "transparent"

    Keys.onSpacePressed: buttonClicked()
    Keys.onReturnPressed: buttonClicked()

    Text {
        id: txt
    }

    MouseArea {
        anchors.fill: parent
        onClicked: buttonClicked()
    }

}
