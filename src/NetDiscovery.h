#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "NetDiscovery.generated.h"

UCLASS()
class PUPPERPARTYVR_API UNetDiscovery : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category="NetDiscovery")
	static void StartDiscovering();
	
	UFUNCTION(BlueprintCallable, Category = "NetDiscovery")
	static bool EndDiscovering(bool &isServer, FString &serverIp);

	UFUNCTION(BlueprintPure, Category = "NetDiscovery")
	static bool IsDiscovering();
};
