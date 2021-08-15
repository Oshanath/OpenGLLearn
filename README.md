# OpenGLLearn

####Very basic C++ graphics engine using modern OpenGL (3.3 core).

##Dependencies - 
  glad
  glfw
  glm
  nlohmann json
  stb_image
  
####All dependencies are included along with the configured visual studio solution.

##Features - 
  Cross platform window creation
  gltf 2.0 model loading with a single line
  Supports multiple objects and multiple light sources in a single scene
  Abstracted using OOP
  Basic Phong shading with 3 light types (spot lights, direct lights and point lights)
  Lights can be any color
  A single model supports one  diffuse map and one specular map
  No need to make direct OpenGL API calls
  8 sample models. More can be downloaded and converted to gltf 2.0 seperate format using Blender
  
##How to use

###Only edit the addModelsAndLights() functions in the main.cpp file. Don't edit anything else.

####Importing a model

To import a model, it needs to be in gltf 2.0 format, and the binary file, textures and the .gltf file need to be seperate.
If your model do not fulfill these requirements, please downlaod Blender and convert it into gltf 2.0 seperate format.

Create a model object in the heap.
```
Model* crate = new Model("models/crate/crate.gltf");
```
The argument of the above function is the path of the gltf file relative to the solution directory.
Tranlate, rotate and scale the created object accordingly.
```
crate->translate(0.0f, 1.0f, 0.0f);
crate->scale(0.05f);
crate->rotate(1.0f, 0.0f, 0.5f);
```

Only uniform scaling is allowed.
For rotation, the individual euler rotation angles should be passed as arguments. (x, y and z axes. Roll, yaw and pitch not in order)

Add the created model to the models object.
```
models.push_back(crate);
```

####Creating a light source
All light sources need an internal model to render. If a model is not used for a light source. Create a model object in the heap as usual but with "" as the arguement.

```
Model* cube = new Model("models/cube/cube.gltf"); // Non empty model
Model* cube = new Model(""); // empty model
```
This model can also be translated, rotated and scaled just like a typical model.

Create a new LightSource object in the heap
```
LightSource* cubeLight = new LightSource(*cube, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), POINT_LIGHT);
```
Constructor arguments -
  argument 1 - A pointer to the model corresponding to the light source
  argument 2 - Light source color. (Color of the light. Not the model)
  argument 3 - Light type. This is a value from the enum LightTyoe which is as follows
  
```
enum LightType {
	DIRECT_LIGHT = 0,
	POINT_LIGHT = 1,
	SPOT_LIGHT = 2
};
```

Values for the enum are assigned manually for GPU uniform purposes.

DIRECT_LIGHT - Parallel light beams, such as from the sun or the moon. The direction of the light is the vector pointing from the lightSource
object to the origin of the plane. Light intensity not yet implemented.

POINT_LIGHT - A light emerging from a point that attenuates over distance. The linear and the quadratic terms regarding the attenuation should be set. 
The default values are linear - 0.14f and quadratic - 0.07f. The quadratic term controls the maximum distance the light travels. The linear term dictates
the intensity of the light closer to the source. (This is an oversimplification. Actual values should be experimental. They depend on the context and the
surroundings). 
```
cubeLight->linear = 0.01;
cubeLight->quadratic = 0.01;
```

SPOT_LIGHT - A spot light that attenuated over distance. 3 additional values should be provided if you are using a spot light. The direction,
the inner cutoff and the outer cutoff. The direction is the direction in which the spot light is pointed at. The spot light designated two areas in the surfaces.
The inner and the outer circles. All the fragments in the inner circle are fully lighted. From the circumference of the inner circle to the outer circle,
the light intensity value interpolated from 1.0 to 0.0. After that, the intensity is 0. You should provide the angle of the inner cone and the outer cone in degrees.
Both cones are formed with the light source as the point and the light circle as the base.

```
cubeLight->innerCutoffDegrees = 10.0f;
cubeLight->innerCutoffDegrees = 30.0f;
```

Add the light source to the std::vector of lightSources.
```
lightSources.push_back(cubeLight);
```

And that's it! Build the program and play around with the values and models.
