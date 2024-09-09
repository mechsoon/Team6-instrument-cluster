import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: speedometer
    width: 788
    height: 400

    // 배경 이미지 (계기판)
    Image {
        id: background
        source: "image/IC BG Final.png"  // 계기판 배경 이미지 경로
        anchors.fill: parent
    }

    // 바늘 이미지
    Image {
        id: needle
        source: "images/needle nookki.png"  // 바늘 이미지 경로
        width: 20
        height: 200
        anchors.centerIn: parent
        transform: Rotation {
            id: needleRotation
            origin.x: needle.width / 2
            origin.y: needle.height * 0.9  // 바늘의 중심점을 끝으로 설정 (바늘 끝이 회전하도록)
            angle: 0  // 초기 각도 (속도가 0일 때)
        }
    }

    // 속도에 따른 바늘 회전 애니메이션
    NumberAnimation on needleRotation.angle {
        id: rotationAnim
        from: 0
        to: 240  // 바늘이 회전할 각도 범위 (속도에 따라 조정)
        duration: 500
    }

    // 속도값을 전달받을 프로퍼티
    property real currentSpeed: 0

    // 속도 업데이트 함수
    function updateSpeed(newSpeed) {
        // 속도를 각도로 변환 (0 ~ maxSpeed = 0 ~ 240도)
        var maxSpeed = 200  // 계기판에서 표시할 최대 속도
        var minAngle = -120  // 바늘의 최소 각도
        var maxAngle = 120   // 바늘의 최대 각도

        var newAngle = minAngle + (newSpeed / maxSpeed) * (maxAngle - minAngle)
        needleRotation.angle = newAngle  // 바늘 회전 각도 설정
    }
}
