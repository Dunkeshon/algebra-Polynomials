import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12


Item {
    // property var currentPolynomial: "x^3-7"
    // property var secondPolinomial: "x^193+x^15+1"
    property alias workView: swipeView
    id: info
    visible: false
    Text {
        id: choosenPolynom
        font.pixelSize: 20
        text: qsTr("Вибраний многочлен : " + UiController.mainPolynomialString )
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.margins: 10
    }

    SwipeView{
        id: swipeView
        interactive: false
        currentIndex: 0
        clip: true
        anchors.left: parent.left
        anchors.top: choosenPolynom.bottom
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        Item{
            id:blankItem
            visible: swipeView.currentIndex==0?true:false
            Text {
                id: toolTip
                font.pixelSize: 20
                text: qsTr(" <u>Підказка: Виберіть операцію </u>")
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.margins: 10
            }
        }
        SwipeViewItem {
            id: plus
            visible: swipeView.currentIndex==1?true:false
            operatorValue: "+"
        }
        SwipeViewItem {
            id: minus
            visible: swipeView.currentIndex==2?true:false
            operatorValue: "-"
        }
        SwipeViewItem {
            id: multiplicate
            visible: swipeView.currentIndex==3?true:false
            operatorValue: "*"
        }
        SwipeViewItem {
            id: difference
            visible: swipeView.currentIndex==4?true:false
            operatorValue: "/"
        }
        SwipeViewItem {
            id: mod
            visible: swipeView.currentIndex==5?true:false
            operatorValue: "%"
        }
        SwipeViewItem {
            id: derivative
            visible: swipeView.currentIndex==6?true:false
            operatorValue: "derivative"
            operatorUse: false
            secondOperationUse: false
            firstOperationName: "DERIVATIVE"
        }
        SwipeViewItem {
            id: makemonic
            visible: swipeView.currentIndex==7?true:false
            operatorValue: "make monic"
            operatorUse: false
            secondOperationUse: false
            firstOperationName: "MAKEMONIC"
        }
        SwipeViewItem {
            id: evaluate
            visible: swipeView.currentIndex==8?true:false
            operatorValue: "evaluate"
            operatorUse: false

            secondOperationName: "EVALUATE"
            secondFieldPlaceholder: "Int"
            polExpected: false
        }
        SwipeViewItem {
            id: rootsNum
            visible: swipeView.currentIndex==9?true:false
            operatorValue: "Roots Num"
            operatorUse: false
            secondOperationUse: false
            firstOperationName: "ROOTSNUM"
            polExpected: false
        }
        SwipeViewItem {
            id: inverse
            visible: swipeView.currentIndex==10?true:false
            operatorValue: "Inverse"
            operatorUse: false
            secondOperationUse: false
            firstOperationName: "INVERSE"
        }
        SwipeViewItem {
            id: gcd
            visible: swipeView.currentIndex==11?true:false
            operatorValue: "gcd"
            operatorUse: false
            firstOperationName: "GCD"
        }
        SwipeViewItem {
            id: buildCircuarPolynom
            visible: swipeView.currentIndex==12?true:false
            operatorValue: "build<br>circular polynom"
            operatorUse: false
            secondOperationUse: false
            firstOperationName: "BUILD_CIRCULAR_POLYNOM"
            firstFieldPlaceholder: "Int"
        }
        SwipeViewItem {
            id: isIrreducible
            visible: swipeView.currentIndex==13?true:false
            operatorValue: "check<br>irreducible"
            operatorUse: false
            secondOperationUse: false
            firstOperationName: "CHECK_IRREDUCIBLE"
            polExpected: false
        }
        SwipeViewItem {
            id: irrPolynomOrder
            visible: swipeView.currentIndex==14?true:false
            operatorValue: "calculate<br>order of irreducible poolynom"
            operatorUse: false
            secondOperationUse: false
            firstOperationName: "IRR_POLYNOM_ORDER"
            polExpected: false
        }
        SwipeViewItem {
            id: redPolynomOrder
            visible: swipeView.currentIndex==15?true:false
            operatorValue: "calculate<br>order of reducible poolynom"
            operatorUse: false
            secondOperationUse: false
            firstOperationName: "RED_POLYNOM_ORDER"
            polExpected: false
        }
    }


}
