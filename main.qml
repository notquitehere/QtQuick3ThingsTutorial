import QtQuick
import QtQuick.Layouts
import Qt.labs.platform

Window {
    width: 640
    height: 600
    visible: true
    title: qsTr("Three Things")
    color: "#fafafa"

    MenuBar {
        Menu {
            id: fileMenu
            title: qsTr("&File")
            MenuItem {
                text: qsTr("&New...")
                shortcut: "+"
                onTriggered: dataModel.sourceModel.add();
            }

        }
    }

    Shortcut {
        sequence: "Alt+A"
        onActivated: {
            if (root.state === "") {
                root.state = "viewAll"
                dataModel.setShowTodayOnly(false)
            } else {
                root.state = ""
                dataModel.setShowTodayOnly(true)
            }
        }
    }

    ColumnLayout {
        id: root
        anchors.fill: parent
        anchors.topMargin: 16
        anchors.bottomMargin: 24
        anchors.leftMargin: 8
        anchors.rightMargin: 8
        spacing: 8

        Item {
            id: titleArea
            Layout.fillWidth: true
            Layout.minimumWidth: titleText.width
            Layout.alignment: Qt.AlignTop
            Layout.preferredHeight: titleText.height

            Text {
                id: titleText
                anchors.centerIn: parent
                text: "To Do Today"
                font.family: "Raleway"
                font.pointSize: 50
            }
        }

        ListView {
            id: toDoView
            Layout.fillHeight: true
            Layout.fillWidth: true
            model: dataModel
            keyNavigationWraps: true
            highlight: Rectangle { color: "#e0e0e0"
                                   radius: 10 }
            delegate: TodoItem {
                            itemWidth: toDoView.width
                       }

            spacing: 8
            clip: true

            Component.onCompleted: currentIndex = -1
        }


        Item {
            id: buttonArea
            Layout.fillWidth: true
            Layout.preferredHeight: changeView.height

            CustomButton {
                id: changeView
                anchors.centerIn: parent
                color: "#aa5c2b80"
                txt.text: qsTr("See all")
                txt.color: "#fafafa"
                txt.padding: 16

                onButtonClicked: {
                    if (root.state === "") {
                        root.state = "viewAll"
                        dataModel.setShowTodayOnly(false)
                    } else {
                        root.state = ""
                        dataModel.setShowTodayOnly(true)
                    }

                }
            }
       }

        states: [
            State {
                name: "viewAll"
                PropertyChanges {
                    target: titleText
                    text: "All the To Do Items"
                }

                PropertyChanges {
                    target: changeView
                    txt.text: "See Today"
                }
            }
        ]

    }
}
