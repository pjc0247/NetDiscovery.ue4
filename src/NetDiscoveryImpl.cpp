#include "PupperPartyVR.h"
#include "NetDiscoveryImpl.h"

#pragma comment (lib, "ws2_32.lib")

using namespace std;

NetDiscoveryImpl::NetDiscoveryImpl() :
	iamServer(false) {

	if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
		printf("Could not create socket : %d", WSAGetLastError());

	char opt = 1;
	if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int)) < 0)
		printf("setsockopt(SO_REUSEADDR) failed");
	if (setsockopt(s, SOL_SOCKET, SO_BROADCAST, &opt, sizeof(int)) < 0)
		printf("setsockopt(SO_BROADCAST) failed");

	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr("0.0.0.0");
	serverAddr.sin_port = htons(9918);

	if (::bind(s, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
		printf("Bind failed with error code : %d", WSAGetLastError());

	netId = rand();

	discovering = true;
	thread([this]() {
		RecvWorker();
	}).detach();
	thread([this]() {
		SendWorker();
	}).detach();
}
NetDiscoveryImpl::~NetDiscoveryImpl() {
	if (s != INVALID_SOCKET)
		closesocket(s);
}

bool NetDiscoveryImpl::EndDiscovery() {
	discovering = false;

	if (peers.empty()) {
		printf("something went wrong");
		return false;
	}

	auto firstPeer = peers.begin();
	iamServer = firstPeer->first == netId;
	serverIp = firstPeer->second;

	return true;
}

bool NetDiscoveryImpl::IsDiscovering() const {
	return discovering;
}
bool NetDiscoveryImpl::IsServer() const {
	if (discovering)
		throw std::runtime_error("discovering == true");

	return iamServer;
}
std::string NetDiscoveryImpl::GetServerIp() const {
	if (discovering)
		throw std::runtime_error("discovering == true");

	return serverIp;
}

void NetDiscoveryImpl::RecvWorker() {
	while (discovering) {
		char buf[1025];
		sockaddr_in otherAddr;
		int recvLen, addrLen;

		addrLen = sizeof(otherAddr);
		if ((recvLen = recvfrom(s, buf, 1024, 0, (struct sockaddr *) &otherAddr, &addrLen)) == SOCKET_ERROR) {
			printf("recvfrom() failed with error code : %d", WSAGetLastError());
			return;
		}
		buf[recvLen] = 0;

		// double check
		if (discovering == false)
			return;

		auto ip = GetIpFromSockAddr(otherAddr);
		peers[atoi(buf)] = ip;

		printf("%s : %s\n", buf, ip.c_str());

		Sleep(100);
	}
}
void NetDiscoveryImpl::SendWorker() {
	sockaddr_in sendAddr;
	memset(&sendAddr, 0, sizeof(sendAddr));
	sendAddr.sin_family = AF_INET;
	sendAddr.sin_addr.s_addr = inet_addr("255.255.255.255");
	sendAddr.sin_port = htons(9918);

	char buf[1024];
	sprintf(buf, "%d", netId);

	while (discovering) {
		int sent = sendto(s, buf, 1024, 0, (sockaddr*)&sendAddr, sizeof(sendAddr));

		if (sent == -1)
			printf("failed to send : %d", (int)GetLastError());

		Sleep(1000);
	}
}

std::string NetDiscoveryImpl::GetIpFromSockAddr(const sockaddr_in &addr) {
	return inet_ntoa(addr.sin_addr);
}
