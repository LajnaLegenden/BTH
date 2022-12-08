const { createCanvas, loadImage } = require('canvas')

const Game = require("./modules/Game")
const Scene = require("./modules/Scene")
const GameObject = require('./modules/GameObject')

const canvas = createCanvas(800, 600);



const game = new Game(canvas);

for(let i = 0; i < 10; i++) {
    const scene = new Scene(canvas);
    for(let j = 0; j < 10; j++) {
        scene.addGameObject(new GameObject(i * 50, j * 50, 50, 50, 0, 0, "red"));
    }
    scene.addGameObject(new GameObject(100, 100, 50, 50, 0, 0, "red", 23332));
    game.addSceneObject(scene);
}

console.log(game)




