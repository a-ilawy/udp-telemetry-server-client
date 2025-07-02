#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>
#include <ctime>
#include <thread>
#include <cstdlib>

#pragma comment(lib, "ws2_32.lib")


float randomFloat(float min, float max) {
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <sensor_name>\n";
        return 1;
    }

    std::string deviceId = argv[1];

    // Initialize Winsock
    WSADATA wsaData;
    int wsaResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (wsaResult != 0) {
        std::cerr << "WSAStartup failed: " << wsaResult << "\n";
        return 1;
    }

    // Create UDP socket
    SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Socket creation failed\n";
        WSACleanup();
        return 1;
    }

    // Define server address
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5005);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr); //server IP

    srand(static_cast<unsigned int>(time(0))); 

    while (true) {
        // Generate random telemetry values
        float temperature = randomFloat(20.0, 60.0); // Example: 20°C to 60°C
        float humidity = randomFloat(30.0, 70.0);    // Example: 30% to 70%

        std::time_t timestamp = std::time(nullptr);

        // Create JSON string
        std::string json = "{\n"
            "\"device_id\":\"" + deviceId + "\",\n"
            "\"timestamp\":" + std::to_string(timestamp) + ",\n" +
            "\"temperature\":" + std::to_string(temperature) + ",\n" +
            "\"humidity\":" + std::to_string(humidity) +
        "\n}";

        // Send data
        int sentBytes = sendto(sock, json.c_str(), json.size(), 0,
            (sockaddr*)&serverAddr, sizeof(serverAddr));

        if (sentBytes == SOCKET_ERROR) {
            std::cerr << "Send failed: " << WSAGetLastError() << "\n";
        } else {
            std::cout << "[" << deviceId << "] Sent telemetry: " << json << "\n\n";
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}


// Compile to get .exe file 
// g++ client.cpp -o client.exe -lws2_32
// Note if the server stopped the client will keep running and sending UDP packets
// because 
//      UDP is connectionless – the client doesn't establish or maintain a connection with the server.
