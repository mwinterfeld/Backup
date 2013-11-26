#ifndef PLAYER_H_
#define PLAYER_H_

class Player
{
public:
	Player() {pos = new float[3]; pos[0] = 5; pos[1] = 5; pos[2] = 0; 
				s = 0.1, h = 1.0; w = 1.0; d = 1.0;}
	~Player() { delete [] pos;}

	float getx() {return pos[0];}
	float gety() {return pos[1];}
	float getz() {return pos[2];}
	float speed() {return s;}
	float height() {return h;}
	float width() {return w;}
	float depth() {return d;}
	
	void setx(float x) {pos[0] = x;}
	void sety(float y) {pos[1] = y;}
	void setz(float z) {pos[2] = z;}
	void setpos(float newpos[]) {pos[0] = newpos[0]; pos[1] = newpos[1]; pos[2] = newpos[2];}
	void setheight(float he) {h = he;}
	void setwidth(float wi) {w = wi;}
	void setdepth(float di) {d = di;}

private:
	float* pos;
	float s;
	float h, w, d;
};

#endif