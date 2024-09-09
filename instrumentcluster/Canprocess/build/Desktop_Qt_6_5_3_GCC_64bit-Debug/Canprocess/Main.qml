import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15

ApplicationWindow {
    visible: true
    width: 788
    height: 400
    title: "Dial Application"

    Rectangle {
        color: "#545454"
        anchors.fill: parent

        //! [the dial in use]
        // Dial with a slider to adjust it
        Cluster {
            id: dial
            anchors.centerIn: parent
            value: slider.x * 100 / (container.width - 32)
        }
        //! [the dial in use]

        // QuitButton
        // Button {
        //     text: "Quit"
        //     anchors.right: parent.right
        //     anchors.top: parent.top
        //     anchors.margins: 10
        //     onClicked: Qt.quit()
        // }
    }
}
