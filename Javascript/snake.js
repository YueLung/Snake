class Snake {
  constructor(ctx) {
    this.ctx = ctx;
  }

  clearRect(x, y) {
    this.ctx.clearRect(x * RectWidth, y * RectWidth, RectWidth, RectWidth);
  }

  init() {
    this.body = [
      { x: 2, y: 0 },
      { x: 1, y: 0 },
      { x: 0, y: 0 },
    ];
    this.preTail = {
      x: this.body[this.body.length - 1].x,
      y: this.body[this.body.length - 1].y,
    };
    this.direction = "right";
    this.nextDirection = "right";
    for (var i = 0; i < this.body.length; ++i) {
      this.#drawRect(this.body[i].x, this.body[i].y);
    }
  }

  update() {
    this.clearRect(
      this.body[this.body.length - 1].x,
      this.body[this.body.length - 1].y
    );

    this.preTail.x = this.body[this.body.length - 1].x;
    this.preTail.y = this.body[this.body.length - 1].y;

    for (var i = this.body.length - 1; i > 0; --i) {
      this.body[i].x = this.body[i - 1].x;
      this.body[i].y = this.body[i - 1].y;
    }

    if (
      (this.direction == "up" && this.nextDirection == "down") ||
      (this.direction == "down" && this.nextDirection == "up") ||
      (this.direction == "left" && this.nextDirection == "right") ||
      (this.direction == "right" && this.nextDirection == "left")
    ) {
      this.direction = this.direction;
    } else {
      this.direction = this.nextDirection;
    }

    switch (this.direction) {
      case "up":
        if (this.body[0].y - 1 == -1) {
          this.body[0].y = HeightCount - 1;
        } else {
          this.body[0].y -= 1;
        }
        break;
      case "down":
        if (this.body[0].y + 1 == HeightCount) {
          this.body[0].y = 0;
        } else {
          this.body[0].y += 1;
        }
        break;
      case "left":
        if (this.body[0].x - 1 == -1) {
          this.body[0].x = WidthCount - 1;
        } else {
          this.body[0].x -= 1;
        }
        break;
      case "right":
        if (this.body[0].x + 1 == WidthCount) {
          this.body[0].x = 0;
        } else {
          this.body[0].x += 1;
        }
        break;
    }

    this.#drawRect(this.body[0].x, this.body[0].y);
  }

  addBody() {
    this.body.push({
      x: this.preTail.x,
      y: this.preTail.y,
    });
    this.#drawRect(this.preTail.x, this.preTail.y);
    this.#drawRect(this.body[0].x, this.body[0].y);
  }

  isGameOver() {
    for (var i = 1; i < this.body.length; ++i) {
      if (
        this.body[0].x == this.body[i].x &&
        this.body[0].y == this.body[i].y
      ) {
        return true;
      }
    }

    return false;
  }

  #drawRect(x, y) {
    this.ctx.fillStyle = "#ffffff";
    this.ctx.fillRect(
      RectPadding + x * RectWidth,
      RectPadding + y * RectWidth,
      RectWidth - 2 * RectPadding,
      RectWidth - 2 * RectPadding
    );
  }
}
