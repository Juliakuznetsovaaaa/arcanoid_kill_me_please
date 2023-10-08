

const float WINDOW_HEIGHT = 900;
const float WINDOW_WEIDH = 1600;

const float BLOCK_SIDE = 50;
const float BLOCKS_IN_COL = 8;
const float BLOCKS_IN_ROW = WINDOW_WEIDH / BLOCK_SIDE;
const float BLOCKS_NUM = BLOCKS_IN_ROW * BLOCKS_IN_COL;

const float PADDLE_WIDTH = WINDOW_WEIDH / 4;
const float PADDLE_HEIGHT = 10;
const float PADDLE_POS_X = 1.5 * PADDLE_WIDTH;
const float PADDLE_POS_Y = WINDOW_HEIGHT - 100;


const float BALL_RADIUS = 10;
const float BALL_POS_X = WINDOW_WEIDH / 2 - BALL_RADIUS;
const float BALL_POS_Y = PADDLE_POS_Y - 2 * BALL_RADIUS;

const float SPEED = 0.3;