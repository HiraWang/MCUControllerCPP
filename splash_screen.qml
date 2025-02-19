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
    signal qmlLoaderFinish

    Component {
        id: splash
        Window {
            id: splashWindow
            width: 350
            height: 300
            modality: Qt.ApplicationModal
            flags: Qt.SplashScreen
            color: "transparent"

            Rectangle {
                width: parent.width
                height: parent.height
                radius: 10
                color: "white"
            }

            Image {
                id: image
                source: "qrc:/images/METIcon.jpg"
                width: 300
                height: 107
                anchors.centerIn: parent
            }

            Text {
                anchors.horizontalCenter: image.horizontalCenter
                anchors.top: image.bottom
                text: ""
                color: "#606060"
                fontSizeMode: Text.Fit
                font.pixelSize: 12
            }

            ProgressBar {
                id: progress
                value: 0.5
                from: 0
                to : 100
                padding: 1

                anchors {
                    left: parent.left
                    right: parent.right
                    bottom: parent.bottom
                }
            
                background: Rectangle {
                    implicitWidth: 200
                    implicitHeight: 15
                    color: "#e6e6e6"
                    radius: 5
                }
            
                contentItem: Item {
                    implicitWidth: 200
                    implicitHeight: 4
            
                    // Progress indicator for determinate state.
                    Rectangle {
                        width: progress.visualPosition * parent.width
                        height: parent.height
                        radius: 5
                        color: "#17a81a"
                        visible: !progress.indeterminate
                    }
            
                    // Scrolling animation for indeterminate state.
                    Item {
                        anchors.fill: parent
                        visible: progress.indeterminate
                        clip: true
            
                        Row {
                            spacing: 20
            
                            Repeater {
                                model: progress.width / 40 + 1
            
                                Rectangle {
                                    color: "#17a81a"
                                    width: 20
                                    height: progress.height
                                }
                            }
                            XAnimator on x {
                                from: 0
                                to: -40
                                loops: Animation.Infinite
                                running: progress.indeterminate
                            }
                        }
                    }
                }
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
                        loader.qmlLoaderFinish()
                    }
                }
            }
        }
    }
}