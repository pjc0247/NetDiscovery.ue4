#pragma once

#include <WinSock2.h>
#include <thread>
#include <atomic>
#include <map>

class PUPPERPARTYVR_API NetDiscoveryImpl {
public:
	NetDiscoveryImpl();
	~NetDiscoveryImpl();

	bool EndDiscovery();

	int GetCurrentPeersCount() const;
	bool IsDiscovering() const;
	bool IsServer() const;
	std::string GetServerIp() const;

private:
	void RecvWorker();
	void SendWorker();

	std::string GetIpFromSockAddr(const sockaddr_in &addr);

private:
	SOCKET s;
	sockaddr_in serverAddr;

	int netId;
	std::atomic<bool> discovering;

	bool iamServer;
	std::string serverIp;

	std::map<int, std::string> peers;
};
