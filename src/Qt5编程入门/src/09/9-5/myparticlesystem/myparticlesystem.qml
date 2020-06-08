import QtQuick 2.2
import QtQuick.Particles 2.0

Rectangle {
    width: 360; height: 600; color: "black"

    ParticleSystem {
        anchors.fill: parent

        ParticleGroup {
            name: "unlit"; duration: 1000
            to: {"lighting":1, "unlit":10}
            ImageParticle {
                source: "images/particle.png"
                color: "#2060160f"; colorVariation: 0.1
            }
            Emitter {
                height: parent.height/2
                emitRate: 4; lifeSpan: 3000
                size: 24; sizeVariation: 4
                velocity: PointDirection {x:120;
                        xVariation: 80; yVariation: 50}
                acceleration: PointDirection {y:120}
            }
        }

        ParticleGroup {
            name: "lighting"; duration: 200; to: {"lit":1}
        }

        ParticleGroup {
            name: "lit"; duration: 2000
            TrailEmitter {
                group: "flame"; emitRatePerParticle: 50
                lifeSpan: 200; emitWidth: 8; emitHeight: 8
                size: 24; sizeVariation: 8; endSize: 4
            }
        }

        ImageParticle {
            groups: ["flame", "lit", "lighting"]
            source: "images/particle.png"
            color: "#00ff400f"; colorVariation: 0.1
        }
    }
}
