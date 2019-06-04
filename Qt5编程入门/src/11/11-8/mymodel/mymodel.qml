import QtQuick 2.2
import QtQuick.LocalStorage 2.0

Rectangle {
    width: 200; height: 100

    Text {
        text: "?"
        anchors.horizontalCenter: parent.horizontalCenter

        function findGreetings() {
            var db = LocalStorage.openDatabaseSync("QQmlExampleDB", "1.0",
                                                   "The Example QML SQL!", 1000000);
            db.transaction(
                        function(tx) {
                            // 如果数据库不存在则创建数据库
                            tx.executeSql('CREATE TABLE IF NOT EXISTS Greeting
                                       (salutation TEXT, salutee TEXT)');
                            // 添加一条记录
                            tx.executeSql('INSERT INTO Greeting VALUES(?, ?)',
                                          [ 'hello', 'world' ]);
                            // 显示内容
                            var rs = tx.executeSql('SELECT * FROM Greeting');

                            var r = ""
                            for(var i = 0; i < rs.rows.length; i++) {
                                r += rs.rows.item(i).salutation + ", "
                                        + rs.rows.item(i).salutee + "\n"
                            }
                            text = r
                        }
                        )
        }
        Component.onCompleted: findGreetings()
    }
}


