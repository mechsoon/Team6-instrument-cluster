import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15

ApplicationWindow {
    visible: true
    visibility: Window.FullScreen
    title: "Dial Application"
    color : "black"

    // Dial (Cluster) 설정
    Cluster {
        id: dial
        anchors.centerIn: parent
        value: 0
    }

    // Quit 버튼
    Button {
        text: "Quit"
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 10
        onClicked: Qt.quit()
    }

    // EMA 필터 제어 버튼
    Button {
        id: emaButton
        text: "Toggle EMA Filter"
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.margins: 20

        onClicked: {
            speedController.toggleEmaFilter();  // EMA 필터 켜고 끄기
            emaButton.text = speedController.isEmaFilterActive() ? "Disable EMA Filter" : "Enable EMA Filter";
        }
    }

    // 칼만 필터 제어 버튼
    Button {
        id: kalmanButton
        text: "Toggle Kalman Filter"
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.margins: 20

        onClicked: {
            speedController.toggleKalmanFilter();  // 칼만 필터 켜고 끄기
            kalmanButton.text = speedController.isKalmanFilterActive() ? "Disable Kalman Filter" : "Enable Kalman Filter";
        }
    }
}
