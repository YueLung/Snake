const canvas = document.querySelector("canvas");
const ctx = canvas.getContext("2d");

canvas.width = RectWidth * WidthCount;
canvas.height = RectWidth * HeightCount;

var refreshIntervalId = null;

const snake = new Snake(ctx);
const fruit = new Fruit(ctx);

function restart() {
  if (refreshIntervalId == null) {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    gameLoop();
  }
}

window.onload = () => {
  gameLoop();
};

function gameLoop() {
  snake.init();
  createFruit();
  refreshIntervalId = setInterval(update, 1000 / 15);
}

function update() {
  snake.update();

  if (snake.isGameOver()) {
    console.log("game over");
    clearInterval(refreshIntervalId);
    refreshIntervalId = null;
  }

  if (snake.body[0].x == fruit.x && snake.body[0].y == fruit.y) {
    createFruit();
    snake.addBody();
  }
}

function createFruit() {
  fruit.clear();
  do {
    fruit.create();
  } while (isFruitOnSnake());

  fruit.draw();
}

function isFruitOnSnake() {
  for (var i = 0; i < snake.body.length; ++i) {
    if (snake.body[i].x == fruit.x && snake.body[i].y == fruit.y) {
      return true;
    }
  }
  return false;
}

addEventListener("keydown", ({ keyCode }) => {
  setTimeout(() => {
    switch (keyCode) {
      case 38:
        snake.nextDirection = "up";
        break;
      case 40:
        snake.nextDirection = "down";
        break;
      case 37:
        snake.nextDirection = "left";
        break;
      case 39:
        snake.nextDirection = "right";
        break;
    }
  }, 1);
});
