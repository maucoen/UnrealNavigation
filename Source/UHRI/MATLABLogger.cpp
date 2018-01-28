// Fill out your copyright notice in the Description page of Project Settings.

#include "MATLABLogger.h"
#include "UObject/ConstructorHelpers.h"
#include "TimerManager.h"


AMATLABLogger::AMATLABLogger()
	: Super()
{
	




	// set default pawn class to spawn
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/VehicleAdv/MarsBuggy_BP"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

}

void AMATLABLogger::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	Players.Add(NewPlayer);

	Matlab = engOpen(NULL);

	/*
	* Plot the result
	*/
	engEvalString(Matlab, "figure(1);");
	engEvalString(Matlab, "title('World position of buggy');");
	engEvalString(Matlab, "xlabel('X');");
	engEvalString(Matlab, "ylabel('Y');");
	engEvalString(Matlab, "hold on;");
	engEvalString(Matlab, "grid on;");
	engEvalString(Matlab, "view(-10, 35);");

	FTimerHandle GameStartTimer;
	GetWorldTimerManager().SetTimer(GameStartTimer, this, &AMATLABLogger::SendToMatlab, 1.0f, true, 10.0f);

}

void AMATLABLogger::SendToMatlab()
{
	UE_LOG(LogTemp, Warning, TEXT("Sending to matlab"));


	//dynamic cast to access public location of first player's actor;
	auto pos = Cast<AActor, APlayerController>(Players[0])->GetActorLocation();

	double posy[3] = { pos.X, pos.Y, pos.Z };

	UE_LOG(LogTemp, Warning, TEXT("Sending to matlab"));
	
	/*
	* Create a variable from our data
	*/
	T = mxCreateDoubleMatrix(3, 1, mxREAL);
	memcpy((char *)mxGetPr(T), (char *)posy, 3 * sizeof(double));

	/*
	* Place the variable T into the MATLAB workspace
	*/
	engPutVariable(Matlab, "T", T);
	engEvalString(Matlab, "stem3(T(1),T(2),T(3));");

}

void AMATLABLogger::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	engClose(Matlab);
}

