#ifndef CLOTHSYSTEM_H
#define CLOTHSYSTEM_H

#include "extra.h"
#include <vector>
#include <iostream>
#include "particleSystem.h"

class ClothSystem: public ParticleSystem
{
///ADD MORE FUNCTION AND FIELDS HERE
public:
	ClothSystem(int size);
	vector<Vector3f> evalF(vector<Vector3f> state);
	void draw();
	void toggleRender();
	void toggleMove();
private:
	int size;
	bool render;
	bool move;
	bool backward;
	vector<int> staticPoints;
	int getIndex(int row,int col);
	Vector3f getPos(int row,int col, vector<Vector3f> state);
	Vector3f getVel(int row,int col, vector<Vector3f> state);
	Vector3f G();
	Vector3f D(Vector3f v);
	Vector3f S(char type, int row1, int col1, int row2, int col2);
	Vector3f getForce(int row, int col, vector<Vector3f> state);
	Vector3f getMoveDir(Vector3f pos);
	void drawLine(int row1,int row2, int col1, int col2);
	void drawCloth(int row, int col);
};


#endif
