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

	Players.Add(NewPlayer->GetPawn());

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
	GetWorldTimerManager().SetTimer(GameStartTimer, this, &AMATLABLogger::SendToMatlab, 0.2f, true, 10.0f);

	//dynamic cast to access public location of first player's actor;
	InitialPos = Players[0]->GetActorLocation();

}

void AMATLABLogger::SendToMatlab()
{
	//dynamic cast to access public location of first player's actor;
	auto pos = Players[0]->GetActorLocation() - InitialPos;

	double posy[3] = { pos.X, pos.Y, pos.Z };

	/*
	* Create a variable from our data
	*/
	T = mxCreateDoubleMatrix(3, 1, mxREAL);
	memcpy((char *)mxGetPr(T), (char *)posy, 3 * sizeof(double));

	/*
	* Place the variable T into the MATLAB workspace
	*/
	engPutVariable(Matlab, "T", T);
	engEvalString(Matlab, "scatter3(T(1),T(2),T(3),'d');");

}

void AMATLABLogger::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	
	// save to filepath and close engine
	engEvalString(Matlab, "saveas(gcf,'D:\\Epic\\Projects\\UHRI\\Saved\\matlab\\stem.png')");
	engEvalString(Matlab, "save('D:\\Epic\\Projects\\UHRI\\Saved\\matlab\\stem.mat')");
	engClose(Matlab); 
}

