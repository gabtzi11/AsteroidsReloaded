#include <stdlib.h>

#define MAX_BULLETS 4
#define MAX_ASTEROIDS 26

#define ST_MAINMENU 0
#define ST_INGAME   1

#define ASTEROID_SMALL  0
#define ASTEROID_LARGE  1

typedef struct {
  bool present;
  float x;
  float y;
  float vx;
  float vy;
  unsigned long creation_time; // millis
} bullet_t;

typedef struct {
  bool present;
  float x;
  float y;
  float vx;
  float vy;
  int type;
} asteroid_t;

const int dacpinY = A21;
const int dacpinX = A22;

const int pinLeft = 16;
const int pinRight = 15;
const int pinThrust = 28;
const int pinShoot = 27;
const int pinHyper = 14;

const int pinBlank = 23;

float sintable[] = {0.0, 0.017, 0.035, 0.052, 0.07, 0.087, 0.105, 0.122, 0.139, 0.156, 0.174, 0.191, 0.208, 0.225, 0.242, 0.259, 0.276, 0.292, 0.309, 0.326, 0.342, 0.358, 0.375, 0.391, 0.407, 0.423, 0.438, 0.454, 0.469, 0.485, 0.5, 0.515, 0.53, 0.545, 0.559, 0.574, 0.588, 0.602, 0.616, 0.629, 0.643, 0.656, 0.669, 0.682, 0.695, 0.707, 0.719, 0.731, 0.743, 0.755, 0.766, 0.777, 0.788, 0.799, 0.809, 0.819, 0.829, 0.839, 0.848, 0.857, 0.866, 0.875, 0.883, 0.891, 0.899, 0.906, 0.914, 0.921, 0.927, 0.934, 0.94, 0.946, 0.951, 0.956, 0.961, 0.966, 0.97, 0.974, 0.978, 0.982, 0.985, 0.988, 0.99, 0.993, 0.995, 0.996, 0.998, 0.999, 0.999, 1.0, 1.0, 1.0, 0.999, 0.999, 0.998, 0.996, 0.995, 0.993, 0.99, 0.988, 0.985, 0.982, 0.978, 0.974, 0.97, 0.966, 0.961, 0.956, 0.951, 0.946, 0.94, 0.934, 0.927, 0.921, 0.914, 0.906, 0.899, 0.891, 0.883, 0.875, 0.866, 0.857, 0.848, 0.839, 0.829, 0.819, 0.809, 0.799, 0.788, 0.777, 0.766, 0.755, 0.743, 0.731, 0.719, 0.707, 0.695, 0.682, 0.669, 0.656, 0.643, 0.629, 0.616, 0.602, 0.588, 0.574, 0.559, 0.545, 0.53, 0.515, 0.5, 0.485, 0.469, 0.454, 0.438, 0.423, 0.407, 0.391, 0.375, 0.358, 0.342, 0.326, 0.309, 0.292, 0.276, 0.259, 0.242, 0.225, 0.208, 0.191, 0.174, 0.156, 0.139, 0.122, 0.105, 0.087, 0.07, 0.052, 0.035, 0.017, 0.0, -0.017, -0.035, -0.052, -0.07, -0.087, -0.105, -0.122, -0.139, -0.156, -0.174, -0.191, -0.208, -0.225, -0.242, -0.259, -0.276, -0.292, -0.309, -0.326, -0.342, -0.358, -0.375, -0.391, -0.407, -0.423, -0.438, -0.454, -0.469, -0.485, -0.5, -0.515, -0.53, -0.545, -0.559, -0.574, -0.588, -0.602, -0.616, -0.629, -0.643, -0.656, -0.669, -0.682, -0.695, -0.707, -0.719, -0.731, -0.743, -0.755, -0.766, -0.777, -0.788, -0.799, -0.809, -0.819, -0.829, -0.839, -0.848, -0.857, -0.866, -0.875, -0.883, -0.891, -0.899, -0.906, -0.914, -0.921, -0.927, -0.934, -0.94, -0.946, -0.951, -0.956, -0.961, -0.966, -0.97, -0.974, -0.978, -0.982, -0.985, -0.988, -0.99, -0.993, -0.995, -0.996, -0.998, -0.999, -0.999, -1.0, -1.0, -1.0, -0.999, -0.999, -0.998, -0.996, -0.995, -0.993, -0.99, -0.988, -0.985, -0.982, -0.978, -0.974, -0.97, -0.966, -0.961, -0.956, -0.951, -0.946, -0.94, -0.934, -0.927, -0.921, -0.914, -0.906, -0.899, -0.891, -0.883, -0.875, -0.866, -0.857, -0.848, -0.839, -0.829, -0.819, -0.809, -0.799, -0.788, -0.777, -0.766, -0.755, -0.743, -0.731, -0.719, -0.707, -0.695, -0.682, -0.669, -0.656, -0.643, -0.629, -0.616, -0.602, -0.588, -0.574, -0.559, -0.545, -0.53, -0.515, -0.5, -0.485, -0.469, -0.454, -0.438, -0.423, -0.407, -0.391, -0.375, -0.358, -0.342, -0.326, -0.309, -0.292, -0.276, -0.259, -0.242, -0.225, -0.208, -0.191, -0.174, -0.156, -0.139, -0.122, -0.105, -0.087, -0.07, -0.052, -0.035, -0.017};
float costable[] = {1.0, 1.0, 0.999, 0.999, 0.998, 0.996, 0.995, 0.993, 0.99, 0.988, 0.985, 0.982, 0.978, 0.974, 0.97, 0.966, 0.961, 0.956, 0.951, 0.946, 0.94, 0.934, 0.927, 0.921, 0.914, 0.906, 0.899, 0.891, 0.883, 0.875, 0.866, 0.857, 0.848, 0.839, 0.829, 0.819, 0.809, 0.799, 0.788, 0.777, 0.766, 0.755, 0.743, 0.731, 0.719, 0.707, 0.695, 0.682, 0.669, 0.656, 0.643, 0.629, 0.616, 0.602, 0.588, 0.574, 0.559, 0.545, 0.53, 0.515, 0.5, 0.485, 0.469, 0.454, 0.438, 0.423, 0.407, 0.391, 0.375, 0.358, 0.342, 0.326, 0.309, 0.292, 0.276, 0.259, 0.242, 0.225, 0.208, 0.191, 0.174, 0.156, 0.139, 0.122, 0.105, 0.087, 0.07, 0.052, 0.035, 0.017, 0.0, -0.017, -0.035, -0.052, -0.07, -0.087, -0.105, -0.122, -0.139, -0.156, -0.174, -0.191, -0.208, -0.225, -0.242, -0.259, -0.276, -0.292, -0.309, -0.326, -0.342, -0.358, -0.375, -0.391, -0.407, -0.423, -0.438, -0.454, -0.469, -0.485, -0.5, -0.515, -0.53, -0.545, -0.559, -0.574, -0.588, -0.602, -0.616, -0.629, -0.643, -0.656, -0.669, -0.682, -0.695, -0.707, -0.719, -0.731, -0.743, -0.755, -0.766, -0.777, -0.788, -0.799, -0.809, -0.819, -0.829, -0.839, -0.848, -0.857, -0.866, -0.875, -0.883, -0.891, -0.899, -0.906, -0.914, -0.921, -0.927, -0.934, -0.94, -0.946, -0.951, -0.956, -0.961, -0.966, -0.97, -0.974, -0.978, -0.982, -0.985, -0.988, -0.99, -0.993, -0.995, -0.996, -0.998, -0.999, -0.999, -1.0, -1.0, -1.0, -0.999, -0.999, -0.998, -0.996, -0.995, -0.993, -0.99, -0.988, -0.985, -0.982, -0.978, -0.974, -0.97, -0.966, -0.961, -0.956, -0.951, -0.946, -0.94, -0.934, -0.927, -0.921, -0.914, -0.906, -0.899, -0.891, -0.883, -0.875, -0.866, -0.857, -0.848, -0.839, -0.829, -0.819, -0.809, -0.799, -0.788, -0.777, -0.766, -0.755, -0.743, -0.731, -0.719, -0.707, -0.695, -0.682, -0.669, -0.656, -0.643, -0.629, -0.616, -0.602, -0.588, -0.574, -0.559, -0.545, -0.53, -0.515, -0.5, -0.485, -0.469, -0.454, -0.438, -0.423, -0.407, -0.391, -0.375, -0.358, -0.342, -0.326, -0.309, -0.292, -0.276, -0.259, -0.242, -0.225, -0.208, -0.191, -0.174, -0.156, -0.139, -0.122, -0.105, -0.087, -0.07, -0.052, -0.035, -0.017, -0.0, 0.017, 0.035, 0.052, 0.07, 0.087, 0.105, 0.122, 0.139, 0.156, 0.174, 0.191, 0.208, 0.225, 0.242, 0.259, 0.276, 0.292, 0.309, 0.326, 0.342, 0.358, 0.375, 0.391, 0.407, 0.423, 0.438, 0.454, 0.469, 0.485, 0.5, 0.515, 0.53, 0.545, 0.559, 0.574, 0.588, 0.602, 0.616, 0.629, 0.643, 0.656, 0.669, 0.682, 0.695, 0.707, 0.719, 0.731, 0.743, 0.755, 0.766, 0.777, 0.788, 0.799, 0.809, 0.819, 0.829, 0.839, 0.848, 0.857, 0.866, 0.875, 0.883, 0.891, 0.899, 0.906, 0.914, 0.921, 0.927, 0.934, 0.94, 0.946, 0.951, 0.956, 0.961, 0.966, 0.97, 0.974, 0.978, 0.982, 0.985, 0.988, 0.99, 0.993, 0.995, 0.996, 0.998, 0.999, 0.999, 1.0};

int allglyphs[] = {0,360,0,0,270,360,270,0,0,360,270,360,0,0,270,0,0,0,270,360,0,360,0,0,0,360,270,360,270,360,270,207,270,207,0,207,0,207,0,0,0,0,270,0,0,360,270,360,0,207,270,207,0,0,270,0,270,360,270,0,0,360,0,207,270,360,270,0,0,207,270,207,0,360,270,360,0,360,0,207,0,207,270,207,270,207,270,0,270,0,0,0,0,360,0,0,270,207,270,0,0,207,270,207,0,0,270,0,0,360,270,360,270,360,270,0,0,360,0,0,270,360,270,0,0,360,270,360,0,0,270,0,0,207,270,207,0,360,270,360,0,207,270,207,0,360,0,207,270,360,270,0,0,270,0,0,270,270,270,0,135,360,0,270,135,360,270,270,0,207,270,207,0,360,0,0,0,360,180,360,0,0,180,0,180,360,270,243,180,0,270,117,0,207,270,207,270,117,270,243,0,360,270,360,0,360,0,0,0,0,270,0,0,360,0,0,0,360,180,360,0,0,180,0,180,360,270,243,180,0,270,117,270,117,270,243,0,360,270,360,0,360,0,0,0,0,270,0,0,207,270,207,0,360,270,360,0,360,0,0,0,207,270,207,0,360,270,360,0,360,0,0,0,0,270,0,270,360,270,315,270,0,270,207,90,207,270,207,0,360,0,0,270,360,270,0,0,207,270,207,0,360,270,360,0,0,270,0,135,360,135,0,270,360,270,360,270,0,135,0,270,0,0,117,135,0,0,180,270,360,0,360,0,0,0,180,270,0,0,360,0,0,0,0,270,0,0,360,0,0,270,360,270,0,0,360,135,207,270,360,135,207,0,360,0,0,270,360,270,0,0,360,270,0,0,360,0,0,270,360,270,0,0,360,270,360,0,0,270,0,0,360,270,360,0,360,0,0,0,207,270,207,270,360,270,207,0,360,270,360,0,360,0,0,270,360,270,90,270,90,180,0,180,0,0,0,270,0,180,90,0,360,270,360,0,360,0,0,0,207,270,207,270,360,270,207,0,207,270,0,0,360,270,360,0,360,0,207,0,207,270,207,270,207,270,0,270,0,0,0,0,360,270,360,135,360,135,0,270,360,0,360,0,0,270,360,270,0,0,0,270,0,0,360,135,0,135,0,270,360,0,360,0,0,270,360,270,0,0,0,135,180,135,180,270,0,0,360,270,0,270,360,0,0,0,360,135,180,135,180,270,360,135,180,135,0,0,360,270,360,270,360,0,0,0,0,270,0,135,360,0,315,135,360,270,315,0,315,0,45,270,315,270,45,270,45,135,0,0,45,135,0,45,270,225,270,45,90,225,90,45,270,45,90,};
int glyphlens[]={20,4,20,16,12,20,16,8,20,16,20,28,12,24,16,12,24,12,14,12,12,8,16,12,16,16,24,20,20,10,12,8,16,8,12,12,36,};
int ascii2glyph[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,9,0,0,0,0,0,0,0,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,0,0,0,0,0,0,0,0,36,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,};
int glyph_starts[]={0,20,24,44,60,72,92,108,116,136,152,172,200,212,236,252,264,288,300,314,326,338,346,362,374,390,406,430,450,470,480,492,500,516,524,536,548,};

int shippoints[] = {
  -60,-50, 0, 70,
  0,70, 60,-50,
  40,-10, -40,-10
};

int asteroidpoints[] = {
0, -75, 100, -175, 
100, -175, 200, -75, 
200, -75, 150, 0, 
150, 0, 200, 100, 
200, 100, 50, 175, 
50, 175, -100, 175, 
-100, 175, -200, 100, 
-200, 100, -200, -75, 
-200, -75, -100, -175, 
-100, -175, 0, -75
};

float shipx;
float shipy;
float shipvx;
float shipvy;
float shiptheta;

bullet_t bullets[MAX_BULLETS] = {0};
asteroid_t asteroids[MAX_ASTEROIDS] = {0};

int find_free_bullet_index();
int find_oldest_bullet_index();
void update_bullets(double);
float wrapf(float f, float l, float r);
void ship_shoot();

void setup() {
  analogWriteResolution(12);
  pinMode(pinLeft, INPUT_PULLUP);
  pinMode(pinRight, INPUT_PULLUP);
  pinMode(pinHyper, INPUT_PULLUP);
  pinMode(pinThrust, INPUT_PULLUP);
  pinMode(pinShoot, INPUT_PULLUP);
  pinMode(pinBlank, OUTPUT);
  pinMode(13, OUTPUT);
  randomSeed(0);
  Serial.begin(9600);

  shipx = 2000;
  shipy = 1500;
  shipvx = 0;
  shipvy = 0;

  asteroids[0] = {true, 500, 500, 1500, 800, ASTEROID_LARGE};
  asteroids[1] = {true, 1000, 1000, -800, 1500, ASTEROID_LARGE};
}

/** Asteroid code */

void draw_asteroid(asteroid_t *ast) {
  for (int i = 0; i < sizeof(asteroidpoints)/sizeof(int); i += 4) {
    line(ast->x+asteroidpoints[i], ast->y+asteroidpoints[i+1], ast->x+asteroidpoints[i+2], ast->y+asteroidpoints[i+3], 2);
  }
}

/** Bullet code */

int find_free_bullet_index() {
  for (int i = 0; i < MAX_BULLETS; i++) {
    if (!bullets[i].present) return i;
  }
  return -1;
}

int find_oldest_bullet_index() {
  int oldest = -1;
  unsigned long oldest_time = millis();

  for (int i = 0; i < MAX_BULLETS; i++) {
    if (bullets[i].present) {
      if (bullets[i].creation_time < oldest_time) {
        oldest_time = bullets[i].creation_time;
        oldest = i;
      }
    }
  }

  return oldest;
}

void update_bullets(double delta) {
  for (int i = 0; i < MAX_BULLETS; i++) {
    if (bullets[i].present) {
      bullets[i].x += bullets[i].vx * delta;
      bullets[i].y += bullets[i].vy * delta;
      bullets[i].x = wrapf(bullets[i].x, 0,4000);
      bullets[i].y = wrapf(bullets[i].y, 0,3000);
    }
  }
}

void update_asteroid(asteroid_t *ast, double delta) {
  ast->x += ast->vx * delta;
  ast->y += ast->vy * delta;
  ast->x = wrapf(ast->x, 0, 4000);
  ast->y = wrapf(ast->y, 0, 3000);
}

void line(int x0, int y0, int x1, int y1, const uint8_t shift) {
  x0 >>= shift;
  x1 >>= shift;
  y0 >>= shift;
  y1 >>= shift;

  int dx = abs(x1-x0), 
    sx = x0 < x1 ? 1 : -1; // The horizontal line direction
  int dy = abs(y1-y0), 
    sy = y0 < y1 ? 1 : -1; // The vertical line direction
  int err = (dx>dy ? dx : -dy) / 2, 
    e2;

  while (1) {
    analogWrite(dacpinX, x0 << shift);
    analogWrite(dacpinY, y0 << shift);

    if (x0 == x1 && y0 == y1) 
      break; // Exit loop once the end point of the line is reached

    e2 = err; // A temporary variable to store the value of err before it'll be
              // changed

    if (e2 > -dx) {
      err -= dy;
      x0 += sx;
    }

    if (e2 < dy) {
      err += dx;
      y0 += sy;
    }
  }
}

void drawBullet(int x, int y) {
  analogWrite(dacpinX, x);
  analogWrite(dacpinY, y);
  delayMicroseconds(100);
}

// 0 >= angle > 360
void rotate(int x, int y, int *xout, int *yout, int angle, int ox, int oy) {
  x -= ox; y -= oy;
  
  float sintheta = sintable[angle];
  float costheta = costable[angle];

  *xout = costheta * x - sintheta * y;
  *yout = sintheta * x + costheta * y;
  *xout += ox; *yout += oy;
}

void draw_glyph(int glyph_id, int x, int y) {
  int *glyph = &(allglyphs[glyph_starts[glyph_id]]);

  for (int i = 0; i < glyphlens[glyph_id]; i += 4) {
    line(x+glyph[i],y+glyph[i+1],x+glyph[i+2],y+glyph[i+3], 2);
  }
}

void draw_string(const char *s, int x, int y) {
  int xo = x;
  for (const char *cp = s; *cp; cp++) {
    draw_glyph(ascii2glyph[*cp], xo, y);
    xo += 380;
  }
}

void ship_shoot() {
  bullet_t new_bullet;
  new_bullet.present = true;
  new_bullet.x = shipx;
  new_bullet.y = shipy;
  new_bullet.vx = -sintable[((int)shiptheta) % 360] * 2000;
  new_bullet.vy = costable[((int)shiptheta) % 360] * 2000;
  new_bullet.creation_time = millis();

  int i;

  while ((i = find_free_bullet_index()) == -1) {
    bullets[find_oldest_bullet_index()].present = false;
  }

  bullets[i] = new_bullet;
}

void loop() {
  static unsigned long prev_micros = 0;
  static bool pinShootDown = false;
  static int state = ST_MAINMENU;

  unsigned long delta_micros = micros() - prev_micros; // The amount of microseconds the last frame took
  prev_micros = micros();
  double delta = delta_micros * 0.000001;

  if (state == ST_MAINMENU) {
    if (digitalRead(pinShoot) == LOW) {
      state = ST_INGAME;
      pinShootDown = true;
    }
  } else if (state == ST_INGAME) {
    update_bullets(delta);
    for (int i = 0; i < MAX_ASTEROIDS; i++) {
      update_asteroid(&(asteroids[i]), delta);
    }
    
    if (digitalRead(pinLeft) == LOW) {
      shiptheta += 0.02 * 300;
    }
    if (digitalRead(pinRight) == LOW) {
      shiptheta -= 0.02 * 300;
    }
    
    shiptheta = wrapf(shiptheta, 0, 359);
    
    if (digitalRead(pinHyper) == LOW) {
    }
    if (digitalRead(pinThrust) == LOW) {
      shipvx += -sintable[(int)shiptheta % 360] * 0.02 * 50;
      shipvy += costable[(int)shiptheta % 360] * 0.02 * 50;
    }
    if (digitalRead(pinShoot) == LOW) {
      if (!pinShootDown) {
        ship_shoot();
      }
      pinShootDown = true;
    } else {
      pinShootDown = false;
    }
    //digitalWrite(13, ledstate ? HIGH : LOW);
  
    shipvx *= 0.98;
    shipvy *= 0.98;
    shipx += shipvx;
    shipy += shipvy;
  
    shipx = wrapf(shipx, 0, 4000);
    shipy = wrapf(shipy, 0, 3000);
  }

  // Callibration box
  line(0,0,0,3000,4);
  line(0,3000,4000,3000,4);
  line(4000,3000,4000,0,4);
  line(4000,0,0,0,4);

  if (state == ST_MAINMENU) {
    draw_string("ASTEROIDS", 320, 2000);
    draw_string("PRESS", 320, 1100);
    draw_string("SHOOT", 320, 630);
  } else if (state == ST_INGAME) {
    for (int i = 0; i < sizeof(shippoints)/sizeof(int); i+=4) {
      int x0,y0,x1,y1;
      rotate(shippoints[i], shippoints[i+1], &x0, &y0, (int)shiptheta, 0, 0);
      rotate(shippoints[i+2], shippoints[i+3], &x1, &y1, (int)shiptheta, 0, 0);
  
      line(x0+shipx,y0+shipy,x1+shipx,y1+shipy, 1);
    }

    for (int i = 0; i < MAX_ASTEROIDS; i++) {
      if (asteroids[i].present) {
        draw_asteroid(&(asteroids[i]));
      }
    }
      
    for (int i = 0; i < MAX_BULLETS; i++) {
      drawBullet(bullets[i].x, bullets[i].y);
    }
  }

  // Idle beam to maintain frame rate
  analogWrite(dacpinX, 0);
  analogWrite(dacpinY, 0);
  delayMicroseconds(16700 - (micros() - prev_micros));
}

float wrapf(float x, float l, float r) {
  float ret = x;
  if (x < l) ret = r;
  if (x > r) ret = l;
  return ret;
}
