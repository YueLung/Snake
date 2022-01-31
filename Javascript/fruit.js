class Fruit {
  constructor(ctx) {
    this.ctx = ctx;
    this.x = -1;
    this.y = -1;
  }

  create() {
    this.x = this.#getRandomInt(0, WidthCount);
    this.y = this.#getRandomInt(0, HeightCount);
  }

  draw() {
    this.ctx.fillStyle = "#ff8fa3";
    this.ctx.fillRect(
      this.x * RectWidth,
      this.y * RectWidth,
      RectWidth,
      RectWidth
    );
  }

  clear() {
    this.ctx.clearRect(
      this.x * RectWidth,
      this.y * RectWidth,
      RectWidth,
      RectWidth
    );
  }

  #getRandomInt(min, max) {
    min = Math.ceil(min);
    max = Math.floor(max);
    return Math.floor(Math.random() * (max - min) + min); //The maximum is exclusive and the minimum is inclusive
  }
}
