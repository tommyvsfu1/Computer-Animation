class vector{
float x,y;
vector(float a, float b) {
  x = a;
  y = b;
} 
};
float map_x;
float map_y;
vector v1 = new vector(0.0,0.0);
vector v2 = new vector(0.0,0.0);
void setup() {
 size(640,640);
 frameRate(60);
 map_x = 200;
 map_y = 0.0;
 v1.x=0;
 v1.y=0;
 v2.x=0;
 v2.y=0;
}

void draw() {
 float time_step = 1.0/60.0;
 float gravity = 9.8;
 vector v_tmp = new vector(0,0);
 background(51);
 fill(102);
 stroke(255);

 float term1 = (map_x*v1.x+map_y*v1.y)/(map_x*map_x+map_y*map_y);
 float term2 = ((9.8*map_y)/(map_x*map_x+map_y*map_y)) * time_step;

 v_tmp.x = term1*map_x + term2 * map_x;

 v_tmp.y = term1*map_y + term2 * map_y - 9.8 * time_step;

 v2.x = v1.x - v_tmp.x;
 v2.y = v1.y - v_tmp.y;
 map_x = map_x + time_step * v2.x;
 map_y = map_y + time_step * v2.y;
 v1.x = v2.x;
 v1.y = v2.y;
 ellipse(map_x+width/2,map_y,32,32);
 line(width/2,0,map_x+width/2,map_y);
}
