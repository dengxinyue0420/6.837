#include <cstring>
#include <iostream>
#include <cstdlib>
#include "Renderer.h"

int
main(int argc, const char **argv)
{
    // Report help usage if no args specified.
    if (argc == 1) {
        std::cout << "Usage: a4 "
            << "-input <scene> -size <width> <height> -output <image.png> -depth <depth_min> <depth_max> <depth_image.png> [-normals <normals_image.png>]\n";
        return 1;
    }

    std::string sceneFilename;
    int width = 0;
    int height = 0;
    std::string outputFilename;
    std::string depthFilename;
    float minDepth = 0.0f;
    float maxDepth = 0.0f;
    std::string normalFilename;

    // Fill in your implementation here.
    // Parse arguments.
    int i = 1;
    while(i<argc){
      if(!strcmp(argv[i], "-input")){
	sceneFilename = argv[i+1];
	i+=2;
      }else if(!strcmp(argv[i],"-size")){
	width = std::atoi(argv[i+1]);
	height = std::atoi(argv[i+2]);
	i+=3;
      }else if(!strcmp(argv[i],"-output")){
	outputFilename = argv[i+1];
	i+=2;
      }else if(!strcmp(argv[i],"-depth")){
	minDepth = (float)std::atof(argv[i+1]);
	maxDepth = (float)std::atof(argv[i+2]);
	depthFilename = argv[i+3];
	i+=4;
      }else if(!strcmp(argv[i],"-normals")){
	normalFilename = argv[i+1];
	i+=2;
      }
    }
    // This loop loops over each of the input arguments.
    // argNum is initialized to 1 because the first
    // "argument" provided to the program is actually the
    // name of the executable (in our case, "a4").
    for (int argNum = 1; argNum < argc; ++argNum) {
        std::cout 
            << "Argument " << argNum 
            << " is: " << argv[argNum] << std::endl;
    }

    Renderer renderer(sceneFilename);
    renderer.Render(width, height, 
                    outputFilename,
                    minDepth, maxDepth,
                    depthFilename, 
                    normalFilename);

    return 0;
}
