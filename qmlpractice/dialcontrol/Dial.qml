// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick

Item {
    id: root
    property real value : 0

    width: 788; height: 400

    Image { source: "framefinal.png" }

//! [needle_shadow]
    // Image {
    //     x: 96
    //     y: 35
    //     source: "needle_shadow.png"
    //     transform: Rotation {
    //         origin.x: 9; origin.y: 67
    //         angle: needleRotation.angle
    //     }
    // }
//! [needle_shadow]
//! [needle]
    Image {
        id: needle
        x: 64; y: 190
        antialiasing: true
        source: "needle.png"
        transform: Rotation {
            id: needleRotation
            origin.x: 115; origin.y: 5
            //! [needle angle]
            angle: Math.min(-28, 208)
            Behavior on angle {
                SpringAnimation {
                    spring: 1.4
                    damping: .15
                }
            }
            //! [needle angle]
        }
    }
//! [needle]
//! [overlay]
    Image { x: 21; y: 18; source: "overlay.png" }
//! [overlay]
}
