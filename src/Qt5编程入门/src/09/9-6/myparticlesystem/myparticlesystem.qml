import QtQuick 2.2
import QtQuick.Particles 2.0

Rectangle {
    width: 300; height: 300
    ParticleSystem { id: particles }
    ImageParticle {
        system: particles; color: "green"
        source: "qrc:///particleresources/glowdot.png"
    }
    Emitter {
        system: particles
        emitRate: 30; lifeSpan: 2000
        velocity: PointDirection { y:100; yVariation: 40; }
        width: parent.width; height: 70
    }
    Rectangle {
        x: 80; y: 120; width: 140; height: 30
        color: "#803333AA"
        Age {
            anchors.fill: parent; system: particles
            lifeLeft: 80; once: true; advancePosition: false
        }
    }
}
