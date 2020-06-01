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
    property bool polExpected: true

    signal calculateButtonClicked()
    signal saveButtonClicked()
    signal changeOperationButtonClicked()

    Text {
        id: toolTip
        font.pixelSize: 20
        text: qsTr(" <u>Підказка: Заповніть поля для здійснення операції " + operatorValue + "</u>")
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.margins: 10
    }

    Text {
        id: firstoperation
        text: firstOperationName
        anchors.top: toolTip.bottom
        anchors.left: parent.left
        anchors.topMargin: 30
        anchors.leftMargin: 10
        font.pixelSize: 20
    }

    TextField {
        id: firstField
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
        font.pixelSize: 20
    }

    Text {
        id: operator
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
        anchors.top: secondOperationUse ? secondoperation.bottom : firstoperation.bottom
        anchors.left: parent.left
        anchors.topMargin: 30
        anchors.leftMargin: 10
        font.pixelSize: 20
        text: "Result: " + UiController.result
    }
    Button{
        id:calculateButton
        anchors.left: parent.left
        anchors.top: resultField.bottom
        anchors.right: polExpected ? undefined : parent.right
        anchors.margins: 10
        text: "Calculate"
        font.pixelSize: 20
        width: parent.width/2-20
        height: 50
        onClicked: {
            if(firstField.text == "" || (secondOperationUse && secondField.text == "")) {
                console.log("Fill all fields")
                return
            }
            calculateButtonClicked()
        }
    }
    Button{
        id:saveButton
        anchors.right: parent.right
        anchors.top: resultField.bottom
        visible: polExpected ? true : false
        anchors.margins: 10
        text: "Save Result"
        font.pixelSize: 20
        width: parent.width/2-20
        height: 50
        onClicked:
        {
            if(UiController.result === "") {
                console.log("No RESULT, pls PRESS CALCULATE")
                return
            }
            saveButtonClicked()
        }

    }
    Button{
        // New Operation with current POLYNOMIAL BUTTON
        id:changeOperation
        anchors.top: calculateButton.bottom
        anchors.margins: 10
        anchors.left: parent.left
        anchors.right: parent.right
        text: "Вибрати іншу операцію та продовжити"
        font.pixelSize: 20
        height: 50
        onClicked: {
            changeInputParamsButton.enabled=true;
            changeOperationButtonClicked()
        }
    }
}
