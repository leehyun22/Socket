#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <string>
#include <WinSock2.h>
#define SIZE 256
using namespace std;

void ShowErrorMessage(string message) {
	cout << "[���� �߻�]: " << message << '\n';
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
	//WSAStartuo()�Լ� ���� ���� ȯ�� ������ �����ؾ���
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ShowErrorMessage("WSAStartup()");
	//socket(��Ʈ��ũ �ּ� ü��, ����Ÿ��, ��������)
	clientSocket = socket(PF_INET, SOCK_STREAM, 0);
	//PF_INET->AF_INET, SOCK_STREAM -> TCP ���� ����
	//������ �����ϴ� �Լ�, ���Լ��� '��Ʈ��ũ �ּ� ü��', '���� Ÿ��','��������'�� �ʱ�ȭ �� �� ����
	if (clientSocket == INVALID_SOCKET)
		ShowErrorMessage("socket()");
	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1"); // ���ڿ� IP�� ��Ʈ��ũ ����Ʈ ��������
	//127.0.0.1�� �ڱ��ڽ��� ��ǻ�� ���� �ּ�
	serverAddress.sin_port = htons(serverPort); //2����Ʈ ���� ��Ʈ��ũ ����Ʈ ��������
	
												
	//connet(���Ϻ���, �����ּ� ����ü, ���� �ּ� ����ü ũ��)
	if (connect(clientSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
		ShowErrorMessage("connect()");
	cout << "[���� ����] connect()\n";
	/*Ŭ���̾�Ʈ ������ ������ ������ ��û. ���� ������ ������ ��� -1�� ��ȯ	
	-IPv4 ���� �ּ� ����ü: ���� �ּ�ü��(sin_family),��Ʈ��ȣ(sin_port),IPv4�ּ�(sin_addr)
	������ ���� �ּ� ����ü�� �̿��� ���� IPv4 ���� �ּ� ����ü�� �Ϲ� ���� ����ü(SOCKADDR)�� ��ȯ�Ͽ� ����ؾ���
	*/

	while (1) { //�ݺ������� ������ �޼����� �����ϰ� ���� �޽����� ���� �޽��ϴ�.
		cout << "[�޽��� ����]: ";
		getline(cin, sent);
		if (sent == "")continue;
		send(clientSocket, sent.c_str(), sent.length(), 0); //string->c��� Ÿ������ ��ȯ(c_str)
		int length = recv(clientSocket, reveived, sizeof(reveived), 0);
		reveived[length] = '\0';
		if (strcmp(reveived, "[exit]") == 0) {
			cout << "[���� ����]\n";
			break;
		}
		cout << "[���� �޽���]: " << reveived << '\n';
	}
	closesocket(clientSocket);
	WSACleanup();
	system("pause");
	return 0;
	//WSACleanup() Winsock�� ���̻� ������� �ʰڴ�.
	

}