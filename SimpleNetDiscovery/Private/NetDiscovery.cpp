#include "SimpleNetDiscovery.h"

#include "NetDiscoveryImpl.h"

#include "NetDiscovery.h"

static NetDiscoveryImpl *netDiscoveryImpl = nullptr;

void UNetDiscovery::StartDiscovery() {
	if (IsDiscovering()) {
		UE_LOG(LogTemp, Warning, TEXT("Already discovering"));
		return;
	}

	netDiscoveryImpl = new NetDiscoveryImpl();
}
bool UNetDiscovery::EndDiscovery(bool &isServer, FString &serverIp) {
	if (IsDiscovering() == false) {
		UE_LOG(LogTemp, Warning, TEXT("IsDiscovering != true"));
		return false;
	}

	auto ret = netDiscoveryImpl->EndDiscovery();

	isServer = netDiscoveryImpl->IsServer();
	serverIp = FString(ANSI_TO_TCHAR(netDiscoveryImpl->GetServerIp().c_str()));

	if (netDiscoveryImpl != nullptr) {
		delete netDiscoveryImpl;
		netDiscoveryImpl = nullptr;
	}

	return ret;
}
bool UNetDiscovery::IsDiscovering() {
	if (netDiscoveryImpl == nullptr)
		return false;

	return netDiscoveryImpl->IsDiscovering();
}
int UNetDiscovery::GetCurrentDiscoveredPeersCount() {
	if (netDiscoveryImpl == nullptr)
		return 0;

	return netDiscoveryImpl->GetCurrentPeersCount();
}
