#include "Mesh.h"

using namespace std;

//parse faces into vectors with 9 elements
void Mesh::load( const char* filename )
{
	// 2.1.1. load() should populate bindVertices, currentVertices, and faces
  fstream fs;
  fs.open(filename,fstream::in);
  string line;
  if(fs.is_open()){
    while(getline(fs,line)){
      stringstream ss(line);
      Vector3f v;
      string s;
      ss>>s;
      if(s=="v"){
	ss>>v[0]>>v[1]>>v[2];
	bindVertices.push_back(v);
      }else if(s=="f"){
	Tuple3u vf;
        ss>>vf[0]>>vf[1]>>vf[2];
	faces.push_back(vf);
      }else{}
    }
    fs.close();
  }

	// make a copy of the bind vertices as the current vertices
  currentVertices = bindVertices;
}

void Mesh::draw()
{
	// Since these meshes don't have normals
	// be sure to generate a normal per triangle.
	// Notice that since we have per-triangle normals
	// rather than the analytical normals from
	// assignment 1, the appearance is "faceted".
  
  for (unsigned i=0; i<faces.size(); i++){   
    Tuple3u face = faces[i];
    Vector3f first = currentVertices[face[0]-1];
    Vector3f second = currentVertices[face[1]-1];
    Vector3f third = currentVertices[face[2]-1];
    Vector3f normal1 = Vector3f::cross(second-first,third-first);
    Vector3f normal2 = Vector3f::cross(third-second,first-second);
    Vector3f normal3 = Vector3f::cross(first-third,second-third);
    normal1.normalize();
    normal2.normalize();
    normal3.normalize();
    glBegin(GL_TRIANGLES);
    glNormal(normal1);
    glVertex(first);
    glNormal(normal2);
    glVertex(second);
    glNormal(normal3);
    glVertex(third);
    glEnd();
  }
  
}

void Mesh::loadAttachments( const char* filename, int numJoints )
{
	// 2.2. Implement this method to load the per-vertex attachment weights
	// this method should update m_mesh.attachments
  fstream fs;
  fs.open(filename,fstream::in);
  string line;
  if(fs.is_open()){
    while(getline(fs,line)){
      stringstream ss(line);
      vector<float> weight;
      weight.push_back(0);
      for(int i=0;i<numJoints-1;i++){
	float w;
	ss>>w;
	weight.push_back(w);
      }
      attachments.push_back(weight);
    }
    fs.close();
  }
}
