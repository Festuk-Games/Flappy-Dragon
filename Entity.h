#pragma once
class Entity
{
public:
	Entity();
	~Entity();

	void Init(int posx, int posy, int w, int h, int s);
	void GetRect(int *posx, int *posy, int *w, int *h);
	void SetX(int posx);
	void SetY(int posy);
	int  GetX();
	int  GetWidth();
	void ShutDown(); 
	bool IsAlive();
	void Move(int dx, int dy);
	void MoveC(int dx, int dy);

private:
	int x, y;
	int width, height;
	int speed = 1;
	int speedc = 1;
	bool is_alive;
};

