import QtQuick 2.2
import QtQuick.Particles 2.0

Item {
    id: root; width: 360; height: 540

    Image {
        anchors.fill: parent
        source: "images/finalfrontier.png"
    }
    ParticleSystem { id: sys }

    Emitter {
        system: sys; anchors.centerIn: parent
        group: "meteor"; emitRate: 3; lifeSpan: 5000
        acceleration: PointDirection { xVariation: 30; yVariation: 30; }
        size: 15; endSize: 300
    }

    ImageParticle {
        system: sys; groups: ["meteor"]
        sprites:[Sprite {
                name: "spinning"; source: "images/meteor.png"
                frameCount: 35; frameDuration: 40; randomStart: true
                to: {"explode":0, "spinning":1}
            },Sprite {
                name: "explode"; source: "images/_explo.png"
                frameCount: 22; frameDuration: 40
                to: {"nullFrame":1}
            },Sprite {
                name: "nullFrame"; source: "images/nullRock.png"
                frameCount: 1; frameDuration: 1000
            }
        ]
    }

    Image {
        id: rocketShip; source: "images/rocket.png"
        x: 100; y:100
    }

    SpriteGoal {
        groups: ["meteor"]; system: sys;
        goalState: "explode"; jump: true
        anchors.fill: rocketShip; width: 60; height: 60
    }
}
