import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    id: window
    visible: true
    width: 500
    height: 200
    color: "#c8d6e5"
    property alias output1: output1
    property alias input1: input1
    property alias input1Text: input1.text
    property alias rowWidth: all_rows.width
    title: qsTr("CalcPlusPlus")

    Row {
        id: all_rows
        anchors.rightMargin: 5
        anchors.leftMargin: 5
        anchors.bottomMargin: 5
        anchors.topMargin: 5
        anchors.fill: parent

        Row {
            id: row1
            height: input1.paintedHeight + output1.paintedHeight + 2
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.leftMargin: 0





            TextEdit {
                id: input1
                y: row1.y
                height: 20
                layer.effect: output1
                selectByMouse: false
                cursorVisible: true
                textFormat: Text.AutoText
                font.pointSize: 14
                font.family: "Courier"
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.right: parent.right
            }

            Text {
                id: output1
                y: input1.paintedHeight + 5
                text: "#input1.text#"
                font.pointSize: 14
                font.family: "Courier"
                anchors.right: parent.right
                anchors.left: parent.left
                anchors.leftMargin: 0
            }
        }
    }

    Connections {
        target: input1
        onKe: print("clicked")
    }
}

/*##^##
Designer {
    D{i:3;anchors_width:80;anchors_x:0}D{i:2;anchors_width:200}D{i:1;anchors_height:0;anchors_width:0;anchors_x:0;anchors_y:0}
}
##^##*/
