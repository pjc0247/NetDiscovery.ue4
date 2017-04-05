#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "NetDiscovery.generated.h"

UCLASS()
class PUPPERPARTYVR_API UNetDiscovery : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category="NetDiscovery")
	static void StartDiscovery();
	
	UFUNCTION(BlueprintCallable, Category = "NetDiscovery")
	static bool EndDiscovery(bool &isServer, FString &serverIp);

	UFUNCTION(BlueprintPure, Category = "NetDiscovery")
	static bool IsDiscovering();

	UFUNCTION(BlueprintPure, Category = "NetDiscovery")
	static int GetCurrentDiscoveredPeersCount();
};
