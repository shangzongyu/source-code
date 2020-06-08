import QtQuick 2.2

Item {
    property var theArray: new Array()
    property var theDate: new Date()

    Component.onCompleted: {
        for (var i = 0; i < 10; i++)
            theArray.push("Item " + i)
        console.log("There are", theArray.length, "items in the array")
        console.log("The time is", theDate.toUTCString())
    }
}

