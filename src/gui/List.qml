import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 640
    height: 480

    ListView {
        anchors.fill: parent
        model: ListModel {
            ListElement { name: "Item 1" }
            ListElement { name: "Item 2" }
            ListElement { name: "Item 3" }
        }

        delegate: Item {
            width: ListView.view.width
            height: 50

            Rectangle {
                width: parent.width
                height: parent.height
                color: "white"
                radius: 5
                border.color: "#cccccc"
                border.width: 1

                Text {
                    anchors.centerIn: parent
                    text: model.name
                    color: "black"
                }

                MouseArea {
                    id: hoverArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor

                    onPressed: {
                        parent.color = "#DDDDDD"
                    }

                    onReleased: {
                        parent.color = "white"
                    }

                    onClicked: {
                        parent.color = "#DDDDDD" // Highlight the item on click
                    }

                    // Hover effect
                    onPositionChanged: {
                        if (hoverArea.containsMouse) {
                            parent.color = "#EEEEEE"
                        } else if (parent.color !== "#DDDDDD") {
                            parent.color = "white"
                        }
                    }
                }
            }
        }
    }
}
