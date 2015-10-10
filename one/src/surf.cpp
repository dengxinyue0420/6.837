#include "surf.h"
#include "extra.h"
#include <math.h>

#define PI 3.14159265

using namespace std;

namespace
{
    
    // We're only implenting swept surfaces where the profile curve is
    // flat on the xy-plane.  This is a check function.
    static bool checkFlat(const Curve &profile)
    {
        for (unsigned i=0; i<profile.size(); i++)
            if (profile[i].V[2] != 0.0 ||
                profile[i].T[2] != 0.0 ||
                profile[i].N[2] != 0.0)
                return false;
    
        return true;
    }
}

Surface makeSurfRev(const Curve &profile, unsigned steps)
{
    Surface surface;
    
    if (!checkFlat(profile))
    {
        cerr << "surfRev profile curve must be flat on xy plane." << endl;
        exit(0);
    }
    double angle = 2*PI/steps;
    Matrix3f M =  Matrix3f((float)cos(angle),0,(float)sin(angle),
			   0,1,0,
			   (float)(-sin(angle)),0,(float)cos(angle));
    M.transpose();
    Curve c = profile;
    int numPoints = c.size();
    for(unsigned s=0;s<steps;s++){
      Curve newc;
      for (unsigned i=0;i<numPoints;i++){
	CurvePoint cp  = c[i];
	surface.VV.push_back(cp.V);
	surface.VN.push_back(-cp.N);
	Vector3f newV = M*cp.V;
	Vector3f newN = M*cp.N;
	newN.normalize();
	struct CurvePoint newP = {newV, cp.T,newN,cp.B};
	newc.push_back(newP);
      }
      c = newc;
      newc.clear();
    }

    int another;
    for(unsigned s=0;s<steps;s++){
      if(s==steps-1){
        another=0;
      }else{
	another = s+1;
      }
      for(unsigned i=0;i<numPoints-1;i++){
	surface.VF.push_back(Tup3u(s*numPoints+i,another*numPoints+i,another*numPoints+i+1));
	surface.VF.push_back(Tup3u(s*numPoints+i,another*numPoints+i+1,s*numPoints+i+1));
      }
    }
    return surface;
}
Matrix4f getTransform(CurvePoint p){
  Vector4f c1 = Vector4f(p.N,0);
  Vector4f c2 = Vector4f(p.B,0);
  Vector4f c3 = Vector4f(p.T,0);
  Vector4f c4 = Vector4f(p.V,1);
  return Matrix4f(c1,c2,c3,c4);
}

void pushVV(Surface &s, Curve c){
  for(unsigned i=0;i<c.size();i++){
    s.VV.push_back(c[i].V);
    s.VN.push_back(c[i].N);
  }
  return;
}

void addTriangle(Surface &s, Curve c1,Curve c2,int k){
  unsigned numP = c1.size();
  unsigned last = k*numP;
  for(unsigned i=0;i<numP-1;i++){
    s.VF.push_back(Tup3u(last+i,last+i+1,last+numP+i));
    s.VF.push_back(Tup3u(last+i+1,last+numP+i+1,last+numP+i));
  }
  return;
}
Surface makeGenCyl(const Curve &profile, const Curve &sweep )
{
    Surface surface;

    if (!checkFlat(profile))
    {
        cerr << "genCyl profile curve must be flat on xy plane." << endl;
        exit(0);
    }

    // TODO: Here you should build the surface.  See surf.h for details.
    Curve c = profile;
    Curve sweepL = sweep;
    unsigned step = sweep.size();
    Matrix4f transform;
    Matrix4f transinverse;
    Curve newc;
    vector<Curve> clist;
    for(unsigned i=0;i<step;i++){//sweepL.size();i++){
      CurvePoint p = sweepL[i];
      transform = getTransform(p);
      transinverse = transform.inverse();
      transinverse.transpose();
      newc.clear();
      for(unsigned j=0;j<c.size();j++){
	Vector4f tempV = transform*Vector4f(c[j].V,1);
	Vector4f tempN = transinverse*Vector4f(c[j].N,1);
	Vector3f newV = Vector3f(tempV[0],tempV[1],tempV[2]);
	Vector3f newN = Vector3f(-tempN[0],-tempN[1],-tempN[2]);
	struct CurvePoint newp = {newV,c[j].T,newN,c[j].B};
	newc.push_back(newp);
      }
      clist.push_back(newc);
    }
    for(unsigned k=0;k<clist.size()-1;k++){
      pushVV(surface,clist[k]);
      addTriangle(surface,clist[k],clist[k+1],k);
    }
    pushVV(surface,clist[clist.size()-1]);
    pushVV(surface,clist[0]);
    addTriangle(surface,clist[clist.size()-1],clist[0],clist.size()-1);
    return surface;
}

void drawSurface(const Surface &surface, bool shaded)
{
    // Save current state of OpenGL
    glPushAttrib(GL_ALL_ATTRIB_BITS);

    if (shaded)
    {
        // This will use the current material color and light
        // positions.  Just set these in drawScene();
        glEnable(GL_LIGHTING);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        // This tells openGL to *not* draw backwards-facing triangles.
        // This is more efficient, and in addition it will help you
        // make sure that your triangles are drawn in the right order.
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    }
    else
    {        
        glDisable(GL_LIGHTING);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        
        glColor4f(0.4f,0.4f,0.4f,1.f);
        glLineWidth(1);
    }

    glBegin(GL_TRIANGLES);
    for (unsigned i=0; i<surface.VF.size(); i++)
    {
        glNormal(surface.VN[surface.VF[i][0]]);
        glVertex(surface.VV[surface.VF[i][0]]);
        glNormal(surface.VN[surface.VF[i][1]]);
        glVertex(surface.VV[surface.VF[i][1]]);
        glNormal(surface.VN[surface.VF[i][2]]);
        glVertex(surface.VV[surface.VF[i][2]]);
    }
    glEnd();

    glPopAttrib();
}

void drawNormals(const Surface &surface, float len)
{
    // Save current state of OpenGL
    glPushAttrib(GL_ALL_ATTRIB_BITS);

    glDisable(GL_LIGHTING);
    glColor4f(0,1,1,1);
    glLineWidth(1);

    glBegin(GL_LINES);
    for (unsigned i=0; i<surface.VV.size(); i++)
    {
        glVertex(surface.VV[i]);
        glVertex(surface.VV[i] + surface.VN[i] * len);
    }
    glEnd();

    glPopAttrib();
}

void outputObjFile(ostream &out, const Surface &surface)
{
    
    for (unsigned i=0; i<surface.VV.size(); i++)
        out << "v  "
            << surface.VV[i][0] << " "
            << surface.VV[i][1] << " "
            << surface.VV[i][2] << endl;

    for (unsigned i=0; i<surface.VN.size(); i++)
        out << "vn "
            << surface.VN[i][0] << " "
            << surface.VN[i][1] << " "
            << surface.VN[i][2] << endl;

    out << "vt  0 0 0" << endl;
    
    for (unsigned i=0; i<surface.VF.size(); i++)
    {
        out << "f  ";
        for (unsigned j=0; j<3; j++)
        {
            unsigned a = surface.VF[i][j]+1;
            out << a << "/" << "1" << "/" << a << " ";
        }
        out << endl;
    }
}
