#include "ClothSystem.h"

#define m 0.01f
#define g 10.0f
#define kf 0.1f

#define ks_struct 2.0f
#define ks_shear 2.0f
#define ks_flex 2.0f

#define r_struct 0.5f
#define r_shear 0.7f
#define r_flex 1.0f

//TODO: Initialize here
ClothSystem::ClothSystem(int size)
{
  this->size = size;
  this->render = false;
  this->move = false;
  this->backward = true;
  for(int i=0; i<size;i++){
    for(int j=0; j<size;j++){
      Vector3f pos = Vector3f(j*0.5,0,-i*0.5);
      Vector3f v = Vector3f(0,0,0);
      this->m_vVecState.push_back(pos);
      this->m_vVecState.push_back(v);
    }
  }
  this->staticPoints.push_back(getIndex(0,0)*2);
  this->staticPoints.push_back(getIndex(0,size-1)*2);
}    

int ClothSystem::getIndex(int row,int col){
  return row*this->size+col;
}
Vector3f ClothSystem::getPos(int row, int col, vector<Vector3f> state){
  return state[getIndex(row,col)*2];
}
Vector3f ClothSystem::getVel(int row, int col, vector<Vector3f> state){
  return state[getIndex(row,col)*2+1];
}

Vector3f ClothSystem::G(){
  return m*Vector3f(0,-g,0);
}
Vector3f ClothSystem::D(Vector3f v){
  return -kf*v;
}
Vector3f ClothSystem::S(char type, int row1, int col1, int row2, int col2){
  if(row1<0||row1>=this->size||row2<0||row2>=this->size||
     col1<0||col1>=this->size||col2<0||col2>=this->size){
    return Vector3f::ZERO;
  }
  Vector3f p1 = getPos(row1,col1, this->getState());
  Vector3f p2 = getPos(row2,col2, this->getState());
  if(type=='s'){
    return -ks_struct*((p1-p2).abs()-r_struct)*((p1-p2).normalized());
  }else if(type=='h'){
    return -ks_shear*((p1-p2).abs()-r_shear)*((p1-p2).normalized());
  }else if(type=='f'){
    return -ks_flex*((p1-p2).abs()-r_flex)*((p1-p2).normalized());
  }else{
    return Vector3f::ZERO;
  }
}
Vector3f ClothSystem::getForce(int row,int col, vector<Vector3f> state){
  Vector3f v = getVel(row,col, state);
  Vector3f spring = Vector3f::ZERO;
  //structual spring
  spring+=S('s',row,col,row-1,col)+S('s',row,col,row+1,col)+S('s',row,col,row,col-1)+S('s',row,col,row,col+1);
  //shear spring
  spring+=S('h',row,col,row-1,col-1)+S('h',row,col,row-1,col+1)+S('h',row,col,row+1,col-1)+S('h',row,col,row+1,col+1);
  //flex spring
  spring+=S('f',row,col,row-2,col)+S('f',row,col,row+2,col)+S('f',row,col,row,col-2)+S('f',row,col,row,col+2);
  return G()+D(v)+spring;
}

Vector3f ClothSystem::getMoveDir(Vector3f pos){
  if(pos.z()<-5){
    this->backward = false;
    return Vector3f(0,0,1);
  }else if(pos.z()>=0){
    this->backward =true;
    return Vector3f(0,0,-1);
  }else{
    if(backward){
      return Vector3f(0,0,-1);
    }else{
      return Vector3f(0,0,1);
    }
  }
}
// TODO: implement evalF
// for a given state, evaluate f(X,t)
vector<Vector3f> ClothSystem::evalF(vector<Vector3f> state)
{
  vector<Vector3f> f;
  for(int i=0;i<this->size;i++){
    for(int j=0;j<this->size;j++){
      f.push_back(getVel(i,j, state));
      f.push_back(getForce(i,j, state)/m);
    }
  }
  for(int i=0;i<this->staticPoints.size();i++){
    int index = this->staticPoints[i];
    if(move){
      f[index]=getMoveDir(state[index]);
    }else{
      f[index]=Vector3f::ZERO;
    }
    f[index+1]=Vector3f::ZERO;
  }
  return f;
}

void ClothSystem::drawLine(int row1, int col1, int row2,int col2){
  if(row1<0||row1>=this->size||row2<0||row2>=this->size||
     col1<0||col1>=this->size||col2<0||col2>=this->size){
    return;
  }
  Vector3f p1 = getPos(row1,col1, this->getState());
  Vector3f p2 = getPos(row2,col2, this->getState());
  glLineWidth(2.5);
  glBegin(GL_LINES);
  glVertex3f(p1[0], p1[1], p1[2]);glVertex3f(p2[0], p2[1], p2[2]);
  glEnd();
}

void ClothSystem::toggleRender(){
  this->render = !this->render;
}
void ClothSystem::toggleMove(){
  this->move = !this->move;
}

void ClothSystem::drawCloth(int row, int col){
  vector<Vector3f> current = this->getState();
  Vector3f p1 = getPos(row,col,current);
  Vector3f p2 = getPos(row,col+1,current);
  Vector3f p3 = getPos(row+1,col,current);
  Vector3f p4 = getPos(row+1,col+1,current);
  Vector3f normal1 = Vector3f::cross(p3-p1,p2-p1).normalized();
  Vector3f normal2 = Vector3f::cross(p2-p3,p1-p3).normalized();
  Vector3f normal3 = Vector3f::cross(p1-p2,p3-p2).normalized();
  Vector3f normal4 = Vector3f::cross(p3-p2,p4-p2).normalized();
  Vector3f normal5 = Vector3f::cross(p4-p3,p2-p3).normalized();
  Vector3f normal6 = Vector3f::cross(p2-p4,p3-p4).normalized();
  glBegin(GL_TRIANGLES);
  glNormal(normal1);
  glVertex(p1);
  glNormal(normal2);
  glVertex(p3);
  glNormal(normal3);
  glVertex(p2);
  glEnd();
  glBegin(GL_TRIANGLES);
  glNormal(normal4);
  glVertex(p2);
  glNormal(normal5);
  glVertex(p3);
  glNormal(normal6);
  glVertex(p4);
  glEnd();
}
///TODO: render the system (ie draw the particles)
void ClothSystem::draw()
{
  if(render){
    for(int i=0;i<this->size-1;i++){
      for(int j=0;j<this->size-1;j++){
	drawCloth(i,j);
      }
    }
  }else{
    for(int i=0;i<this->size;i++){
      for(int j=0;j<this->size;j++){
	Vector3f pos = getPos(i,j, this->getState());
	glPushMatrix();
	glTranslatef(pos[0],pos[1],pos[2]);
	glutSolidSphere(0.075f,10.0f,10.0f);
	glPopMatrix();
	drawLine(i,j,i-1,j);
	drawLine(i,j,i+1,j);
	drawLine(i,j,i,j-1);
	drawLine(i,j,i,j+1);
      }
    }
  }
}

