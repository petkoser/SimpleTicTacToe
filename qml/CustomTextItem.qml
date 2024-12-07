import QtQuick 2.15

Item {
    property alias text: customText.text
    property alias font: customText.font

    CustomText {
        id: customText
        text: "Players: " + gameController.player1 + " VS " + gameController.player2
        font.pixelSize: 64
        anchors.centerIn: parent
    }
}
