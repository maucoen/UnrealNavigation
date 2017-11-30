// AMAZON CONFIDENTIAL

/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/
#pragma once


#include "ModuleManager.h"
#include "DelegateCombinations.h"

#if PLATFORM_WINDOWS
#include "AllowWindowsPlatformTypes.h"
#endif

#include "aws/gamelift/common/Outcome.h"
#include "aws/gamelift/server/GameLiftServerAPI.h"
#include "GameLiftServerSDKModels.h"
#include <map>

#if PLATFORM_WINDOWS
#include "HideWindowsPlatformTypes.h"
#endif

DECLARE_DELEGATE_OneParam(FOnStartGameSession, Aws::GameLift::Server::Model::GameSession);
DECLARE_DELEGATE_RetVal(bool, FOnHealthCheck);

struct GAMELIFTSERVERSDK_API FProcessParameters {
    FOnStartGameSession OnStartGameSession;
    FOnHealthCheck OnHealthCheck;
    FSimpleDelegate OnTerminate;
    int port = -1;
    TArray<FString> logParameters;

    void OnTerminateFunction() {
        this->OnTerminate.ExecuteIfBound();
    }

    bool OnHealthCheckFunction() {
        if (this->OnHealthCheck.IsBound()){
            return this->OnHealthCheck.Execute();
        }
        return false;
    }

    void OnActivateFunction(Aws::GameLift::Server::Model::GameSession gameSession) {
        this->OnStartGameSession.ExecuteIfBound(gameSession);
    }
};

class GAMELIFTSERVERSDK_API FGameLiftServerSDKModule : public IModuleInterface
{
public:

    /** IModuleInterface implementation */
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

    virtual FGameLiftStringOutcome GetSdkVersion();

    // Needs the standalone server to be running locally. If not, this will block at load time.
    virtual FGameLiftGenericOutcome InitSDK();

    //virtual TGameLiftGenericOutcome ProcessReady(Aws::GameLift::Server::ProcessParameters &processParameters);
    virtual FGameLiftGenericOutcome ProcessReady(FProcessParameters &processParameters);

    virtual FGameLiftGenericOutcome ProcessEnding();
    virtual FGameLiftGenericOutcome ActivateGameSession();
    virtual FGameLiftGenericOutcome TerminateGameSession();
    virtual FGameLiftGenericOutcome AcceptPlayerSession(const FString& playerSessionId);
    virtual FGameLiftGenericOutcome RemovePlayerSession(const FString& playerSessionId);

    virtual FGameLiftGenericOutcome UpdatePlayerSessionCreationPolicy(EPlayerSessionCreationPolicy policy);
    virtual FGameLiftStringOutcome GetGameSessionId();

private:
    /** Handle to the dll we will load */
    static void* GameLiftServerSDKLibraryHandle;
    static bool LoadDependency(const FString& Dir, const FString& Name, void*& Handle);
    static void FreeDependency(void*& Handle);
};
