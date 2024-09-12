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
                console.log("Speed changed to: " + speedController.speed);
                needleRotation.angle=speedController.speed-28;
            }
        }
    Connections {
            target: batterylevel
            onBatteryChanged: {
                console.log("Battery changed to: " + batterylevel.level);
                needleRotation_battery.angle=((batterylevel.level) * (-1.16)) - 32;
            }
        }


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
                    duration: 100
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
        //     Behavior on angle {
        //         SpringAnimation {
        //             spring: 1.4
        //             damping: .15
        //         }
        //         NumberAnimation {
        //             duration: 500
        //             easing.type: Easing.InOutQuad
        //         }
        //     }
        
        }
    }



}

