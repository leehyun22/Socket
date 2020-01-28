#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <string>
#include <WinSock2.h>
#define SIZE 256
using namespace std;

void ShowErrorMessage(string message) {
	cout << "[오류 발생]: " << message << '\n';
	system("pause");
	exit(1);
}

int main() {
	WSADATA wsaData;
	SOCKET clientSocket;
	SOCKADDR_IN serverAddress;

	int serverPort = 9876;
	char reveived[SIZE];
	string sent;
	//WSAStartuo()함수 등을 통해 환경 설정을 진행해야함
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ShowErrorMessage("WSAStartup()");
	//socket(네트워크 주소 체계, 소켓타입, 프로토콜)
	clientSocket = socket(PF_INET, SOCK_STREAM, 0);
	//PF_INET->AF_INET, SOCK_STREAM -> TCP 소켓 생성
	//소켓을 생성하는 함수, 이함수는 '네트워크 주소 체계', '소켓 타입','프로토콜'로 초기화 할 수 있음
	if (clientSocket == INVALID_SOCKET)
		ShowErrorMessage("socket()");
	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1"); // 문자열 IP를 네트워크 바이트 형식으로
	//127.0.0.1은 자기자신의 컴퓨터 서버 주소
	serverAddress.sin_port = htons(serverPort); //2바이트 정수 네트워크 바이트 형식으로
	
												
	//connet(소켓변수, 서버주소 구조체, 서버 주소 구조체 크기)
	if (connect(clientSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
		ShowErrorMessage("connect()");
	cout << "[현재 상태] connect()\n";
	/*클라이언트 측에서 서버에 연결을 요청. 소켓 생성에 실패한 경우 -1을 반환	
	-IPv4 소켓 주소 구조체: 소켓 주소체계(sin_family),포트번호(sin_port),IPv4주소(sin_addr)
	실제로 소켓 주소 구조체를 이용할 때는 IPv4 소켓 주소 구조체를 일반 소켓 구조체(SOCKADDR)로 변환하여 사용해야함
	*/

	while (1) { //반복적으로 서버로 메세지를 전송하고 에코 메시지를 전달 받습니다.
		cout << "[메시지 전송]: ";
		getline(cin, sent);
		if (sent == "")continue;
		send(clientSocket, sent.c_str(), sent.length(), 0); //string->c언어 타입으로 변환(c_str)
		int length = recv(clientSocket, reveived, sizeof(reveived), 0);
		reveived[length] = '\0';
		if (strcmp(reveived, "[exit]") == 0) {
			cout << "[서버 종료]\n";
			break;
		}
		cout << "[서버 메시지]: " << reveived << '\n';
	}
	closesocket(clientSocket);
	WSACleanup();
	system("pause");
	return 0;
	//WSACleanup() Winsock을 더이상 사용하지 않겠다.
	

}