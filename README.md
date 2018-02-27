# UnrealNavigation
Unreal Navigation is an effort to integrate industry standard autonomous navigation algorithms to the Unreal Engine to provide a variety of test environments and ease of use in a real-time simulation. 

## Current Setup
We are using the Unreal Engine 4.18, source-built in Linux, as simulation environment. ROS Kinetic is being used as the utility that has most of these industry standard autonomous navigation algorithms. 

## UE4 Dependencies
Unreal Navigation currently depends on the UROSBridge, UCoordConv and UnrealCV plugins. 


## Current Progress

A few demonstrations of ORB-SLAM operating on a real-time Unreal Engine simulation have been performed in uncommon environments.

Here is an asteroid field (10x speed):

<<<<<<< HEAD
=======
Here is an asteroid field:

>>>>>>> 6f0a2971b8d57c3a32299c1b57c6da7374698351
![Asteroid ORBSLAM](https://github.com/maucoen/UnrealNavigation/blob/Navigation/WebContent/asteroidslam.gif "Asteroid field ORB SLAM")



### Current Priority
Integration of a simple Voxblox to form a physical representation of the map.

