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
        onCurrentIndexChanged: {
            if(currentIndex == 0)
                return
            swipeView.currentItem.clearAllFields()
        }

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
            calculate.onClicked: {
                if(!checkFields())
                    return
                UiController.inputPolynomials(ff.text, sf.text)
                UiController.plus()
                UiController.updateHistory(ff.text + " + " + sf.text + " = " + UiController.result)
            }
        }
        SwipeViewItem {
            id: minus
            visible: swipeView.currentIndex==2?true:false
            operatorValue: "-"
            calculate.onClicked: {
                if(!checkFields())
                    return
                UiController.inputPolynomials(ff.text, sf.text)
                UiController.minus()
                UiController.updateHistory(ff.text + " - " + sf.text + " = " + UiController.result)
            }
        }
        SwipeViewItem {
            id: multiplicate
            visible: swipeView.currentIndex==3?true:false
            operatorValue: "*"
            calculate.onClicked: {
                if(!checkFields())
                    return
                UiController.inputPolynomials(ff.text, sf.text)
                UiController.mult()
                UiController.updateHistory(ff.text + " * " + sf.text + " = " + UiController.result)
            }
        }
        SwipeViewItem {
            id: difference
            visible: swipeView.currentIndex==4?true:false
            operatorValue: "/"
            calculate.onClicked: {
                if(!checkFields())
                    return
                UiController.inputPolynomials(ff.text, sf.text)
                UiController.division()
                UiController.updateHistory(ff.text + " / " + sf.text + " = " + UiController.result)
            }
        }
        SwipeViewItem {
            id: mod
            visible: swipeView.currentIndex==5?true:false
            operatorValue: "%"
            calculate.onClicked: {
                if(!checkFields())
                    return
                UiController.inputPolynomials(ff.text, sf.text)
                UiController.divMod()
                UiController.updateHistory(ff.text + " % " + sf.text + " = " + UiController.result)
            }
        }
        SwipeViewItem {
            id: derivative
            visible: swipeView.currentIndex==6?true:false
            operatorValue: "derivative"
            operatorUse: false
            secondOperationUse: false
            firstOperationName: "DERIVATIVE"
            calculate.onClicked: {
                if(!checkFields())
                    return
                UiController.inputPolynomials(ff.text)
                UiController.derivate()
                UiController.updateHistory(ff.text + "' = " + UiController.result)
            }
        }
        SwipeViewItem {
            id: makemonic
            visible: swipeView.currentIndex==7?true:false
            operatorValue: "make monic"
            operatorUse: false
            secondOperationUse: false
            firstOperationName: "MAKEMONIC"
            calculate.onClicked: {
                if(!checkFields())
                    return
                UiController.inputPolynomials(ff.text)
                UiController.monic()
                UiController.updateHistory("Make Monic(" + ff.text + ") = " + UiController.result)
            }
        }
        SwipeViewItem {
            id: evaluate
            visible: swipeView.currentIndex==8?true:false
            operatorValue: "evaluate"
            operatorUse: false

            secondOperationName: "EVALUATE"
            secondFieldPlaceholder: "Int"
            calculate.onClicked: {
                if(!checkFields())
                    return
                UiController.inputPolynomials(ff.text)
                UiController.evaluate(sf.text)
                UiController.updateHistory(ff.text + "(" + sf.text + ") : " + UiController.result)
            }
        }
        SwipeViewItem {
            id: rootsNum
            visible: swipeView.currentIndex==9?true:false
            operatorValue: "Roots Num"
            operatorUse: false
            secondOperationUse: false
            firstOperationName: "ROOTSNUM"
            calculate.onClicked: {
                if(!checkFields())
                    return
                UiController.inputPolynomials(ff.text)
                UiController.rootsNumber()
                UiController.updateHistory("Roots Num(" + ff.text + ") = " + UiController.result)
            }
        }
        SwipeViewItem {
            id: inverse
            visible: swipeView.currentIndex==10?true:false
            operatorValue: "Inverse"
            operatorUse: false
            secondOperationUse: false
            firstOperationName: "INVERSE"
            calculate.onClicked: {
                if(!checkFields())
                    return
                UiController.inputPolynomials(ff.text)
                UiController.inverse()
                UiController.updateHistory("Inverse(" + ff.text + ") = " + UiController.result)
            }
        }
        SwipeViewItem {
            id: gcd
            visible: swipeView.currentIndex==11?true:false
            operatorValue: "gcd"
            operatorUse: false
            firstOperationName: "GCD"
            calculate.onClicked: {
                if(!checkFields())
                    return
                UiController.inputPolynomials(ff.text, sf.text)
                UiController.gcd()
                UiController.updateHistory("GCD(" + ff.text + "," + sf.text + ") = " + UiController.result)
            }
        }
        SwipeViewItem {
            id: buildCircuarPolynom
            visible: swipeView.currentIndex==12?true:false
            operatorValue: "build circular polynom"
            operatorUse: false
            secondOperationUse: false
            firstOperationName: "BUILD_CIRCULAR_POLYNOM"
            firstFieldPlaceholder: "Int"
            calculate.onClicked: {
                if(!checkFields())
                    return
                UiController.buildCircularPolynom(ff.text)
                UiController.updateHistory("BuildCircuarPolynom(" + ff.text + ") = " + UiController.result)
            }
        }
        SwipeViewItem {
            id: isIrreducible
            visible: swipeView.currentIndex==13?true:false
            operatorValue: "check irreducible"
            operatorUse: false
            secondOperationUse: false
            firstOperationName: "CHECK_IRR"
            calculate.onClicked: {
                if(!checkFields())
                    return
                UiController.inputPolynomials(ff.text)
                UiController.isIrreduc()
                UiController.updateHistory("IsIrreducible(" + ff.text + ") = " + UiController.result)
            }
        }
        SwipeViewItem {
            id: irrPolynomOrder
            visible: swipeView.currentIndex==14?true:false
            operatorValue: "calculate order of irreducible poolynom"
            operatorUse: false
            secondOperationUse: false
            firstOperationName: "IRR_POL_ORDER"
            calculate.onClicked: {
                if(!checkFields())
                    return
                UiController.inputPolynomials(ff.text)
                UiController.irrPolOrder()
                UiController.updateHistory("IrrPolynomOrder(" + ff.text + ") = " + UiController.result)
            }
        }
        SwipeViewItem {
            id: redPolynomOrder
            visible: swipeView.currentIndex==15?true:false
            operatorValue: "calculate order of reducible poolynom"
            operatorUse: false
            secondOperationUse: false
            firstOperationName: "RED_POL_ORDER"
        }
    }


}
