# UnrealNavigation
Unreal Navigation is an effort to integrate industry standard autonomous navigation algorithms to the Unreal Engine to provide a variety of test environments and ease of use in a real-time simulation. 

## Setup
We are using the Unreal Engine 4.18, source-built in Linux, as simulation environment. ROS Kinetic is being used as the utility that has most of these industry standard autonomous navigation algorithms. 

### UE4 Dependencies
This branch currently depends on the [UROSBridge], [UCoordConv] (provided by RobCoG ) and [UnrealCV] plugins.

### How to Use
Please download all plugins to your UE project. Additionally, install ROS and ORB-SLAM2 in your system.

In the UE Editor, attach the ROSImagePublisher actor to your specific camera sensor actor. It will inherit rotation and location for its attachment, and will act as your camera sensor to ROS. 

The ROSImagePublisher has settings for Mono, RGBD, or Stereo camera, accesible from the UE Editor. You can toggle publishing to ORB-SLAM2 topics by pressing keyboard K once in-game. (line 31 ROSImagePublisher.cpp)

Before starting to publish to ROS, run the ROSBridge nodes (as detailed in [UROSBridge]) and the ORB-SLAM2 node for your camera settings (as detailed in ORB-SLAM2 ROS nodes examples). Yaml files to match the current commit are in: `./Config/` in this repo. 


## Final Status
A few demonstrations of [ORB-SLAM2] operating on a real-time Unreal Engine simulation have been performed in uncommon environments.

Here is an asteroid field (10x speed):

![Asteroid ORBSLAM](https://github.com/maucoen/UnrealNavigation/blob/Navigation/WebContent/asteroidslam.gif "Asteroid field ORB SLAM")

For the mapping functionality, we are integrating with [Voxblox] to form a physical representation of the map.

Below is a demo using [Voxblox] mapping and subsequent pointcloud visualization in RViz.

![Asteroid PCL2](https://github.com/maucoen/UnrealNavigation/blob/Navigation/WebContent/asteroidpcl.gif "Asteroid field PCL2")

Below is a demo of the full autonomous navigation system working at a basic level. The ESDF map from Voxblox can be seen, as well as the planner's trajectory and the Orion capsule following the trajectory in real-time in the simulation. 


![Full Loop ](https://github.com/maucoen/UnrealNavigation/blob/Navigation/WebContent/fullLoop.gif "Full Loop") 
 

[UROSBridge]: https://github.com/robcog-iai/UROSBridge
[UCoordConv]: https://github.com/robcog-iai/UCoordConv
[RobCoG]: https://github.com/robcog-iai
[UnrealCV]: https://github.com/unrealcv/unrealcv
[ORB-SLAM2]: https://github.com/raulmur/ORB_SLAM2
[Voxblox]: https://github.com/ethz-asl/voxblox
