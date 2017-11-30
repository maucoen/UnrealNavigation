# GameLiftServerSDK Unreal Plugin
## Documention
You can find the official GameLift documentation [here](https://aws.amazon.com/documentation/gamelift/).
## Using the plugin
### Building the C++ SDK
Before we can use the plugin inside an Unreal game, we need to compile GameLift server c++ SDK.
To build GameLift server sdk, all you must do is the following:  
Linux -
```sh
mkdir out
cd out
cmake -DBUILD_FOR_UNREAL=1 ..
make
```

Windows -
```sh
mkdir out
cd out
cmake -G "Visual Studio 14 2015 Win64" -DBUILD_FOR_UNREAL=1 ..
msbuild ALL_BUILD.vcxproj /p:Configuration=Release
```
This step produces the following binary files required by the plugin.  

Linux -  
* out/prefix/lib/aws-cpp-sdk-gamelift-server.so  

Windows -  
* out\prefix\bin\aws-cpp-sdk-gamelift-server.dll  
* out\prefix\lib\aws-cpp-sdk-gamelift-server.lib

Second step is to copy the binary files to the Unreal plugin's ThirdParty directory. 

Linux -  
* ThirdParty/GameLiftServerSDK/Linux/x86_64-unknown-linux-gnu/aws-cpp-sdk-gamelift-server.so  

Windows -  
* ThirdParty\GameLiftServerSDK\Win64\aws-cpp-sdk-gamelift-server.dll
* ThirdParty\GameLiftServerSDK\Win64\aws-cpp-sdk-gamelift-server.lib

At this point, we are ready to add the plugin to an Unreal game project and start using it.

For more detailed instructions on how to build the c++ SDK, please refer to the README.md file located in the c++ SDK directory.

### Import the plugin into a project
There are quite a lot of wasy to import an Unreal plugin. The method shown below doesn't require use of the Unreal Editor.

First, we'll want to add GameLiftServerSDK plugin to the game's .uproject file.
```sh
"Plugins": [
    {
        "Name": "GameLiftServerSDK",
        "Enabled": true
    }
]
```
Next, we'll want to make sure the game's ModuleRules take a dependency on the plugin.
For example:
```csharp
using UnrealBuildTool;

public class MyAwesomeGame : ModuleRules
{
    public MyAwesomeGame(TargetInfo Target)
    {
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "GameLiftServerSDK" });
    }
}
```

And that's it! We can start using with the plugin now!


GameLiftServerSDK plugin defines WITH_GAMELIFT preprocessor flag.
WITH_GAMELIFT=1 only when two conditions are met:
1. The plugins found the GameLift server SDK binaries.
2. Target.Type == TargetRules.TargetType.Server  

This means only Unreal Server builds will invoke GameLift's backplane API. It also enables developers to write code that will execute properly for all the different Unreal Targets the game may produce.
 
### Example code
The code sample below showcases how to initialize a game server with GameLift. See the GameLift server integration guide for more details.
As we can see, the GameLift-specific code is dependent on the WITH_GAMELIFT preprocessor flag. This flag is true only when both of these conditions are met:
1. The plugins found the GameLift server SDK binaries.
2. Target.Type == TargetRules.TargetType.Server  

This means only Unreal Server builds will invoke GameLift's backplane API. It also enables developers to write code that will execute properly for all the different Unreal Targets the game may produce.

```cpp
#include "GameLiftFPS.h"
#include "Engine.h"
#include "EngineGlobals.h"
#include "GameLiftFPSGameMode.h"
#include "GameLiftFPSHUD.h"
#include "GameLiftFPSCharacter.h"
#include "GameLiftServerSDK.h"

AGameLiftFPSGameMode::AGameLiftFPSGameMode()
    : Super()
{

//Let's run this code only if GAMELIFT is enabled. Only with Server targets!
#if WITH_GAMELIFT

    //Getting the module first.
    FGameLiftServerSDKModule* gameLiftSdkModule = &FModuleManager::LoadModuleChecked<FGameLiftServerSDKModule>(FName("GameLiftServerSDK"));

    //InitSDK will establish a local connection with GameLift's agent to enable further communication.
    gameLiftSdkModule->InitSDK();

    //When a game session is created, GameLift sends an activation request to the game server and passes along the game session object containing game properties and other settings.
    //Here is where a game server should take action based on the game session object.
    //Once the game server is ready to receive incoming player connections, it should invoke GameLiftServerAPI.ActivateGameSession()
    auto onGameSession = [=](Aws::GameLift::Server::Model::GameSession gameSession)
    {
        gameLiftSdkModule->ActivateGameSession();
    };
    
    FProcessParameters* params = new FProcessParameters();
    params->OnStartGameSession.BindLambda(onGameSession);

    //OnProcessTerminate callback. GameLift will invoke this callback before shutting down an instance hosting this game server.
    //It gives this game server a chance to save its state, communicate with services, etc., before being shut down.
    //In this case, we simply tell GameLift we are indeed going to shutdown.
    params->OnTerminate.BindLambda([=](){gameLiftSdkModule->ProcessEnding();});

    //This is the HealthCheck callback.
    //GameLift will invoke this callback every 60 seconds or so.
    //Here, a game server might want to check the health of dependencies and such.
    //Simply return true if healthy, false otherwise.
    //The game server has 60 seconds to respond with its health status. GameLift will default to 'false' if the game server doesn't respond in time.
    //In this case, we're always healthy!
    params->OnHealthCheck.BindLambda([](){return true; });

    //This game server tells GameLift that it will listen on port 7777 for incoming player connections.
    params->port = 7777;

    //Here, the game server tells GameLift what set of files to upload when the game session ends.
    //GameLift will upload everything specified here for the developers to fetch later.
    TArray<FString> logfiles;
    logfiles.Add(TEXT("aLogFile.txt"));
    params->logParameters = logfiles;

    //Calling ProcessReady tells GameLift this game server is ready to receive incoming game sessions!
    gameLiftSdkModule->ProcessReady(*params);
#endif
}
```