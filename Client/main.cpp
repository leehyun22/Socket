#include <iostream>
#include <string>
#include <WinSock2.h>

using namespace std;

void ShowErrorMessage(string message) {
	cout << "[오류 발생]: " << message << '\n';
	system("pause");
	exit(1);
}

int main() {

	//connet(소켓변수, 서버주소 구조체, 서버 주소 구조체 크기)

	/*클라이언트 측에서 서버에 연결을 요청. 소켓 생성에 실패한 경우 -1을 반환
	
	-IPv4 소켓 주소 구조체: 소켓 주소체계(sin_family),포트번호(sin_port),IPv4주소(sin_addr)
	실제로 소켓 주소 구조체를 이용할 때는 IPv4 소켓 주소 구조체를 일반 소켓 구조체(SOCKADDR)로 변환하여 사용해야함

	*/
	//WSAStartuo(윈속 버전, WSA 데이터변수)
	//사용할 Winsock 버전을 설정. 관련 설정 정보를 받기 위해 WSADATA 변수를 함께 넣어줌
	
	//WSACleanup() Winsock을 더이상 사용하지 않겠다.
	

}