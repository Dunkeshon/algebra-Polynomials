import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
    id:mainw
    property bool isEmptyWorkspace: true
    visible: true
    //    width: screen.width
    //    height: screen.height
    minimumWidth: 950
    minimumHeight: 475
    //   visibility: "FullScreen"
    //   flags: Qt.MaximizeUsingFullscreenGeometryHint|Qt.WindowMinMaxButtonsHint| Qt.WindowCloseButtonHint | Qt.WindowSystemMenuHint
    title: qsTr("Algebra polynomials")
    Item{
        id:topPanel
        property alias  previousIndex : showHistoryButton.previousPage
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        height: 60
        Item {
            id: group1
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            width:  fieldDescription.width + 10 + fieldInput.width + 20 + fieldExtensionDescription.width + 10 + fieldExtentionInput.width + 10
            height: parent.height
            Text {
                id: fieldDescription
                color: "#0A0908"
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                anchors.leftMargin: 10
                text: qsTr("Модуль поля p")
                font.pixelSize: 20
            }
            TextField{
                id:fieldInput
                color: "#0A0908"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: fieldDescription.right
                anchors.leftMargin: 10
                focus: true
                font.pixelSize: 18
                width: 85
                selectByMouse: true
                placeholderText: "просте"
                validator: IntValidator{bottom: 0; top: 999;}
                background: Rectangle{
                    color: "#ece9ec"//"#bcd2eb"
                }
                onEditingFinished: {
                    if(!UiController.isPrime(text)){
                        fieldInput.text = ""
                        console.log("module needs to be simple")
                    }
                }
            }
            Text {
                id: fieldExtensionDescription
                color: "#0A0908"
                anchors.left: fieldInput.right
                anchors.leftMargin: 10
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("Розширення поля q")
                font.pixelSize: 20
            }
            TextField{
                id:fieldExtentionInput
                color: "#0A0908"
                anchors.left: fieldExtensionDescription.right
                anchors.verticalCenter: parent.verticalCenter
                anchors.leftMargin: 10
                font.pixelSize: 18
                width: 85
                selectByMouse: true
                validator: IntValidator{bottom: 0; top: 999;}
                background: Rectangle{
                    color: "#ece9ec"
                }
            }
        }
        Button{
            property bool paramsChoosen: false
            id:changeInputParamsButton
            anchors.right: showHistoryButton.left
            anchors.margins: 10
            anchors.verticalCenter: parent.verticalCenter
            enabled: true
            text:
            {
                var curtext = paramsChoosen?"Змінити вхідні параметри":"Вибрати незвідний многочлен"
                return "<font color='#ffffff'>" + curtext + "</font>"
            }



            font.pixelSize: 20
            onClicked: {
                if(!changeInputParamsButton.paramsChoosen){
                    if (fieldInput.text!==""&&fieldExtentionInput.text!=="")
                    {
                        //    12 var function search for irreducible polinomials
                        //    update qProperty AvaileblePolynomials

                        //for now // p = 2   1<=q<8
                        UiController.findIrreducibles(fieldInput.text,fieldExtentionInput.text)
                        console.log(UiController.irreducibleStrings)
                        availableList.ourData=UiController.irreducibleStrings
                        // availableList.visible=true;
                        availableList.forceActiveFocus()
                        swipeView.currentIndex=1
                        group1.enabled=false
                        changeInputParamsButton.paramsChoosen = true

                    }
                }
                else{
                    group1.enabled=true;
                    swipeView.currentIndex=0;
                    workSpace.workView.currentIndex = 0;
                    workSpace.visible = false;
                    //CLEAR MAIN POLYNOM IN C++
                    UiController.clearMainPolynomial();
                    UiController.clearIrreducibles();
                    //clear history
                    UiController.clearHistory();
                    changeInputParamsButton.paramsChoosen = false

                    //UiController.historyStrings.clear(); //FIND FINCTION THAT CLEAR THIS FUCKING SHIT
                }
            }
            background: Rectangle{
                color: changeInputParamsButton.pressed? "#145499":"#1d68b8"
            }
        }
        Button{
            property var previousPage : 0
            property bool storyActive: false
            id:showHistoryButton
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 10
            font.pixelSize: 20
            text:
            {
                var curtext = storyActive? "Назад" : "Історія"
                return "<font color='#ffffff'>" + curtext + "</font>"
            }
            onClicked: {
                if(!storyActive){
                    //show historyPage
                    swipeView.currentIndex=3
                    storyActive=true
                }
                else{
                    swipeView.currentIndex = previousPage
                    storyActive=false
                }
            }
            background: Rectangle{
                color: showHistoryButton.pressed? "#145499":"#1d68b8"
            }
        }

    }
    Rectangle{
        id:topPanelSeparator
        height: 3
        z:1
        width: parent.width
        anchors.top: topPanel.bottom
        color: "#184677"
    }


    SwipeView{
        id: swipeView
        anchors.top: topPanel.bottom
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        width:parent.width/2 //parent.width - group1.width - 10
        interactive: false
        currentIndex: 0
        clip: true
        onCurrentIndexChanged: {
            if(currentIndex!=3){
                topPanel.previousIndex = currentIndex
            }
        }

        Item {
            id: blank
            visible: swipeView.currentIndex==0?true:false
            Rectangle{

                anchors.fill: parent
                Text {
                    id: guide
                    color: "#0A0908"
                    anchors.centerIn: parent

                    font.pixelSize: 36
                    text: qsTr("Спершу виберіть модуль <br>та розширення поля")
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
        }
        Item {
            id: polynomials
            visible: swipeView.currentIndex==1?true:false
            ListView{
                id:availableList
                property var ourData
                focus: true
                clip: true
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: confirmButton.top
                anchors.bottomMargin: 5

                visible: true
                model:ourData
                delegate: Rectangle{
                    id: delegate

                    height: 50
                    width: parent.width
                    Rectangle{
                        anchors.bottom: parent.bottom
                        width: parent.width
                        height: 3
                        color:"#184677"
                    }


                    Text {
                        anchors.centerIn: parent
                        color: "#0A0908"
                        font.pixelSize: 20
                        renderType: Text.NativeRendering
                        text: modelData || "empty text"

                    }
                    color: ListView.isCurrentItem ? "#99C0EB" : "#CCE0F5"
                    MouseArea {
                        anchors.fill: parent
                        //onClicked: delegate.ListView.view.currentIndex = model.index // if only selection is wanted
                        onClicked: {
                            //console.debug("click");
                            if (delegate.ListView.isCurrentItem)
                            {
                                delegate.ListView.view.currentIndex = -1;
                            }
                            else
                            {
                                delegate.ListView.view.currentIndex = model.index;
                            }
                        }
                    }
                }
                onCurrentIndexChanged: {
                    console.log("current index is:" + currentIndex)
                }
            }
            Button{
                id:confirmButton
                width: parent.width/2
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 5
                anchors.horizontalCenter: availableList.horizontalCenter
                text: "<font color='#ffffff'> Вибрати </font>"




                font.pixelSize: 20
                onClicked: {
                    if (availableList.currentIndex!=-1){
                        // save this polynomial with this index as BASIC working polynomial
                        //CLASSIC BASIC Polynomial = irreducibles[availableList.currentIndex] in C++
                        UiController.selectMainPolynom(availableList.currentIndex)
                        // instruction: select operation
                        workSpace.visible=true
                        workSpace.workView.currentIndex=0
                        // show list of tasks
                        swipeView.currentIndex=2;

                    }
                }
                background: Rectangle{
                    color: confirmButton.pressed? "#145499":"#1d68b8"
                }
            }
        }
        Item {
            id: tasks
            visible: swipeView.currentIndex==2?true:false
            ListView{
                property var dataModel: [
                    {
                        text: "+"
                    },
                    {
                        text: "-"
                    },
                    {
                        text: "*"
                    },
                    {
                        text: "/"
                    },
                    {
                        text: "%"
                    },
                    {
                        text: "Знайти похідну многочлена"
                    },
                    {
                        text: "Нормування многочлена"
                    },
                    {
                        text: "Знайти значення многочлена у точці"
                    },
                    {
                        text: "Кількість коренів многочлена"
                    },
                    {
                        text: "Знаходження оберненого многочлена до заданого"
                    },
                    {
                        text: "Знайти НСД двох многочленів"
                    },
                    {
                        text: "Знаходження кругового многочлена заданого порядку"
                    },
                    {
                        text: "Перевірка,чи є многочлен незвідним"
                    },
                    {
                        text: "Знаходження порядку незвідного многочлена"
                    },
                    {
                        text: "Знаходження порядку довільного многочлена"
                    },
                    {
                        text: "Розклад многочлена на незвідні множники \nвикористовуючи многочлени Ri"
                    },
                    {
                        text: "Розклад довільного многочлена на незвідні \nмножники за допомогою алгоритму Берлекемпа"
                    }

                ]
                id:tasksView
                focus: true
                clip: true
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: selectButton.top
                anchors.bottomMargin: 5
                visible: true
                model:dataModel
                delegate: Rectangle{
                    Rectangle{
                        anchors.bottom: parent.bottom
                        width: parent.width
                        height: 3
                        color:"#184677"
                    }

                    id: taskDelegate
                    height: 50
                    width: parent.width
                    TextArea {
                        anchors.centerIn: parent
                        color: "#0A0908"
                        font.pixelSize: 20
                        renderType: Text.NativeRendering
                        text: modelData.text || "empty text"
                    }
                    color: ListView.isCurrentItem ? "#99C0EB" : "#CCE0F5"
                    MouseArea {
                        anchors.fill: parent
                        //onClicked: delegate.ListView.view.currentIndex = model.index // if only selection is wanted
                        onClicked: {
                            //console.debug("click");
                            if (taskDelegate.ListView.isCurrentItem)
                            {
                                taskDelegate.ListView.view.currentIndex = -1;
                            }
                            else
                            {
                                taskDelegate.ListView.view.currentIndex = model.index;
                            }
                        }
                    }
                }
                onCurrentIndexChanged: {
                    console.log("current index is:" + currentIndex)
                }
            }
            Button{
                id:selectButton
                width: parent.width/2
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 5
                anchors.horizontalCenter: tasksView.horizontalCenter
                text: "<font color='#ffffff'> Вибрати </font>"
                font.pixelSize: 20
                onClicked: {
                    if (tasksView.currentIndex!=-1){
                        workSpace.visible=true
                        workSpace.enabled=false;


                        UiController.clearInputFields();

                        // show list of tasks

                        //test for ui
                        workSpace.workView.currentIndex=tasksView.currentIndex+1;
                        workSpace.enabled=true

                    }
                }
                background: Rectangle{
                    color: selectButton.pressed? "#145499":"#1d68b8"
                }
            }
        }
        Item{
            id:historyPage
            //ToDo
            visible: swipeView.currentIndex==3?true:false

            ListView{
                id:historyList
                focus: true
                clip: true
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 5
                visible: true
                model:UiController.historyStrings
                delegate: Rectangle{
                    id: delegateh
                    height: 50
                    width: parent.width
                    Rectangle{
                        anchors.bottom: parent.bottom
                        width: parent.width
                        height: 3
                        color:"#184677"
                    }
                    Text {
                        anchors.centerIn: parent
                        color: "#0A0908"
                        font.pixelSize: 20
                        renderType: Text.NativeRendering
                        text: modelData || "empty text"
                    }
                    color: ListView.isCurrentItem ? "#99C0EB" : "#CCE0F5"
                    MouseArea {
                        anchors.fill: parent
                        //onClicked: delegate.ListView.view.currentIndex = model.index // if only selection is wanted
                        onClicked: {
                            //console.debug("click");
                            if (delegate.ListView.isCurrentItem)
                            {
                                delegate.ListView.view.currentIndex = -1;
                            }
                            else
                            {
                                delegate.ListView.view.currentIndex = model.index;
                            }
                        }
                    }
                }
                onCurrentIndexChanged: {
                    console.log("current index is:" + currentIndex)


                }
            }
        }
    }

    Rectangle{
        id:separator
        anchors.right: swipeView.left
        anchors.bottom: parent.bottom
        width: 3
        height: parent.height - topPanel.height
        color: "#184677"
        z:2
    }
    WorkSpaceView{
        id:workSpace
        anchors.top: topPanel.bottom
        anchors.left: parent.left
        anchors.right: separator.left
        anchors.bottom: parent.bottom
    }
}
