import QtQuick
import QtQuick.Window
import QtQuick.Controls

Loader {
    id: loader
    sourceComponent: splash
    active: true
    visible: true
    onStatusChanged: {
        if (loader.status === Loader.Ready) {
            item.show();
        }
    }
    signal qmlSignal

    Component {
        id: splash
        Window {
            id: splashWindow
            width: 300
            height: 200
            modality: Qt.ApplicationModal
            flags: Qt.SplashScreen
            color: "#DEDEDE"

            ProgressBar {
                id: progress
                anchors {
                    left: parent.left
                    right: parent.right
                    bottom: parent.bottom
                }
                value: 0
                to : 100
                from : 0
            }

            Text {
                anchors.centerIn: parent
                text: "Loading, please wait ..."
            }

            Timer {
                id: timer
                interval: 10
                running: true
                repeat: true
                onTriggered: {
                    progress.value++;
                    if (progress.value >= 100) {
                        timer.stop();
                        loader.sourceComponent = undefined;
                        loader.qmlSignal()
                    }
                }
            }
        }
    }
}