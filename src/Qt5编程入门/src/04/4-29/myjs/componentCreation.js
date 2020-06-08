var component;
var sprite;

function createSpriteObjects() {
    component = Qt.createComponent("Sprite.qml");
    if (component.status == Component.Ready)
        finishCreation();
    else
        component.statusChanged.connect(finishCreation);
}

function finishCreation() {
    if (component.status == Component.Ready) {
        sprite = component.createObject(appWindow, {"x": 100, "y": 100});
        if (sprite == null) {
            // 错误处理
            console.log("Error creating object");
        }
    } else if (component.status == Component.Error) {
        // 错误处理
        console.log("Error loading component:", component.errorString());
    }
}
