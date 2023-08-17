//game class

class Game {
  constructor(canvas) {
    this.canvas = canvas;
    this.ctx = canvas.getContext("2d");
    this.width = canvas.width;
    this.height = canvas.height;
    this.sceneIndex = -1;
    this.scenes = [];
  }

  addSceneObject(gameObject) {
    this.scenes.push(gameObject);
  }

  setScene(sceneIndex) {
    this.sceneIndex = sceneIndex;
    return true
  }

  setInteractionOptions(options) {
    this.interactionOptions = options;
  }

  getGameObjectFromCurrentSceneById(id) {
    return this.scenes[this.sceneIndex].getGameobjectById(id);
  }

  selectGameObject(id) {
    return this.scenes[this.sceneIndex].selectGameObject(id);
  }

  selectInteraction(interaction) {
    this.scenes[this.sceneIndex].selectInteraction(interaction);
    return true;
  }

  runSelectedInteraction() {
    this.scenes[this.sceneIndex].interactWithSelectedObject();
  }

  draw() {
    this.ctx.clearRect(0, 0, this.width, this.height);
    this.ctx.fillStyle = "black";
    this.ctx.font = "20px Arial";
    this.ctx.fillText(this.gameOverText, this.width / 2 - 50, this.height / 2);
    this.scenes[this.sceneIndex].draw();
  }
}
module.exports = Game;
