// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick


Item {
    id: root
    property real value : 0

    width: 788; height: 400

    
    // onSpeedChanged :{
    //         console.log("Speed changed to:", speedController.speed);
    //         // changeSpeed(speedController.speed);
    //         needleRotation.angle=speedController.speed;
    //     }
    Connections {
            target: speedController  // speedController와 시그널 연결
            onSpeedChanged: {
                console.log("Speed changed to: " + speedController.speed);
                needleRotation.angle=speedController.speed; // 속도에 따라 각도 변경
            }
        }

    // function changeSpeed(newSpeed) {

    //     var maxSpeed = 180

    //     var minAngle = -28
    //     var maxAngle = 208
    //     var newAngle = minAngle + (newSpeed / maxSpeed) * (maxAngle - minAngle)
    //     needleRotation.angle = newAngle
    // }


    Image { source: "qrc:/framefffinal.png" }

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
                SpringAnimation {
                    spring: 1.4
                    damping: .15
                }
                NumberAnimation {
                    duration: 700  // 1초 동안
                    easing.type: Easing.InOutQuad  // 부드러운 애니메이션
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
            angle: Math.max(-148, -32)
            Behavior on angle {
                SpringAnimation {
                    spring: 1.4
                    damping: .15
                }
                NumberAnimation {
                    duration: 700  // 1초 동안
                    easing.type: Easing.InOutQuad  // 부드러운 애니메이션
                }
            }
        
        }
    }



}
