#include <iostream>
#include <string>
#include <WinSock2.h>

using namespace std;

void ShowErrorMessage(string message) {
	cout << "[���� �߻�]: " << message << '\n';
	system("pause");
	exit(1);
}

int main() {

	//connet(���Ϻ���, �����ּ� ����ü, ���� �ּ� ����ü ũ��)

	/*Ŭ���̾�Ʈ ������ ������ ������ ��û. ���� ������ ������ ��� -1�� ��ȯ
	
	-IPv4 ���� �ּ� ����ü: ���� �ּ�ü��(sin_family),��Ʈ��ȣ(sin_port),IPv4�ּ�(sin_addr)
	������ ���� �ּ� ����ü�� �̿��� ���� IPv4 ���� �ּ� ����ü�� �Ϲ� ���� ����ü(SOCKADDR)�� ��ȯ�Ͽ� ����ؾ���

	*/
	//WSAStartuo(���� ����, WSA �����ͺ���)
	//����� Winsock ������ ����. ���� ���� ������ �ޱ� ���� WSADATA ������ �Բ� �־���
	
	//WSACleanup() Winsock�� ���̻� ������� �ʰڴ�.
	

}