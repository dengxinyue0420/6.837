#include "SkeletalModel.h"

#include <FL/Fl.H>

using namespace std;

void SkeletalModel::load(const char *skeletonFile, const char *meshFile, const char *attachmentsFile)
{
	loadSkeleton(skeletonFile);

	m_mesh.load(meshFile);
	m_mesh.loadAttachments(attachmentsFile, m_joints.size());

	computeBindWorldToJointTransforms();
	updateCurrentJointToWorldTransforms();
}

void SkeletalModel::draw(Matrix4f cameraMatrix, bool skeletonVisible)
{
	// draw() gets called whenever a redraw is required
	// (after an update() occurs, when the camera moves, the window is resized, etc)

	m_matrixStack.clear();
	m_matrixStack.push(cameraMatrix);

	if( skeletonVisible )
	{
		drawJoints();

		drawSkeleton();
	}
	else
	{
		// Clear out any weird matrix we may have been using for drawing the bones and revert to the camera matrix.
		glLoadMatrixf(m_matrixStack.top());

		// Tell the mesh to draw itself.
		m_mesh.draw();
		m_matrixStack.pop();
	}
}

void SkeletalModel::loadSkeleton( const char* filename )
{
	// Load the skeleton from file here.
  fstream fs;
  fs.open(filename,fstream::in);
  string line;
  if(fs.is_open()){
    while(getline(fs, line)){
      stringstream ss(line);
      float x,y,z;
      int parent;
      ss>>x>>y>>z>>parent;
      Joint* joint = new Joint;
      joint->transform = Matrix4f::translation(x,y,z);
      if(parent==-1){
	m_rootJoint = joint;
	m_joints.push_back(joint);
      }else{
	if(parent<m_joints.size()){
	  Joint* parentJoint = m_joints[parent];
	  parentJoint->children.push_back(joint);
	  m_joints.push_back(joint);
	}else{
	  cerr<<"skeleton file wrong parent"<<endl;
	}
      }
    }
    fs.close();
  }
}

void drawNodeJoint(Joint* joint, MatrixStack& m_stack){
  if(joint->children.size()==0){
    m_stack.push(joint->transform);
    glLoadMatrixf(m_stack.top());
    glutSolidSphere(0.025f, 12, 12);
    m_stack.pop();
  }else{
    m_stack.push(joint->transform);
    for(int i=0;i<joint->children.size();i++){
      drawNodeJoint(joint->children[i],m_stack);
    }
    glLoadMatrixf(m_stack.top());
    glutSolidSphere(0.025f, 12, 12);
    m_stack.pop();
  }
}

void SkeletalModel::drawJoints( )
{
	// Draw a sphere at each joint. You will need to add a recursive helper function to traverse the joint hierarchy.
	//
	// We recommend using glutSolidSphere( 0.025f, 12, 12 )
	// to draw a sphere of reasonable size.
	//
	// You are *not* permitted to use the OpenGL matrix stack commands
	// (glPushMatrix, glPopMatrix, glMultMatrix).
	// You should use your MatrixStack class
	// and use glLoadMatrix() before your drawing call.
  drawNodeJoint(m_rootJoint, m_matrixStack);
}

void drawJointBone(Joint* joint, MatrixStack& m_stack){
  m_stack.push(joint->transform);
  if(joint->children.size()!=0){
    for(int i=0;i<joint->children.size();i++){
      Joint* child = joint->children[i];
      Vector3f offset = child->transform.getCol(3).xyz();
      float l = offset.abs();
      Matrix4f T = Matrix4f::translation(0,0,0.5);
      Matrix4f S = Matrix4f::scaling(0.025f,0.025f,l);
      Matrix4f R;
      if(l!=0){
	Vector3f z = offset.normalized();
	Vector3f normal = Vector3f::cross(Vector3f(0,0,1),z);
	R = Matrix4f::rotation(normal,acos(z.z()));
      }else{
	R = Matrix4f::identity();
      }
      Matrix4f boxTrans = R*S*T;
      //boxTrans.print();
      m_stack.push(boxTrans);
      glLoadMatrixf(m_stack.top());
      glutSolidCube(1.0f);
      m_stack.pop();
      drawJointBone(child,m_stack);
    }
  }
  m_stack.pop();
}

void SkeletalModel::drawSkeleton( )
{
	// Draw boxes between the joints. You will need to add a recursive helper function to traverse the joint hierarchy.
  drawJointBone(m_rootJoint,m_matrixStack);
}

void SkeletalModel::setJointTransform(int jointIndex, float rX, float rY, float rZ)
{
	// Set the rotation part of the joint's transformation matrix based on the passed in Euler angles.
  Joint* joint = m_joints[jointIndex];
  Matrix4f xrot = Matrix4f::rotateX(rX);
  Matrix4f yrot = Matrix4f::rotateY(rY);
  Matrix4f zrot = Matrix4f::rotateZ(rZ);
  Matrix4f rotation = xrot*yrot*zrot;
  Matrix4f newT = joint->transform;
  newT.setSubmatrix3x3(0,0,rotation.getSubmatrix3x3(0,0));
  joint->transform = newT;
}

void computeWorldtoJoint(Joint* joint, MatrixStack m_stack){
  m_stack.push(joint->transform.inverse());
  if(joint->children.size()==0){
    joint->bindWorldToJointTransform = m_stack.top();
    m_stack.pop();
  }else{
    for(int i=0;i<joint->children.size();i++){
      computeWorldtoJoint(joint->children[i],m_stack);
    }
    joint->bindWorldToJointTransform=m_stack.top();
    m_stack.pop();
  }

  //joint->bindWorldToJointTransform.print();
}
void SkeletalModel::computeBindWorldToJointTransforms()
{
	// 2.3.1. Implement this method to compute a per-joint transform from
	// world-space to joint space in the BIND POSE.
	//
	// Note that this needs to be computed only once since there is only
	// a single bind pose.
	//
	// This method should update each joint's bindWorldToJointTransform.
	// You will need to add a recursive helper function to traverse the joint hierarchy.
  computeWorldtoJoint(m_rootJoint,m_matrixStack);
}

void computeJointToWorld(Joint* joint, MatrixStack m_stack){
  m_stack.push(joint->transform);
  if(joint->children.size()==0){
    joint->currentJointToWorldTransform = m_stack.top();
    m_stack.pop();
  }else{
    for(int i=0;i<joint->children.size();i++){
      computeJointToWorld(joint->children[i],m_stack);
    }
    joint->currentJointToWorldTransform=m_stack.top();
    m_stack.pop();
  }
}

void SkeletalModel::updateCurrentJointToWorldTransforms()
{
	// 2.3.2. Implement this method to compute a per-joint transform from
	// joint space to world space in the CURRENT POSE.
	//
	// The current pose is defined by the rotations you've applied to the
	// joints and hence needs to be *updated* every time the joint angles change.
	//
	// This method should update each joint's currentJointToWorldTransform.
	// You will need to add a recursive helper function to traverse the joint hierarchy.
  computeJointToWorld(m_rootJoint,m_matrixStack);
  /*
  for(int j=0;j<m_joints.size();j++){
    Joint* joint = m_joints[j];
    Matrix4f res = joint->bindWorldToJointTransform*joint->currentJointToWorldTransform;
    res.print();
    joint->bindWorldToJointTransform.print();
    cout<<endl;
    joint->currentJointToWorldTransform.print();
    cout<<endl;
  }
  */
}

void SkeletalModel::updateMesh()
{
	// 2.3.2. This is the core of SSD.
	// Implement this method to update the vertices of the mesh
	// given the current state of the skeleton.
	// You will need both the bind pose world --> joint transforms.
	// and the current joint --> world transforms.
  for(int i=0;i<m_mesh.currentVertices.size();i++){
    vector<float> weight = m_mesh.attachments[i];
    Vector3f current = m_mesh.bindVertices[i];
    Vector4f newV = Vector4f(0,0,0,0);
    for(int j=0;j<weight.size();j++){
      Joint* joint = m_joints[j];
      Vector4f step = joint->currentJointToWorldTransform*joint->bindWorldToJointTransform*Vector4f(current,1);
      newV = newV+weight[j]*step;
    }
    m_mesh.currentVertices[i] = Vector3f(newV[0],newV[1],newV[2]);
  }
  //m_mesh.currentVertices[0].print();
}

