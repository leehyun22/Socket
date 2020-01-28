#include <iostream>
#include <string>
#include <WinSock2.h>
#include <string.h>
#define SIZE 256
using namespace std;

void ShowErrorMessage(string message) {
	cout << "[���� �߻�]: " << message << '\n';
	system("pause");
	exit(1);
}

int main() {

	WSADATA wsaData;
	SOCKET serverSocket, clientSocket;
	SOCKADDR_IN serverAddress, clientAddress;
	int serverPort = 9876;
	char received[SIZE];
	//WSAStartuo()�Լ� ���� ���� ȯ�� ������ �����ؾ���
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ShowErrorMessage("WSAStartup()");

	//socket(��Ʈ��ũ �ּ� ü��, ����Ÿ��, ��������)
	serverSocket = socket(PF_INET, SOCK_STREAM, 0);
	//PF_INET->AF_INET, SOCK_STREAM -> TCP ���� ����
	//������ �����ϴ� �Լ�, ���Լ��� '��Ʈ��ũ �ּ� ü��', '���� Ÿ��','��������'�� �ʱ�ȭ �� �� ����
	if (serverSocket == INVALID_SOCKET)
		ShowErrorMessage("socket()");
	//���� ������ �����ϴ� ��� -1 ��ȯ
	//-��Ʈ��ũ �ּ� ü��: IPv4(AF_INET),IPv6(AF_INET6)
	//-����Ÿ��:TCP(SOCK_STREAM),UDP(SOCK_DGRAM)
	//-��������:TCP(IPPROPTO_TCP),UDP(IPPROTO_UDP)
	
	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY); //4����Ʈ ������ ��Ʈ��ũ ����Ʈ �������� 
	serverAddress.sin_port = htons(serverPort); //2����Ʈ ���� ��Ʈ��ũ ����Ʈ ��������
	
	//bind(���Ϻ���, ���� �ּ� ����ü,�����ּ� ����ü�� ũ��)
	if (bind(serverSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
		ShowErrorMessage("bind()");
	cout << "[���� ����] bind()\n";
	/*���� ���� ���Ͽ� IP�� ��Ʈ ��ȣ�� �Ҵ��Ͽ� ��Ʈ��ũ �������̽��� ���� �� �ֵ��� ��
	-IPv4���� �ּ� ����ü(SOCKADDR_IN): ���� �ּ�ü��(sin_family),��Ʈ(sin_port),IPv4�ּ�(sin_addr)
	������ ���� �ּ� ����ü�� �̿��� ���� IPv4 ���� �ּ� ����ü�� �Ϲ� ���� ����ü(SOCKADDR)�� ��ȯ�Ͽ� ����ؾ���
	*/

	//listen(���Ϻ���,�� �α� ť�� ũ��)
	if (listen(serverSocket, 5) == SOCKET_ERROR)
		ShowErrorMessage("listen()");

	/*Ŭ���̾�Ʈ�κ��� ���� ��û�� ��ٸ�. ��α׶� ���ÿ� ������ �õ��ϴ� �ִ� Ŭ���̾�Ʈ ���� �ǹ���.*/
	
	int sizeClientAddress = sizeof(clientAddress);
	clientSocket = accept(serverSocket, (SOCKADDR*)&clientAddress, &sizeClientAddress);
	//accept(���� ����, Ŭ���̾�Ʈ �ּ� ����ü ����, Ŭ���̾�Ʈ �ּ� ����ü ũ��)
	cout << "[���� ����] accept()\n";

	/*���������� Ŭ���̾�Ʈ�� ������ ����, accpet()�Լ� ���ο��� Ŭ���̾�Ʈ �ּҸ� ������ �ڿ� ��ſ�
	����� Ŭ���̾�Ʈ�� ������ ��ȯ��, ������ �߻��� ��� -1 ��ȯ
	������ ���� �ּ� ����ü�� �̿��� ���� IPv4 ���� �ּ� ����ü�� �Ϲ� ���� ����ü(SOCKADDR)�� ��ȯ�Ͽ� ����ؾ���
	*/
	if (clientSocket == INVALID_SOCKET)
		ShowErrorMessage("accept()'\n");
	while (1) {

		int length = recv(clientSocket, received, sizeof(received), 0);
		//recv(���� ����, ���ڿ� ����, ���ڿ� ����ũ��, �÷���)
		/*�����͸� �����Ͽ� Ư�� ���ۿ� ��´�. �÷��״� Ư���� ��찡 �ƴ϶�� 0�� ����. ������ ���ſ� �����ϴ� ��� -1��ȯ*/
		received[length] = NULL;
		cout << "[Ŭ���̾�Ʈ �޽���]: " << received << '\n';
		cout << "[�޽��� ����]: " << received << '\n';
		if (strcmp(received, "[exit]") == 0) {
			send(clientSocket, received, sizeof(received) - 1, 0);
			//send(���Ϻ���, ���ڿ� ����, ���ڿ� ���� ũ��,�÷���)
			/*���濡�� �����͸� ����.Ư���� �������� ���ڿ� ���ۿ� ��� ������ ����. �÷��״� Ư���� ��찡
			�ƴ϶�� 0�� ����. ������ ���ۿ� �����ϴ� ��� -1 ��ȯ*/
			cout << "[���� ����]\n";
			break;
		}
		send(clientSocket, received, sizeof(received) - 1, 0);
	}


	//closesocket(���Ϻ���) ���� ������ �ݴ´�.
	closesocket(clientSocket);
	closesocket(serverSocket);
	WSACleanup();
	system("pause");
	//Winsock2

	//windows socket api�� �ظ� ��Ʈ��ũ ���α׷����� ���� ���̺귯��. ws2_32.dll������ ��뼳��
	return 0;


}