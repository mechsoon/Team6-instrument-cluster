// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick


Item {
    id: root
    property real value : 0

    width: 788; height: 400

    

    Connections {
            target: speedController
            onSpeedChanged: {
                needleRotation.angle=speedController.speed-28;
            }
        }
    Connections {
            target: batterylevel
            onBatteryChanged: {
                console.log("Battery changed to: " + batterylevel.level);
                needleRotation_battery.angle=((batterylevel.level) * (-1.16)) - 32;
                // needleRotation_battery.angle=batterylevel.level
            }
        }


    Image {
        source: "qrc:/framefffinal.png"
        Text {
            id: speedText
            text: speedController.speed + "cm/s"
            anchors.top: parent.bottom
            anchors.topMargin: -50
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 30
            color: "#7C9392" // 글자 색상 설정
        }
        Text {
            id: batteryText
            text: "Battery: " + batterylevel.level + "%"
            anchors.top: speedText.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 30
            color: "#7C9392" // 글자 색상 설정
        }
    }

    Image {
        id: needle
        x: 64; y: 190
        antialiasing: true
        source: "qrc:/needle.png"
        transform: Rotation {
            id: needleRotation
            origin.x: 115; origin.y: 5
            angle: -28
            Behavior on angle {
                // SpringAnimation {
                //     spring: 1.4
                //     damping: .15
                // }
                NumberAnimation {
                    duration: 50
                    easing.type: Easing.InOutQuad
                }
            }
        }
    }

    Image {
        id: needle_battery
        x: 104; y: 250
        antialiasing: true
        source: "qrc:/needle_battery.png"
        transform: Rotation {
            id: needleRotation_battery
            origin.x: 80; origin.y: 3.5
            angle: -32
            Behavior on angle {
                SpringAnimation {
                    spring: 1.4
                    damping: .5
                 }
                NumberAnimation {
                    duration: 100
                    easing.type: Easing.InOutQuad
                }
            }
        
        }
    }
    
    // 배터리 경고가 발생했을 때 이미지와 텍스트를 표시하는 변수
    property bool lowBattery: false

    // 배터리 전압이 낮을 때 호출되는 함수
    function showLowBatteryWarning() {
        lowBattery = true;
    }

    Image {
        id: low_battery1
        visible: lowBattery
        x: 123; y: 200
        antialiasing: true
        source: "qrc:/low_battery.png"
    }

    Text {
        text: "Low_Battery WARNING!!"
        color: "red"
        font.pixelSize: 20
        anchors.horizontalCenter: low_battery1.horizontalCenter  // Image의 가로 중앙에 맞춤
        anchors.top: low_battery1.bottom  // Image의 아래쪽에 배치
        anchors.topMargin: 10  // Image와 Text 사이의 간격을 조정
    }

    Image {
        id: low_battery2
        visible: lowBattery
        x: 1157; y: 200
        antialiasing: true
        source: "qrc:/low_battery.png"
    }

    Text {
        text: "Low_Battery WARNING!!"
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

