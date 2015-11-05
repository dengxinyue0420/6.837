#include "Renderer.h"

#include "Image.h"
#include "Camera.h"
#include "Ray.h"
#include "Hit.h"

Renderer::Renderer(const std::string &sceneFilename):
  _sp(sceneFilename)
{
}

Renderer::~Renderer()
{
  // TODO: free up resources
  //  if(&_sp){
  // delete &_sp;
  //}
}

void
Renderer::Render(int width,
                 int height,
                 const std::string &outputFilename,
                 float minDepth,
                 float maxDepth,
                 const std::string &depthFilename,
                 const std::string &normalFilename)
{
    // TODO: implement

    // Loop over each pixel in the image, shooting a ray
    // through that pixel and finding its intersection with
    // the scene. Write the color at the intersection to that
    // pixel in your output image.
    //
    // Use the Image class to write out the requested output files.
  float x_step = 2.0/width;
  float y_step = 2.0/height;
  
  Camera * cam = this->_sp.getCamera();
  Group * group = this->_sp.getGroup();
  Image outputF = Image(width,height);
  Image depthF = Image(width,height);
  Image normalF = Image(width,height);
  for(int i=0;i<width;i++){
    for(int j=0;j<height;j++){
      Ray r = cam->generateRay(Vector2f(-1+i*x_step, -1+j*y_step));
      Hit h = Hit();
      if(group->intersect(r,cam->getTMin(),h)){
	outputF.setPixel(i,j,0.2*Vector3f(1,1,1));
	float t = h.getT();
	//std::cout<<t<<std::endl;
	if(t>=minDepth&&t<=maxDepth){
	  float level = (maxDepth-t)/(maxDepth-minDepth);
	  //std::cout<<level<<std::endl;
	  depthF.setPixel(i,j,level*Vector3f(1,1,1));
	}else{
	  depthF.setPixel(i,j,Vector3f(1,1,1));
	}
      }
    }
  }
  outputF.savePNG(outputFilename);
  if(&depthFilename!=NULL){
    depthF.savePNG(depthFilename);
  }
}
