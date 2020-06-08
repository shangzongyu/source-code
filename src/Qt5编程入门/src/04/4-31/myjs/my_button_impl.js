var clickCount = 0;   // 该状态对于每一个MyButton的实例都是独立的
function onClicked(btn) {
    clickCount += 1;
    if ((clickCount % 5) == 0) {
        btn.color = Qt.rgba(1,0,0,1);
    } else {
        btn.color = Qt.rgba(0,1,0,1);
    }
}
