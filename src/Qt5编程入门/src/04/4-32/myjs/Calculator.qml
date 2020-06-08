import QtQuick 2.2

// 这个JavaScript 资源只会被QML引擎调用一次，
// 即便Calculator.qml文件创建了多个实例
import "factorial.js" as FactorialCalculator

Text {
    property int input: 17
    width: 500; height: 100
    text: "The factorial of " + input + " is: "
          + FactorialCalculator.factorial(input)
}

