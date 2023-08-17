//game object class

const {
  TasteInteraction,
  TurnOnInteraction,
  TurnOffInteraction,
  MoveInteraction,
  PickupInteraction,
  LookInteraction,
  DropInteraction,
} = require("./InteractionTypes");

class GameObject {
  constructor(x, y, w, h, velX, velY, color, id = -1) {
    this.x = x;
    this.y = y;
    this.w = w;
    this.h = h;
    this.velX = velX;
    this.velY = velY;
    this.color = color;
    this.interactionOptions = [];
    this.state = "off";
    this.id = id;
    if (id == -1) {
      this.id = Math.floor(Math.random() * 10000000);
    }

    let num = Math.floor(Math.random() * 6);
    switch (num) {
      case 0:
        this.interactionOptions.push(new TurnOnInteraction(this));
        break;
      case 1:
        this.interactionOptions.push(new TurnOffInteraction(this));
        break;
      case 2:
        this.interactionOptions.push(new DropInteraction(this));
        break;
      case 3:
        this.interactionOptions.push(new TasteInteraction(this));
        break;
      case 4:
        this.interactionOptions.push(new LookInteraction(this));
        break;
      case 5:
        this.interactionOptions.push(new MoveInteraction(this));
        break;
      case 6:
        this.interactionOptions.push(new PickupInteraction(this));
        break;
    }
  }

  draw() {
    ctx.fillStyle = this.color;
    ctx.fillRect(this.x, this.y, this.w, this.h);
  }

  setInteractionOptions(options) {
    this.interactionOptions = options;
  }

  interact(interaction) {
    return interaction.run(this);
  }

  select() {
    return this.interactionOptions;
  }

  update() {
    this.x += this.velX;
    this.y += this.velY;
  }
}
module.exports = GameObject;
