NetDiscovery.ue4
====

같은 네트워크 안에서 피어들을 검색한다

### How to Setup

1. 자기 UE4 프로젝트의 Source 폴더에 SimpleNetDiscovery 폴더를 복붙한다.
2. 자기 프로젝트 Target.cs와 Editor.Target.Cs에 SimpleNetDiscovery 모듈 추가한다.
3. 이 모듈을 쓸 게임 모듈(보통 프로젝트 게임 모듈)의 Public Dependency에 SimpleNetDiscovery를 추가한다.

### 사용법

![dis](_discovery.png)<br><br>

여기서 자기가 Server면 열고 싶은 맵 ?listen붙여서 열고 아니면 서버 아이피로 접속하기