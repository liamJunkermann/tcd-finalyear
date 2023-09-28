Links: [[CSU44052 Computer Graphics Lectures]]
Tags: #LectureNote 
___
# Lecture 2
## Rendering: Lighting
- Photorealism vs Physically-based realism
	- Make it look real vs making sure light is interacting appropriately
	- Cheaper but slightly less realistic vs more expensive but more realistic
- Rendering is determining the appropriate colour to assign to a pixel
- Colour depends on
	- Geometry
	- Position, geometry, and colour of light sources (*luminaiares*)
	- position and response of viewer
	- Surface reflectance properties of the object at that point
	- scattering by any participating media (eg. smoke, rising hot air)
### Rendering Algorithms
> Local, Global, View Dependant, View Independent
- **Local illumination** algorithms: consider lighting only form the light sources and ignores the effects of other objects in the scene
	- Don't get shadows or reflections for free
- **Global Illumination** considers other points in scene
- **View Dependent Solution (Ray Tracing)
	- Advantages
		- Only looking at the relevant parts of a scene
		- Can work with any kind of geometry
		- Can produce very high-quality results
		- In some methods, view dependent portions of the solution can be cached as well
		- Uses less memory than view independent
- **View Independent**
	- A single solution for the light distribution in the entire scene is determined advanced
	- Then snapshots of the solution from different viewpoints by sampling the complete solution for specific positions/directions
	- Disadvantages
		- Usually restricted to meshes
		- Extra computation that mightn't be needed
### Light, Colour, Spectra
- 
### Surface Reflectance
 - Solving of **light reflection** of arbitrarily complex geometries
 - Surfaces scatter light
	 - Different colours/textures scatter light differently
 - Distribution can be described by BDRF algorithm, how much energy is scattered
 - 
### Solid angle, radiometric units, radiance
### Inverse Square Law, the cosine rule
___
Created: 2023-09-20

