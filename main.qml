import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import NfcCpp 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    NfcManagerWrapper {
        id: nfc_manager
        onTargetDetected: {
            btn_read.enabled = true
            btn_write.enabled = true
        }
        onTargetLost: {
            btn_read.enabled = false
            btn_write.enabled = false
        }
        onDataReaded: {
            te_read_data.text = data
        }
    }

    Column {
        anchors.centerIn: parent
        width: parent.width * 0.9
        spacing: 20

        Row {
            Button {
                id: btn_read
                text: 'Read'
                enabled: false
                onClicked: {
                    nfc_manager.read16BytesFromBlock(Number(te_read_block_id.text))
                }
            }
            Text {
                text: ' 16 bytes from: '
                anchors.verticalCenter: parent.verticalCenter
            }
            TextField {
                id: te_read_block_id
                text: '4'
                anchors.verticalCenter: parent.verticalCenter
                color: 'blue'
                font.bold: true
                width: 30
            }
        }
        TextField {
            id: te_read_data
            width: parent.width
            readOnly: true
            text: 'No data to read'
        }
        Row {
            Button {
                id: btn_write
                text: 'Write'
                enabled: false
                onClicked: {
                    nfc_manager.write4BytesToBlock(Number(te_write_block_id.text), te_write_data.text)
                }
            }
            Text {
                text: ' 4 bytes to: '
                anchors.verticalCenter: parent.verticalCenter
            }
            TextField {
                id: te_write_block_id
                text: '4'
                anchors.verticalCenter: parent.verticalCenter
                color: 'blue'
                font.bold: true
                width: 30
            }
        }
        TextField {
            id: te_write_data
            width: parent.width
            text: 'No data to write'
        }
        Button {
            text: 'Copy read data to write text field'
            onClicked: {
                te_write_data.text = te_read_data.text
            }
        }
    }

    Text {
        text: '1. Кнопки для чтения и записи\nактивны при обнаружении метки\n'
                + '2. Из поля ввода данных для записи\nберутся только первые 8 знаков (4 байта)'
    }
}
