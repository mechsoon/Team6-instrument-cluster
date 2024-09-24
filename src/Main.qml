import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15

ApplicationWindow {
    visible: true
    //width: 1280
    //height: 400
    visibility: Window.FullScreen
    title: "Dial Application"
    color : "black"

    // Rectangle {
    //     color: "#545454"
    //     anchors.fill: parent

        //! [the dial in use]
        // Dial with a slider to adjust it
    Cluster {
        id: dial
        anchors.centerIn: parent
        value: 0

        //! [the dial in use]

        // QuitButton
        Button {
            text: "Quit"
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.margins: 10
            onClicked: Qt.quit()
        }
    }

    Image {
        id: low_battery1
        visible: (batterylevel.level)<=10?true:false
        anchors.left: parent.left
        antialiasing: true
        anchors.leftMargin: 250
        anchors.top: parent.top
        anchors.topMargin: 400
        source: "qrc:/low_battery.png"

    }

    Text {
        text: "Low_Battery WARNING!!"
        visible: (batterylevel.level)<=10?true:false
        color: "red"
        font.pixelSize: 20
        anchors.horizontalCenter: low_battery1.horizontalCenter  // Image의 가로 중앙에 맞춤
        anchors.top: low_battery1.bottom  // Image의 아래쪽에 배치
        anchors.topMargin: 10  // Image와 Text 사이의 간격을 조정
    }

    Image {
        id: low_battery2
        visible: (batterylevel.level)<=10?true:false
        anchors.right: parent.right
        antialiasing: true
        anchors.rightMargin: 250
        anchors.top: parent.top
        anchors.topMargin: 400
        source: "qrc:/low_battery.png"
    }

    Text {
        text: "Low_Battery WARNING!!"
        visible: (batterylevel.level)<=10?true:false
        color: "red"
        font.pixelSize: 20
        anchors.horizontalCenter: low_battery2.horizontalCenter  // Image의 가로 중앙에 맞춤
        anchors.top: low_battery2.bottom  // Image의 아래쪽에 배치
        anchors.topMargin: 10  // Image와 Text 사이의 간격을 조정
    }

    Connections {
        target: batterylevel  // C++ 객체를 QML로 전달받는 객체
        onLowBatteryWarning: {
            showLowBatteryWarning()
        }
    }
}
