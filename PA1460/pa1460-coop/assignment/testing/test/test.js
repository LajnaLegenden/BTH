let chai = require("chai");
let assert = require("assert");
var expect = chai.expect;

let { createCanvas } = require("canvas");

const Game = require("../src/modules/Game");
const Scene = require("../src/modules/Scene");
const GameObject = require("../src/modules/GameObject");
const canvas = createCanvas(800, 600);

let game = null;

describe("Game", function () {
  before(function () {
    game = new Game(canvas);
    for (let i = 0; i < 10; i++) {
      const scene = new Scene(canvas);
      for (let j = 0; j < 10; j++) {
        scene.addGameObject(
          new GameObject(i * 50, j * 50, 50, 50, 0, 0, "red")
        );
      }
      scene.addGameObject(new GameObject(100, 100, 50, 50, 0, 0, "red", 23332));
      game.addSceneObject(scene);
    }
  });
  describe("Creation", function () {
    it("should create a new game with 10 scenes", function () {
      assert.equal(game.scenes.length, 10);
    });
    it("first scene should have 11 game objects", function () {
      assert.equal(game.scenes[0].gameObjects.length, 11);
    });
    it("no scene should be selected at start", function () {
      assert.equal(game.sceneIndex, -1);
    });
  });
});

describe("Scene", function () {
  before(function () {
    const scene = new Scene(canvas);
    for (let j = 0; j < 10; j++) {
      scene.addGameObject(new GameObject(50, j * 50, 50, 50, 0, 0, "red"));
    }
    scene.addGameObject(new GameObject(100, 100, 50, 50, 0, 0, "red", 23332));
  });
  describe("Creation", function () {
    it("should create a new scene with 11 game objects", function () {
      assert.equal(game.scenes[0].gameObjects.length, 11);
    });

    it("can find a gameObject with id 23332", function () {
      assert.equal(game.scenes[0].getGameobjectById(23332).id, 23332);
    });
  });
});

describe("Use case: Interact with Object", function () {
  before(function () {
    game = new Game(canvas);
    for (let i = 0; i < 10; i++) {
      const scene = new Scene(canvas);
      for (let j = 0; j < 10; j++) {
        scene.addGameObject(
          new GameObject(i * 50, j * 50, 50, 50, 0, 0, "red")
        );
      }
      scene.addGameObject(new GameObject(100, 100, 50, 50, 0, 0, "red", 23332));
      game.addSceneObject(scene);
    }
  });
  describe("positive path", function () {
    let interaction = null;
    it("can find a gameObject with id 23332", function () {
      assert.equal(game.scenes[0].getGameobjectById(23332).id, 23332);
    });
    it("can select scene", function () {
      assert.equal(game.setScene(0), true);
    });
    it("intended gameObject is in scene", function () {
      let obj = game.getGameObjectFromCurrentSceneById(23332);
      expect(obj).to.not.be.null;
    });

    it("can select the gameObject and returns interaction options", function () {
      let obj = game.selectGameObject(23332);
      interaction = obj[0];
      expect(obj.length).to.be.equal(1);
    });

    it("can select the interaction and returns options if any (none for these interactions)", function () {
      let obj = game.selectInteraction(interaction);
      expect(obj).to.be.true;
    });

    it("run the interaction", function () {
      let obj = game.runSelectedInteraction();
    });
  });
  describe("no selected object path", function () {
    let interaction = null;
    it("can find a gameObject with id 23332", function () {
      assert.equal(game.scenes[0].getGameobjectById(23332).id, 23332);
    });
    it("can select scene", function () {
      assert.equal(game.setScene(0), true);
    });
    it("intended gameObject is in scene", function () {
      let obj = game.getGameObjectFromCurrentSceneById(23332);
      expect(obj).to.not.be.null;
    });

    it("fails when selecting interaction", function () {
      expect(game.selectInteraction()).to.throw
    });
  });
});
