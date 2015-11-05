import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.2
import AdbProcess 1.0
import QtQuick.Dialogs 1.2
import Qt.labs.settings 1.0

Window {
    id: window1
    visible: true
    width: 360
    height: 700

    function passAdbPathToCpp(adbPath){
        adbProcess.setAdbPath(adbPath.substring(7))
    }

    Component.onCompleted: {
        txtAdbPath.text = settings.adbPath
        passAdbPathToCpp(settings.adbPath)
    }

    ColumnLayout {
        id: columnLayout1
        anchors.fill: parent

        RowLayout {
            id: rowLayout1
            spacing: 5
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0

            Button {
                id: btnStartCap
                text: qsTr("开始监视")
                onClicked: adbProcess.startSnapAndPull()
            }

            Button {
                id: btnStopCap
                text: qsTr("停止监视")
                onClicked: adbProcess.stop()
            }

            TextField {
                id: txtAdbPath
                height: 20
                font.pointSize: 12
                anchors.left: btnStopCap.right
                anchors.leftMargin: 5
                anchors.right: btnBrowseForAdb.left
                anchors.rightMargin: 5
            }

            Button {
                id: btnBrowseForAdb
                text: qsTr("浏览")
                anchors.right: parent.right
                anchors.rightMargin: 0
                onClicked: {
                    fdAdbPath.folder = txtAdbPath.text
                    fdAdbPath.open()
                }
            }
        }

        Image {
            id: imgDeviceScreen
            cache: false
            fillMode: Image.PreserveAspectFit
            anchors.top: rowLayout1.bottom
            anchors.topMargin: 0
            anchors.bottom: txtStatus.top
            anchors.bottomMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
        }

        Text {
            id: txtStatus
            text: qsTr("")
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            font.pixelSize: 12
        }

    }


    AdbProcess{
        id: adbProcess
        onSnap:{
            imgDeviceScreen.source = "file://"+path
        }

        onShowAlert:{
            messageBox.text = msg
            messageBox.open()
        }

        onShowStatusMsg:{
            txtStatus.text = msg
        }
    }

    MessageDialog{
        id: messageBox
    }

    Settings{
        id: settings
        property string adbPath: "/path/to/your/adb"
    }

    FileDialog{
        id: fdAdbPath
        title: "浏览adb文件"
        onAccepted: {
            settings.adbPath = fdAdbPath.fileUrl
            txtAdbPath.text = fdAdbPath.fileUrl
            passAdbPathToCpp(fdAdbPath.fileUrl)
        }
    }
}
