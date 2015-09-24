#include "curve.h"
#include "extra.h"
using namespace std;

namespace
{
    // Approximately equal to.  We don't want to use == because of
    // precision issues with floating point.
    inline bool approx( const Vector3f& lhs, const Vector3f& rhs )
    {
        const float eps = 1e-8f;
        return ( lhs - rhs ).absSquared() < eps;
    }

    
}

Vector4f monobasis(float t){
  return Vector4f(1,t,pow(t,2),pow(t,3));
}

Vector4f monobasisDeriv(float t){
  return Vector4f(0,1,2*t,3*pow(t,2));
}

Vector3f computeVector(Vector4f basis, Vector4f x, Vector4f y, Vector4f z){
  float newx = Vector4f::dot(basis,x);
  float newy = Vector4f::dot(basis,y);
  float newz = Vector4f::dot(basis,z);
  return Vector3f(newx,newy,newz);
}

Curve evalBezier( const vector< Vector3f >& P, unsigned steps )
{
    // Check
    if( P.size() < 4 || P.size() % 3 != 1 )
    {
        cerr << "evalBezier must be called with 3n+1 control points." << endl;
        exit( 0 );
    }

    // TODO:
    // You should implement this function so that it returns a Curve
    // (e.g., a vector< CurvePoint >).  The variable "steps" tells you
    // the number of points to generate on each piece of the spline.
    // At least, that's how the sample solution is implemented and how
    // the SWP files are written.  But you are free to interpret this
    // variable however you want, so long as you can control the
    // "resolution" of the discretized spline curve with it.

    // Make sure that this function computes all the appropriate
    // Vector3fs for each CurvePoint: V,T,N,B.
    // [NBT] should be unit and orthogonal.

    // Also note that you may assume that all Bezier curves that you
    // receive have G1 continuity.  Otherwise, the TNB will not be
    // be defined at points where this does not hold.
    Matrix4f BezierBasis = Matrix4f(1,-3,3,-1,
				    0,3,-6,3,
				    0,0,3,-3,
				    0,0,0,1);
    Curve c;
    float deltaT = 1.0/steps;
    Vector4f x,y,z,bb,bbderi;
    Vector3f V,B,N,T;
    float newx,newy,newz ;
    float derivx,derivy,derivz;

    for(unsigned i =3;i<P.size();i=i+3){
      x = Vector4f(P[i-3][0],P[i-2][0],P[i-1][0],P[i][0]);
      y = Vector4f(P[i-3][1],P[i-2][1],P[i-1][1],P[i][1]);
      z = Vector4f(P[i-3][2],P[i-2][2],P[i-1][2],P[i][2]);
      
      B = Vector3f(0,0,1);
      T = P[i-2]-P[i-3];
      N = Vector3f::cross(B,T);
      
      if(N!=Vector3f::ZERO){
	T.normalize();
	N.normalize();
	B.normalize();
	struct CurvePoint start = {P[i-3],T,N,B};
	c.push_back(start);
      }else{
	B = Vector3f(0,1,0);
	N = Vector3f::cross(B,T);
	T.normalize();
	N.normalize();
	B.normalize();
        struct CurvePoint start = {P[i-3],T,N,B};
	c.push_back(start);
      }
      for(unsigned s=1;s<=steps;s++){
	bb = BezierBasis*monobasis(s*deltaT);
	bbderi = BezierBasis*monobasisDeriv(s*deltaT);
	V = computeVector(bb,x,y,z);
	T = computeVector(bbderi,x,y,z);
	N = Vector3f::cross(B,T);
	B = Vector3f::cross(T,N);
	T.normalize();
	N.normalize();
	B.normalize();
	struct CurvePoint current = {V,T,N,B};
	c.push_back(current);
      }
    }
    // Right now this will just return this empty curve.
    return c;
}

Curve evalBspline( const vector< Vector3f >& P, unsigned steps )
{
    // Check
    if( P.size() < 4 )
     {
        cerr << "evalBspline must be called with 4 or more control points." << endl;
        exit( 0 );
    }

    // TODO:
    // It is suggested that you implement this function by changing
    // basis from B-spline to Bezier.  That way, you can just call
    // your evalBezier function.
    Matrix4f BsplineBasis = Matrix4f(1,-3,3,-1,
				    4,0,-6,3,
				    1,3,3,-3,
				    0,0,0,1);
    BsplineBasis /=6.0f;
    Curve c;
    float deltaT = 1.0/steps;
    Vector4f x,y,z,bb,bbderi;
    Vector3f V,B,N,T;
    float newx,newy,newz ;
    float derivx,derivy,derivz;

    for(unsigned i =3;i<P.size();i=i+1){
      x = Vector4f(P[i-3][0],P[i-2][0],P[i-1][0],P[i][0]);
      y = Vector4f(P[i-3][1],P[i-2][1],P[i-1][1],P[i][1]);
      z = Vector4f(P[i-3][2],P[i-2][2],P[i-1][2],P[i][2]);
      
      B = Vector3f(0,0,1);
      T = computeVector(BsplineBasis*monobasis(0),x,y,z);
      if(Vector3f::cross(B,T)==Vector3f::ZERO){
	B = Vector3f(0,1,0);
      }
      for(unsigned s=0;s<=steps;s++){
	bb = BsplineBasis*monobasis(s*deltaT);
	bbderi = BsplineBasis*monobasisDeriv(s*deltaT);
	V = computeVector(bb,x,y,z);
	T = computeVector(bbderi,x,y,z);
	N = Vector3f::cross(B,T);
	B = Vector3f::cross(T,N);
	T.normalize();
	N.normalize();
	B.normalize();
	
	//V.print();
	//N.print();
	//B.print();
	struct CurvePoint current = {V,T,N,B};
	c.push_back(current);
      }
    }
    // Right now this will just return this empty curve.
    return c;
}

Curve evalCircle( float radius, unsigned steps )
{
    // This is a sample function on how to properly initialize a Curve
    // (which is a vector< CurvePoint >).
    
    // Preallocate a curve with steps+1 CurvePoints
    Curve R( steps+1 );

    // Fill it in counterclockwise
    for( unsigned i = 0; i <= steps; ++i )
    {
        // step from 0 to 2pi
        float t = 2.0f * M_PI * float( i ) / steps;

        // Initialize position
        // We're pivoting counterclockwise around the y-axis
        R[i].V = radius * Vector3f( cos(t), sin(t), 0 );
        
        // Tangent vector is first derivative
        R[i].T = Vector3f( -sin(t), cos(t), 0 );
        
        // Normal vector is second derivative
        R[i].N = Vector3f( -cos(t), -sin(t), 0 );

        // Finally, binormal is facing up.
        R[i].B = Vector3f( 0, 0, 1 );
    }

    return R;
}

void drawCurve( const Curve& curve, float framesize )
{
    // Save current state of OpenGL
    glPushAttrib( GL_ALL_ATTRIB_BITS );

    // Setup for line drawing
    glDisable( GL_LIGHTING ); 
    glColor4f( 1, 1, 1, 1 );
    glLineWidth( 1 );
    
    // Draw curve
    glBegin( GL_LINE_STRIP );
    for( unsigned i = 0; i < curve.size(); ++i )
    {
        glVertex( curve[ i ].V );
    }
    glEnd();

    glLineWidth( 1 );

    // Draw coordinate frames if framesize nonzero
    if( framesize != 0.0f )
    {
        Matrix4f M;

        for( unsigned i = 0; i < curve.size(); ++i )
        {
            M.setCol( 0, Vector4f( curve[i].N, 0 ) );
            M.setCol( 1, Vector4f( curve[i].B, 0 ) );
            M.setCol( 2, Vector4f( curve[i].T, 0 ) );
            M.setCol( 3, Vector4f( curve[i].V, 1 ) );

            glPushMatrix();
            glMultMatrixf( M );
            glScaled( framesize, framesize, framesize );
            glBegin( GL_LINES );
            glColor3f( 1, 0, 0 ); glVertex3d( 0, 0, 0 ); glVertex3d( 1, 0, 0 );
            glColor3f( 0, 1, 0 ); glVertex3d( 0, 0, 0 ); glVertex3d( 0, 1, 0 );
            glColor3f( 0, 0, 1 ); glVertex3d( 0, 0, 0 ); glVertex3d( 0, 0, 1 );
            glEnd();
            glPopMatrix();
        }
    }
    
    // Pop state
    glPopAttrib();
}

