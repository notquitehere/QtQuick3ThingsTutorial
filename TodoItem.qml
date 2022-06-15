import QtQuick
import QtQuick.Layouts

FocusScope {
    property alias itemWidth: toDoItemContainer.width
    width: toDoItemContainer.width
    height: toDoItemContainer.height
    x: toDoItemContainer.x
    y: toDoItemContainer.y
    onActiveFocusChanged: {
        if (activeFocus) {
            toDoView.currentIndex = index
        } else {
            editItemText.focus = true
        }
    }
    activeFocusOnTab: true
    Keys.onEscapePressed: {
        toDoView.currentIndex = -1
        focus = false
    }

    Rectangle {
        id: toDoItemContainer
        height: todoItem.implicitHeight + 12
        anchors.horizontalCenter: parent.horizontalCenter
        radius: 10
        border.color: "#777479"
        color: "transparent"

        component UpdateButton: CustomButton {
            txt.leftPadding: 7.5
            txt.rightPadding: 7.5
            txt.font.pointSize: 24
        }

        RowLayout {
            id: todoItem
            spacing: 8
            anchors.fill: parent
            anchors.margins: 6

            TextInput {
                id: editItemText
                text: item
                Layout.margins: 8
                Layout.fillWidth: true
                font.strikeout: completed

                onEditingFinished: {
                    item= text
                    focus = false
                }

                focus: true
                KeyNavigation.right:  setToday
            }

            UpdateButton {
                id: setToday
                color: "#aaff9400"
                txt.text: today ? "\u2212" : "\u002B"
                visible: root.state === "" ? false : true

                onButtonClicked: today = !today

                KeyNavigation.right: itemCompleted
            }

            UpdateButton {
                id: itemCompleted
                color: "#0ab74f"
                txt.text: "\u2714"

                onButtonClicked: completed = !completed
                KeyNavigation.right: removeItem

            }

            UpdateButton {
                id: removeItem
                color: "#b7190a"
                txt.text: "\u2718"

                onButtonClicked: remove = true
            }

        }

    }
}

