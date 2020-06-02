import QtQuick 2.0
import QtQuick.Controls 2.12


Item {
    id: page

    property var firstOperationName: ""
    property var secondOperationName: ""
    property var firstFieldPlaceholder: "Polynom"
    property var secondFieldPlaceholder: "Polynom"
    property var operatorValue: ""
    property bool operatorUse: true
    property bool secondOperationUse: true

    property alias ff: firstField
    property alias sf: secondField
    property alias calculate: calculateButton

    Text {
        id: toolTip
        color: "#0A0908"
        font.pixelSize: 20
        text: qsTr(" Підказка: <u>Заповніть поля для здійснення операції<br>" + operatorValue + "<br>Поліноми вводити у порядку зростання степенів.</u>")
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.margins: 10
    }

    Text {
        id: firstoperation
        color: "#0A0908"
        text: firstOperationName
        anchors.top: toolTip.bottom
        anchors.left: parent.left
        anchors.topMargin: 30
        anchors.leftMargin: 10
        font.pixelSize: 20
    }

    TextField {
        id: firstField
        color: "#0A0908"
        width:  {
            if(firstFieldPlaceholder == "Polynom")
                return 300
            return 50
        }
        placeholderText: firstFieldPlaceholder
        anchors.left: firstoperation.right
        anchors.verticalCenter: firstoperation.verticalCenter
        anchors.leftMargin: {
            if(firstoperation.text == "")
                return 0;
            return 10;
        }
        background: Rectangle{
            color: "#ece9ec"
        }
        font.pixelSize: 20
    }

    Text {
        id: operator
        color: "#0A0908"
        anchors.top: firstoperation.bottom
        anchors.left: parent.left
        anchors.topMargin: 10
        anchors.leftMargin: 30
        visible: operatorUse ? true : false
        text: operatorValue
        font.pixelSize: 30
    }
    Text {
        id: secondoperation
        color: "#0A0908"
        text: secondOperationName
        anchors.top: operatorUse ? operator.bottom : firstoperation.bottom
        visible: secondOperationUse ? true : false
        anchors.left: parent.left
        anchors.topMargin: operatorUse ? 10 : 30
        anchors.leftMargin: 10
        font.pixelSize: 20
    }
    TextField {
        id: secondField
        background: Rectangle{
            color: "#ece9ec"
        }
        color: "#0A0908"
        width:  {
            if(secondFieldPlaceholder == "Polynom")
                return 300
            return 50
        }
        placeholderText: secondFieldPlaceholder
        anchors.verticalCenter: secondoperation.verticalCenter
        anchors.horizontalCenter: {
            if(operatorValue == "gcd")
                return firstField.horizontalCenter
        }

        anchors.left: {
            if(operatorValue == "gcd")
                return undefined
            return secondoperation.right
        }
        visible: secondOperationUse ? true : false
        anchors.leftMargin: {
            if(secondoperation.text == "")
                return 0;
            return 10;
        }
        font.pixelSize: 20
    }
    Text {
        id: resultField
        color: "#0A0908"
        anchors.top: secondOperationUse ? secondoperation.bottom : firstoperation.bottom
        anchors.left: parent.left
        anchors.topMargin: 30
        anchors.leftMargin: 10
        font.pixelSize: 20
        text: "Результат: " + UiController.result
    }
    Button{
        id:calculateButton
        anchors.left: parent.left
        anchors.top: resultField.bottom
        anchors.right: parent.right
        anchors.margins: 10
        text: "<font color='#ffffff'> Розрахувати </font>"
        font.pixelSize: 20
        width: parent.width/2-20
        height: 50
        background: Rectangle{
            color: calculateButton.pressed? "#145499":"#1d68b8"
        }
    }

    function clearAllFields() {
        firstField.text = ""
        secondField.text = ""
        UiController.setResult("")
    }
    function checkFields() {
        if(firstField.text == "" || (secondOperationUse && secondField.text == "")) {
            console.log("Fill all fields!")
            return false
        }
        return true
    }
}
