UCoordConv
=====

Coordinate (left/right hand, camera) conversions from and to Unreal.

## Usage

-   Add the plugin to your project (e.g `MyProject/Plugins/UCoordConv`)  
    

-   Add the module dependency to your module (Project, Plugin); In the
    `MyModule.Build.cs` file:  

		PublicDependencyModuleNames.AddRange(  
		new string[]  
		{  
		...  
		"UCoordConv",  
		...  
		}  
		);  
    

-   Include `CoordConvStatics.h` where you plan to use the functions.

## Example

```cpp
	// Unreal to ROS conversion
	FTransform ROSTransf = FCoordConvStatics::UToROS(InUTransform);
```



### Engine Version 4.18
