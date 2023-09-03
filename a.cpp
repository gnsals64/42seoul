#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

const int PORT = 8080;
const int MAX_BUFFER_SIZE = 1024;

void saveBinaryData(const char* filename, const char* data, size_t dataSize) {
    const char* homeDir = getenv("HOME");
    std::string savePath = std::string(homeDir) + "/42seoul/webserv/" + std::string(filename);
    std::ofstream file(savePath.c_str(), std::ios::out | std::ios::binary);
    if (file) {
        file.write(data, dataSize);
        file.close();
        std::cout << "2진 파일 저장 완료: " << filename << std::endl;

        // 파일에 저장된 이진 데이터를 std::cout으로 출력
        std::cout.write(data, dataSize);
    } else {
        std::cerr << "2진 파일 저장 실패: " << filename << std::endl;
    }
}

int main() {
    int serverSocket, clientSocket;
    socklen_t clientLength;
    struct sockaddr_in serverAddr, clientAddr;
    char buffer[MAX_BUFFER_SIZE];

    // 서버 소켓 생성
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "서버 소켓 생성 실패" << std::endl;
        return 1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    // 서버 주소와 포트 바인딩
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "바인딩 실패" << std::endl;
        return 1;
    }

    // 클라이언트 연결 대기
    listen(serverSocket, 5);
    std::cout << "서버가 " << PORT << " 포트에서 대기 중..." << std::endl;

    while (true) {
        clientLength = sizeof(clientAddr);

        // 클라이언트 연결 수락
        clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientLength);
        if (clientSocket < 0) {
            std::cerr << "클라이언트 연결 수락 실패" << std::endl;
            return 1;
        }

        memset(buffer, 0, sizeof(buffer));

        // 클라이언트로부터 요청 데이터 읽기
        ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);

        if (bytesRead < 0) {
            std::cerr << "데이터 읽기 실패" << std::endl;
            return 1;
        }

        // 요청 본문을 2진 파일로 저장 (예: "uploaded_binary_file.bin")
        saveBinaryData("uploaded_binary_file.bin", buffer, bytesRead);

        close(clientSocket);
    }

    close(serverSocket);
    return 0;
}