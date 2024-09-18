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
}
