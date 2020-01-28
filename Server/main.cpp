#include <iostream>
#include <string>
#include <WinSock2.h>
#include <string.h>
#define SIZE 256
using namespace std;

void ShowErrorMessage(string message) {
	cout << "[오류 발생]: " << message << '\n';
	system("pause");
	exit(1);
}

int main() {

	WSADATA wsaData;
	SOCKET serverSocket, clientSocket;
	SOCKADDR_IN serverAddress, clientAddress;
	int serverPort = 9876;
	char received[SIZE];
	//WSAStartuo()함수 등을 통해 환경 설정을 진행해야함
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ShowErrorMessage("WSAStartup()");

	//socket(네트워크 주소 체계, 소켓타입, 프로토콜)
	serverSocket = socket(PF_INET, SOCK_STREAM, 0);
	//PF_INET->AF_INET, SOCK_STREAM -> TCP 소켓 생성
	//소켓을 생성하는 함수, 이함수는 '네트워크 주소 체계', '소켓 타입','프로토콜'로 초기화 할 수 있음
	if (serverSocket == INVALID_SOCKET)
		ShowErrorMessage("socket()");
	//소켓 생성에 실패하는 경우 -1 반환
	//-네트워크 주소 체계: IPv4(AF_INET),IPv6(AF_INET6)
	//-소켓타입:TCP(SOCK_STREAM),UDP(SOCK_DGRAM)
	//-프로토콜:TCP(IPPROPTO_TCP),UDP(IPPROTO_UDP)
	
	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY); //4바이트 정수를 네트워크 바이트 형식으로 
	serverAddress.sin_port = htons(serverPort); //2바이트 정수 네트워크 바이트 형식으로
	
	//bind(소켓변수, 서버 주소 구조체,서버주소 구조체의 크기)
	if (bind(serverSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
		ShowErrorMessage("bind()");
	cout << "[현재 상태] bind()\n";
	/*서버 측의 소켓에 IP와 포트 번호를 할당하여 네트워크 인터페이스와 묶일 수 있도록 함
	-IPv4소켓 주소 구조체(SOCKADDR_IN): 소켓 주소체계(sin_family),포트(sin_port),IPv4주소(sin_addr)
	실제로 소켓 주소 구조체를 이용할 때는 IPv4 소켓 주소 구조체를 일반 소켓 구조체(SOCKADDR)로 변환하여 사용해야함
	*/

	//listen(소켓변수,백 로그 큐의 크기)
	if (listen(serverSocket, 5) == SOCKET_ERROR)
		ShowErrorMessage("listen()");

	/*클라이언트로부터 연결 요청을 기다림. 백로그란 동시에 연결을 시도하는 최대 클라이언트 수를 의미함.*/
	
	int sizeClientAddress = sizeof(clientAddress);
	clientSocket = accept(serverSocket, (SOCKADDR*)&clientAddress, &sizeClientAddress);
	//accept(소켓 변수, 클라이언트 주소 구조체 변수, 클라이언트 주소 구조체 크기)
	cout << "[현재 상태] accept()\n";

	/*서버측에서 클라이언트의 연결을 수락, accpet()함수 내부에서 클라이언트 주소를 설정한 뒤에 통신에
	사용할 클라이언트의 소켓을 반환함, 오류가 발생할 경우 -1 반환
	실제로 소켓 주소 구조체를 이용할 때는 IPv4 소켓 주소 구조체를 일반 소켓 구조체(SOCKADDR)로 변환하여 사용해야함
	*/
	if (clientSocket == INVALID_SOCKET)
		ShowErrorMessage("accept()'\n");
	while (1) {

		int length = recv(clientSocket, received, sizeof(received), 0);
		//recv(소켓 변수, 문자열 버퍼, 문자열 버퍼크기, 플래그)
		/*데이터를 수신하여 특정 버퍼에 담는다. 플래그는 특별한 경우가 아니라면 0을 설정. 데이터 수신에 실패하는 경우 -1반환*/
		received[length] = NULL;
		cout << "[클라이언트 메시지]: " << received << '\n';
		cout << "[메시지 전송]: " << received << '\n';
		if (strcmp(received, "[exit]") == 0) {
			send(clientSocket, received, sizeof(received) - 1, 0);
			//send(소켓변수, 문자열 버퍼, 문자열 버퍼 크기,플래그)
			/*상대방에게 데이터를 보냄.특정한 소켓으로 문자열 버퍼에 담긴 내용을 전송. 플래그는 특별한 경우가
			아니라면 0을 설정. 데이터 전송에 실패하는 경우 -1 반환*/
			cout << "[서버 종료]\n";
			break;
		}
		send(clientSocket, received, sizeof(received) - 1, 0);
	}


	//closesocket(소켓변수) 열린 소켓을 닫는다.
	closesocket(clientSocket);
	closesocket(serverSocket);
	WSACleanup();
	system("pause");
	//Winsock2

	//windows socket api의 준말 네트워크 프로그래밍을 위한 라이브러리. ws2_32.dll파일을 사용설정
	return 0;


}