// Fill out your copyright notice in the Description page of Project Settings.

#include "ROSImagePublisher.h"
#include "TimerManager.h"
#include "geometry_msgs/Transform.h"
#include "geometry_msgs/TransformStamped.h"
#include "CoordConvStatics.h"
#include "tf2_msgs/TFMessage.h"
#include "CaptureManager.h"
#include "Kismet/GameplayStatics.h"
#include "Components/InputComponent.h"

// Sets default values for this component's properties
AROSImagePublisher::AROSImagePublisher(const FObjectInitializer &ObjectInitializer)
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryActorTick.bCanEverTick = true;

    // All socket and timers defined in .h, editable in editor.
}

// Called when the game starts
void AROSImagePublisher::BeginPlay()
{
    Super::BeginPlay();

    auto Controller = UGameplayStatics::GetPlayerController(this, 0);
    if (Controller)
    {
        InputComponent = NewObject<UInputComponent>(this);
        if (InputComponent)
        {
            InputComponent->BindKey(EKeys::K, EInputEvent::IE_Pressed, this, &AROSImagePublisher::TogglePublish);
            EnableInput(Controller);
        }
    }

    if (bIsCompressed)
    {
        Type = TEXT("sensor_msgs/CompressedImage");
    }
    else
    {
        Type = TEXT("sensor_msgs/Image");
    }

    //handles imaging types and ROS connection
    SetupImager();
}

// Called when game ends or actor deleted
void AROSImagePublisher::EndPlay(const EEndPlayReason::Type Reason)
{
    LastFrame.Empty();

    if (Handler.IsValid())
        Handler->Disconnect();

    Super::EndPlay(Reason);
}

// Called every frame
void AROSImagePublisher::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    //UE_LOG(LogTemp, Warning, TEXT("tick"));
    while (!LastFrame.IsEmpty())
    {
        UE_LOG(LogTemp, Warning, TEXT("non empty"));
        //FGTCaptureTask Task;
        //PendingTasksROS.Peek(Task);

        uint64 FrameToRender;
        LastFrame.Peek(FrameToRender);
        uint64 CurrentFrame = GFrameCounter;
        int WaitCount = 1;

        //frametorender needs one or 2 ticks before it's rendered, we skip tick otherwise
        if (CurrentFrame > (FrameToRender + WaitCount))
        {
            LastFrame.Pop();

            UE_LOG(LogTemp, Warning, TEXT("inside framer"));
            for (int i = 0; i < Modes.Num(); i++)
            {
                if (i > 0 && (ImagingType == EImagingType::STEREO)) //stereo eye
                {
                    GTCapturers[i]->SetRelativeLocation(StereoBaselineCm);
                }
                //check for capture component directly
                if (GTCapturers[i]->GetCaptureComponent(Modes[i]) != nullptr)
                {
                    TArray<uint8> ImgData;
                    if (bIsCompressed)
                    {
                        ImgData = GTCapturers[i]->CapturePng(Modes[i]);
                    }
                    else
                    {
                        ImgData = GTCapturers[i]->CaptureNpyUint8(Modes[i], channels);
                        UE_LOG(LogTemp, Warning, TEXT("Capturing %s"), *Modes[i]);
                    }
                    ROSHeader.SetSeq(Count);
                    ROSHeader.SetStamp(FROSTime());

                    if (bSaveToDisk) //saves
                    {
                        FString Filename = FString::FromInt(Count++) + Modes[i] + FString::FromInt(i) + TEXT(".png");
                        GTCapturers[i]->SavePng(GTCapturers[i]->GetCaptureComponent(Modes[i])->TextureTarget, Filename);
                    }

                    if (Handler.IsValid())
                    {
                        // Send to ROS asynchronously!
                        (new FAutoDeleteAsyncTask<FSendToROS>(
                             Handler,
                             ImgData,
                             ROSHeader,
                             Topics[i],
                             bIsCompressed))
                            ->StartBackgroundTask();
                    }
                    else
                    {
                        UE_LOG(LogTemp, Warning, TEXT("NULL ROSBridge! No image sent"));
                    }
                }
                else
                {
                    UE_LOG(LogTemp, Warning, TEXT("NULL Capture! No image sent"));
                }
            }

            FTransform TF = 
                GTCapturers[0]->GetComponentTransform();

	        FVector tr = TF.GetTranslation();
	        FQuat qt = TF.GetRotation();

            
            // Question on rotation vs transformation... Affects the order - we want a transformation
            // Translation and rotation should transform from body to global (what qt is)
            // We want a transformation from camera to global
            // T_{c->g} = T_{c->b} * T_{b->g}
            // Convention for quaternion multiplication is from: https://wiki.unrealengine.com/UE4_Transform_Calculus_-_Part_2
            // Convetion is q3 = q2*q1; FOR TRANSFORMATIONS
            FQuat T_cb = FQuat(0,0,90)*FQuat(90,0,0); // 90 roll then 90 yaw from camera to body

            qt = qt*T_cb; // qt is body to global, after this line it is camera to global
            // Transformation is 
            // v_g = q_bg v_b q_bg^c (q^c is the quaternion conjugate)
            // so 
            // v_g = q_bg q_cb v_c q_cb^c q_bg^c
            // Hence q_cg = q_bg q_cb

            // To test a simple example: - should have forward along the y axis
            // qt = qt*FQuat(0,0,-90);
            

            // If rotations are negated due to the left handed system:
            // qt = qt*FQuat(0,0,90);
            // FQuat T_cb = FQuat(0,0,-90)*FQuat(-90,0,0);

            /*
            // With Rotation matrices
            FRotationMatrix T_bg = FRotationMatrix(FRotator(qt));
            //or 
            // FRotationMatrix T_bg = FRotationMatrix(qt);
            FRotationMatrix T_cb = FRotationMatrix(FRotator(0,0,90))*FRotationMatrix(FRotator(0,0,90));

            qt = FQuat(T_bg*T_cb); // Body to camera, then body to global
            */


            // FRotator rot = FRotator(qt);

            // rot = rot + FRotator(0,0,90);
            // rot = rot + FRotator(90,0,0);

            // qt = FQuat(rot);

            FTransform TF2 = FCoordConvStatics::UToROS(FTransform(qt,tr));

	        FVector tr2 = TF2.GetTranslation();
	        FQuat qt2 = TF2.GetRotation();
            // Construct geometry::msg transfrom
	        // geometry::msgs Vector3, Quaternion already have
	        // overloaded constructors from FVector

            std_msgs::Header ROSHeader1 = std_msgs::Header(Count, FROSTime(), TEXT("world"));
            TSharedPtr<geometry_msgs::TransformStamped> FTransform = MakeShareable(
                new geometry_msgs::TransformStamped(
                    ROSHeader1, 
                    TEXT("Cam"), 
                    geometry_msgs::Transform(tr2, qt2)));

            // Send msg to ROS

            TSharedPtr<tf2_msgs::TFMessage> SendTF = MakeShareable(
                new tf2_msgs::TFMessage());

            SendTF->AddTransform(*FTransform);

            Handler->PublishMsg("/tf", SendTF);
            Count++;
        }
        else {break; }
    }
}

void AROSImagePublisher::SetupImager()
{

    auto CastedPawn = Cast<APawn, AActor>(GetAttachParentActor());
    // Setup Correct types of capture Mode and ORBSLAM ROS Topic
    switch (ImagingType)
    {
        case EImagingType::MONO:
        {
            Modes.Add(TEXT("lit"));
            Topics.Add(TEXT("/camera/image_raw"));
            GTCapturers.Add(UGTCaptureComponent::Create(CastedPawn, Modes));
            break;
        }

        case EImagingType::RGBD:
        {
            Modes.Add(TEXT("lit"));
            Modes.Add(TEXT("vis_depth"));
            GTCapturers.Add(UGTCaptureComponent::Create(CastedPawn, Modes));
            GTCapturers.Add(UGTCaptureComponent::Create(CastedPawn, Modes));
            Topics.Add(TEXT("/camera/rgb/image_raw"));
            Topics.Add(TEXT("/camera/depth_registered/image_raw"));
            break;
        }

        case EImagingType::STEREO:
        {
            Modes.Add(TEXT("lit"));
            Modes.Add(TEXT("lit"));
            GTCapturers.Add(UGTCaptureComponent::Create(CastedPawn, Modes));
            GTCapturers.Add(UGTCaptureComponent::Create(CastedPawn, Modes));
            Topics.Add(TEXT("/camera/left/image_raw"));
            Topics.Add(TEXT("/camera/right/image_raw"));
            break;
        }
    }

    

    Handler = MakeShareable<FROSBridgeHandler>(
        new FROSBridgeHandler(IPAddress, Port));

    // Set websocket server address to default
    for (int i = 0; i < Modes.Num(); i++)
    {
        Handler->AddPublisher(
            MakeShareable<FROSBridgePublisher>(
                new FROSBridgePublisher(Topics[i], Type)));
    }

    Topics.Add(TEXT("CameraTransform"));
    Handler->AddPublisher(
            MakeShareable<FROSBridgePublisher>(
                new FROSBridgePublisher("tf", "tf2_msgs/TFMessage")));


    Handler->Connect();
    UE_LOG(LogTemp, Warning, TEXT("handler on"));

    ROSHeader = std_msgs::Header(Count, FROSTime(), TEXT("Cam"));
}

void AROSImagePublisher::EnqueueImageTask()
{
    // FString InFilename = FString::FromInt(Count) + TEXT("mono.png");
    // FAsyncRecord* AsyncRecord = FAsyncRecord::Create();
    // FGTCaptureTask GTCaptureTask = FGTCaptureTask(Modes[0], InFilename, GFrameCounter, AsyncRecord);
    // PendingTasksROS.Enqueue(GTCaptureTask);

    LastFrame.Enqueue(GFrameCounter);
}

void AROSImagePublisher::TogglePublish()
{
    if (!bIsPublishing)
    {
        float Period = 1.0 / Frequency;

        GetWorldTimerManager().SetTimer(PublishTimer, this,
                                        &AROSImagePublisher::EnqueueImageTask, Period, true, 0.5f);

        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(
                -1, 2.0f, FColor::Green, TEXT("starting image publishing"), true, FVector2D(2, 2));
        }
    }
    else
    {
        GetWorld()->GetTimerManager().ClearTimer(PublishTimer);
        
        LastFrame.Empty();

        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(
                -1, 2.0f, FColor::Red, TEXT("stopping image publishing"), true, FVector2D(2, 2));
        }
    }

    bIsPublishing = !bIsPublishing;
}



// /**
// Attach a GTCaptureComponent to a pawn
//  */
// UGTCaptureComponent* UGTCaptureComponent::Create(APawn* InPawn, TArray<FString> Modes)
// {
// 	UWorld* World = FUE4CVServer::Get().GetGameWorld();
// 	UGTCaptureComponent* GTCapturer = NewObject<UGTCaptureComponent>();

// 	GTCapturer->bIsActive = true;
// 	// check(GTCapturer->IsComponentTickEnabled() == true);
// 	GTCapturer->Pawn = InPawn; // This GTCapturer should depend on the Pawn and be released together with the Pawn.

// 	// This snippet is from Engine/Source/Runtime/Engine/Private/Components/SceneComponent.cpp, AttachTo
// 	FAttachmentTransformRules AttachmentRules(EAttachmentRule::KeepRelative, false);
// 	//ConvertAttachLocation(EAttachLocation::KeepRelativeOffset, AttachmentRules.LocationRule, AttachmentRules.RotationRule, AttachmentRules.ScaleRule);
// 	GTCapturer->AttachToComponent(InPawn->GetRootComponent(), AttachmentRules);
// 	// GTCapturer->AddToRoot();
// 	GTCapturer->RegisterComponentWithWorld(World);
// 	GTCapturer->SetTickableWhenPaused(true);

// 	for (FString Mode : Modes)
// 	{
// 		// DEPRECATED_FORGAME(4.6, "CaptureComponent2D should not be accessed directly, please use GetCaptureComponent2D() function instead. CaptureComponent2D will soon be private and your code will not compile.")
// 		USceneCaptureComponent2D* CaptureComponent = NewObject<USceneCaptureComponent2D>();
// 		CaptureComponent->bIsActive = false; // Disable it by default for performance consideration
// 		GTCapturer->CaptureComponents.Add(Mode, CaptureComponent);

// 		// CaptureComponent needs to be attached to somewhere immediately, otherwise it will be gc-ed

// 		CaptureComponent->AttachToComponent(GTCapturer, AttachmentRules);
// 		InitCaptureComponent(CaptureComponent);

// 		UE_LOG(LogUnrealCV, Warning, TEXT("mode is %s"), *Mode);

// 		UMaterial* Material = GetMaterial(Mode);
// 		if (Mode == "lit") // For rendered images
// 		{
// 			//UE_LOG(LogUnrealCV, Warning, TEXT("inside mode lit"));
// 			// FViewMode::Lit(CaptureComponent->ShowFlags);
// 			CaptureComponent->TextureTarget->TargetGamma = GEngine->GetDisplayGamma();
// 			// float DisplayGamma = SceneViewport->GetDisplayGamma();
// 		}
// 		else if (Mode == "default")
// 		{
// 			continue;
// 		}
// 		else // for ground truth
// 		{
// 			CaptureComponent->TextureTarget->TargetGamma = 1;
// 			if (Mode == "object_mask") // For object mask
// 			{
// 				// FViewMode::Lit(CaptureComponent->ShowFlags);
// 				FViewMode::VertexColor(CaptureComponent->ShowFlags);
// 			}
// 			else if (Mode == "wireframe") // For object mask
// 			{
// 				FViewMode::Wireframe(CaptureComponent->ShowFlags);
// 			}
// 			else //depth requires post processing
// 			{
// 				check(Material);
// 				// GEngine->GetDisplayGamma(), the default gamma is 2.2
// 				// CaptureComponent->TextureTarget->TargetGamma = 2.2;
// 				FViewMode::PostProcess(CaptureComponent->ShowFlags);

// 				CaptureComponent->PostProcessSettings.AddBlendable(Material, 1);
// 				// Instead of switching post-process materials, we create several SceneCaptureComponent, so that we can capture different GT within the same frame.
// 			}
// 		}
// 	}
// 	return GTCapturer;
// }

// TArray<uint8> UGTCaptureComponent::CaptureNpyUint8(FString Mode, int32 Channels)
// {
// 	// Flush location and rotation
// 	check(CaptureComponents.Num() != 0);
// 	USceneCaptureComponent2D* CaptureComponent = CaptureComponents.FindRef(Mode);

// 	TArray<uint8> NpyData;
// 	if (CaptureComponent == nullptr) {
//     UE_LOG(LogUnrealCV, Error, TEXT("Component for mode %s not found. Returning empty array."), *Mode);
//     return NpyData;
//   }

// 	// Attach this to something, for example, a real camera
// 	const FRotator PawnViewRotation = Pawn->GetViewRotation();
// 	if (!PawnViewRotation.Equals(CaptureComponent->GetComponentRotation()))
// 	{
// 		//CaptureComponent->SetWorldRotation(PawnViewRotation+FRotator(0,90,0));
// 		//CaptureComponent->AddRelativeRotation(FRotator(0,30,0));
// 	}

// 	UTextureRenderTarget2D* RenderTarget = CaptureComponent->TextureTarget;
// 	int32 Width = RenderTarget->SizeX, Height = RenderTarget->SizeY;
// 	TArray<FColor> ImageData;
// 	FTextureRenderTargetResource* RenderTargetResource;
// 	ImageData.AddUninitialized(Width * Height);
// 	RenderTargetResource = RenderTarget->GameThread_GetRenderTargetResource();
// 	FReadSurfaceDataFlags ReadSurfaceDataFlags;
// 	ReadSurfaceDataFlags.SetLinearToGamma(false); // This is super important to disable this!
// 	// Instead of using this flag, we will set the gamma to the correct value directly
// 	RenderTargetResource->ReadPixels(ImageData, ReadSurfaceDataFlags);

// 	//UE_LOG(LogTemp, Warning, TEXT("Image data before serialize is %d, %d, %d, %d"),ImageData[1001].R,ImageData[1001].G,ImageData[1001].B,ImageData[1001].A);
// 	// Check the byte order of data
// 	// Compress image data to npy array
// 	// Generate a header for the numpy array
// 	NpyData = NpySerialization(ImageData, Width, Height, Channels);

// 	return NpyData;
// }

// TArray<uint8> UGTCaptureComponent::NpySerialization(TArray<FColor> ImageData, int32 Width, int32 Height, int32 Channel)
// {
// 	uint8 *TypePointer = nullptr; // Only used for determing the type
// 	//UE_LOG(LogTemp, Warning, TEXT("INSIDE NPySerialization"));
// 	std::vector<int> Shape;
// 	Shape.push_back(Height);
// 	Shape.push_back(Width);
// 	if (Channel != 1) Shape.push_back(Channel);

// 	// std::vector<char> NpyHeader;// = cnpy::create_npy_header(TypePointer, Shape);

// 	// Append the actual data
// 	// FIXME: A slow implementation to convert TArray<FFloat16Color> to binary.
// 	/* A small size test
// 	std::vector<char> NpyData;
// 	for (int i = 0; i < 3 * 3 * 3; i++)
// 	{
// 		NpyData.push_back(i);
// 	}
// 	*/
// 	// std::vector<char> NpyData;
// 	std::vector<uint8> Uint8Data;
// 	Uint8Data.reserve(ImageData.Num() * Channel);
// 	//UE_LOG(LogTemp, Warning, TEXT("Image data in serialize is %d, %d, %d, %d"),ImageData[101].R,ImageData[101].G,ImageData[101].B,ImageData[101].A);
// 	for (int i = 0; i < ImageData.Num(); i++)
// 	{
// 		if (Channel == 1)
// 		{
// 			uint8 v = ImageData[i].R;
// 			Uint8Data.push_back(ImageData[i].R);
// 		}
// 		else if (Channel == 3)
// 		{
// 			Uint8Data.push_back(ImageData[i].R);
// 			Uint8Data.push_back(ImageData[i].G);
// 			Uint8Data.push_back(ImageData[i].B);
// 		}
// 		else if (Channel == 4)
// 		{
// 			Uint8Data.push_back(ImageData[i].R);
// 			Uint8Data.push_back(ImageData[i].G);
// 			Uint8Data.push_back(ImageData[i].B);
// 			Uint8Data.push_back(ImageData[i].A);
// 		}
// 	}
// 	//UE_LOG(LogTemp, Warning, TEXT("Uint8Data %d, %d, %d, %d"),Uint8Data[401],Uint8Data[402],Uint8Data[403],Uint8Data[404]);	
// 	check(Uint8Data.size() == Width * Height * Channel);
// 	// Convert to binary array
// 	const unsigned char* bytes = reinterpret_cast<const unsigned char*>(&Uint8Data[0]);

// 	// https://stackoverflow.com/questions/22629728/what-is-the-difference-between-char-and-unsigned-char
// 	// https://stackoverflow.com/questions/11022099/convert-float-vector-to-byte-vector-and-back
// 	std::vector<unsigned char> NpyData(bytes, bytes + sizeof(uint8) * Uint8Data.size());

// 	//NpyHeader.insert(NpyHeader.end(), NpyData.begin(), NpyData.end());
// 	// NpyHeader.insert(NpyData.begin(), NpyData.end());

// 	// FIXME: Find a more efficient implementation
// 	TArray<uint8> BinaryData;
// 	for (char Element : NpyData)
// 	{
// 		BinaryData.Add(Element);
// 	}
// 	return BinaryData;
// }

// void InitCaptureComponent(USceneCaptureComponent2D* CaptureComponent)
// {
// 	UWorld* World = FUE4CVServer::Get().GetGameWorld();
// 	// Can not use ESceneCaptureSource::SCS_SceneColorHDR, this option will disable post-processing
// 	CaptureComponent->CaptureSource = ESceneCaptureSource::SCS_FinalColorLDR;

// 	CaptureComponent->TextureTarget = NewObject<UTextureRenderTarget2D>();
// 	FServerConfig& Config = FUE4CVServer::Get().Config;
// 	CaptureComponent->TextureTarget->InitAutoFormat(Config.Width, Config.Height);
// 	CaptureComponent->FOVAngle = Config.FOV;

// 	/*
// 	UGameViewportClient* GameViewportClient = World->GetGameViewport();
// 	CaptureComponent->TextureTarget->InitAutoFormat(GameViewportClient->Viewport->GetSizeXY().X,  GameViewportClient->Viewport->GetSizeXY().Y); // TODO: Update this later
// 	*/

// 	CaptureComponent->RegisterComponentWithWorld(World); // What happened for this?
// 	// CaptureComponent->AddToRoot(); This is not necessary since it has been attached to the Pawn.

// }

// UMaterial* UGTCaptureComponent::GetMaterial(FString InModeName = TEXT(""))
// {
// 	// Load material for visualization
// 	static TMap<FString, FString>* MaterialPathMap = nullptr;
// 	if (MaterialPathMap == nullptr)
// 	{
// 		MaterialPathMap = new TMap<FString, FString>();
// 		MaterialPathMap->Add(TEXT("depth"), TEXT("Material'/UnrealCV/SceneDepthWorldUnits.SceneDepthWorldUnits'"));
//     	MaterialPathMap->Add(TEXT("plane_depth"), TEXT("Material'/UnrealCV/ScenePlaneDepthWorldUnits.ScenePlaneDepthWorldUnits'"));
// 		MaterialPathMap->Add(TEXT("vis_depth"), TEXT("Material'/UnrealCV/SceneDepth.SceneDepth'"));
// 		MaterialPathMap->Add(TEXT("debug"), TEXT("Material'/UnrealCV/debug.debug'"));
// 		// MaterialPathMap->Add(TEXT("object_mask"), TEXT("Material'/UnrealCV/VertexColorMaterial.VertexColorMaterial'"));
// 		MaterialPathMap->Add(TEXT("normal"), TEXT("Material'/UnrealCV/WorldNormal.WorldNormal'"));

// 		FString OpaqueMaterialName = "Material'/UnrealCV/OpaqueMaterial.OpaqueMaterial'";
// 		MaterialPathMap->Add(TEXT("opaque"), OpaqueMaterialName);
// 	}

// 	static TMap<FString, UMaterial*>* StaticMaterialMap = nullptr;
// 	if (StaticMaterialMap == nullptr)
// 	{
// 		StaticMaterialMap = new TMap<FString, UMaterial*>();
// 		for (auto& Elem : *MaterialPathMap)
// 		{
// 			FString ModeName = Elem.Key;
// 			FString MaterialPath = Elem.Value;
// 			ConstructorHelpers::FObjectFinder<UMaterial> Material(*MaterialPath); // ConsturctorHelpers is only available for UObject.

// 			if (Material.Object != NULL)
// 			{
// 				StaticMaterialMap->Add(ModeName, (UMaterial*)Material.Object);
// 			}
// 		}
// 	}

// 	UMaterial* Material = StaticMaterialMap->FindRef(InModeName);
// 	if (Material == nullptr)
// 	{
// 		UE_LOG(LogUnrealCV, Warning, TEXT("Can not recognize visualization mode %s"), *InModeName);
// 	}
// 	else UE_LOG(LogUnrealCV, Warning, TEXT("Returning %s"), *InModeName);
	
// 	return Material;
// }