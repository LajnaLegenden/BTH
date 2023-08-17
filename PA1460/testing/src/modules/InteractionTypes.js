// abstract class for interaction types

class InteractionTypes {
  constructor(type, data, fn, target) {
    this.type = type;
    this.data = data;
    this.fn = fn;
    this.target = target;
  }

  run() {
    this.fn(this.data, this.target);
    return true;
  }
}

// Interaction types

/**
 * @class
 */
class TurnOnInteraction extends InteractionTypes {
  /**
   *
   * @param {GameObject} target
   */
  constructor(target) {
    super("turnOn", null, null, target);
    this.fn = function (target) {
      console.log(`GameObject ${this.target.id}: ${this.target.state}`);
    };
  }
}

/**
 * @class
 */
class TurnOffInteraction extends InteractionTypes {
  /**
   *
   * @param {GameObject} target
   */
  constructor(target) {
    super("turnOff", null, null, target);
    this.fn = function (target) {
      console.log(`GameObject ${this.target.id}: ${this.target.state}`);
    };
  }
}

/**
 * @class
 */
class TasteInteraction extends InteractionTypes {
  /**
   *
   * @param {GameObject} target
   */
  constructor(target) {
    super("Taste", "Tasted", null, target);
    this.fn = function (target) {
      console.log(`GameObject ${this.target.id}: ${this.data}`);
    };
  }
}

/**
 * @class
 */
class LookInteraction extends InteractionTypes {
  /**
   *
   * @param {GameObject} target
   */
  constructor(target) {
    super("Look", "Looked", null, target);
    this.fn = function (target) {
      console.log(`GameObject ${this.target.id}: ${this.data}`);
    };
  }
}

/**
 * @class
 */
class MoveInteraction extends InteractionTypes {
  /**
   *
   * @param {GameObject} target
   */
  constructor(target) {
    super("Move", "Moved", null, target);
    this.fn = function (target) {
      console.log(`GameObject ${this.target.id}: ${this.data}`);
    };
  }
}

/**
 * @class
 */
class PickupInteraction extends InteractionTypes {
  /**
   *
   * @param {GameObject} target
   */
  constructor(target) {
    super("Pickup", "Picked Up", null, target);
    this.fn = function (target) {
      console.log(`GameObject ${this.target.id}: ${this.data}`);
    };
  }
}

/**
 * @class
 */
class DropInteraction extends InteractionTypes {
  /**
   *
   * @param {GameObject} target
   */
  constructor(target) {
    super("Drop", "Dropped", null, target);
    this.fn = (target) => {
      console.log(`GameObject ${this.target.id}: ${this.data}`);
    };
  }
}

module.exports = {
  DropInteraction,
  PickupInteraction,
  MoveInteraction,
  LookInteraction,
  TasteInteraction,
  TurnOnInteraction,
  TurnOffInteraction,
};
