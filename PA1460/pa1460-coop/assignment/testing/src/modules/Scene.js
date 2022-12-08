// scene class
class Scene {
  constructor(canvas) {
    this.canvas = canvas;
    this.ctx = canvas.getContext("2d");
    this.width = canvas.width;
    this.height = canvas.height;
    this.selectedObjectId = -1;
    this.gameObjects = [];
    this.selectedInteraction = null;
  }

  addGameObject(gameObject) {
    this.gameObjects.push(gameObject);
  }

  selectGameObject(id) {
    this.selectedObjectId = id;
    return this.getGameobjectById(id).select();
  }

  getGameobjectById(id) {
    return this.gameObjects.find((gameObject) => gameObject.id === id);
  }

  selectInteraction(interaction) {
    if (this.selectGameObject == null) throw new Error("No object selected");
    this.selectedInteraction = interaction;
  }

  interactWithSelectedObject() {
    if (this.selectGameObject == null) throw new Error("No object selected");
    this.getGameobjectById(this.selectedObjectId).interact(
      this.selectedInteraction
    );
  }
}
module.exports = Scene;
