#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <chrono>
#include <ctime>
#include <thread>
#include <ctime>
#include <opencv2/opencv.hpp>
#include <vector>
#include <mutex>

const int BUFFER_SIZE = 4096;
const int PORT = 8081; // 사용할 포트 번호

// 간단한 HTML 웹 페이지 생성 함수
std::string generateHTML()
{
    std::string html = R"(
<!DOCTYPE html>
<html>
<head>
    <title>SSE Example</title>
</head>
<body>
    <h1>SSE Example</h1>
    <p id="sse-data"></p>
    <script>
        const sseData = document.getElementById('sse-data');

        // SSE 연결
        const eventSource = new EventSource('/stream');
        eventSource.onmessage = function(event) 
        {
            sseData.innerHTML = event.data;
        };
    </script>

    
</body>
</html>
    )";
    return html;
}

std::string readFile(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file)
    {
        throw std::runtime_error("파일을 열 수 없습니다.");
    }

    return std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
}

static const std::string base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

std::string base64_encode(const unsigned char *data, size_t length)
{
    std::string encoded;
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    while (length--)
    {
        char_array_3[i++] = *(data++);
        if (i == 3)
        {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (i = 0; (i < 4); i++)
                encoded += base64_chars[char_array_4[i]];
            i = 0;
        }
    }

    if (i)
    {
        for (j = i; j < 3; j++)
            char_array_3[j] = '\0';

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);

        for (j = 0; (j < i + 1); j++)
            encoded += base64_chars[char_array_4[j]];

        while ((i++ < 3))
            encoded += '=';
    }

    return encoded;
}

std::mutex mutex;
std::string generateJPG()
{
    std::unique_lock<std::mutex> lock(mutex);
    // 이미지 생성 또는 이미지 파일에서 이미지를 가져오는 로직을 여기에 추가
    // 여기서는 간단히 빈 이미지를 생성하여 사용합니다.
    // cv::Mat image(480, 640, CV_8UC3, cv::Scalar(255, 255, 255));

    static cv::VideoCapture cap(0);
    // 가로 640, 세로 480 크기의 빈 이미지 생성
    // cv::Mat image(480, 640, CV_8UC3, cv::Scalar(255, 255, 255));
    cv::Mat image;
    cap >> image;
    if (image.size().width == 0)
        return std::string(); // simple integrity check; skip erroneous data...
    cv::resize(image, image, cv::Size(1280, 1024));

    cv::Point center(rand() % image.cols / 2, rand() % image.rows / 2);
    cv::circle(image, center, 100, cv::Scalar(0, 0, 255), -1);

    // 이미지를 JPG 형식으로 인코딩
    std::vector<uchar> buffer;
    cv::imencode(".jpg", image, buffer);

    // 인코딩된 이미지 데이터를 Base64로 인코딩하여 반환
    std::string base64_image = base64_encode(buffer.data(), buffer.size());
    return base64_image;
}

const std::string SSE_HEADERS =
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/event-stream\r\n"
    "Cache-Control: no-cache\r\n"
    "Connection: keep-alive\r\n\r\n"
    "event: message\r\n";
//  "data: Hello, World!\r\n\r\n";

uint32_t packetSize = 0;
uint32_t streamSpeed = 1;
// SSE 스트리밍 처리
void sseStreaming1(int clientSock)
{
    send(clientSock, SSE_HEADERS.c_str(), SSE_HEADERS.length(), 0);
    const int MAX_BUFFER_SIZE = 10000;
    uint8_t m_buff[MAX_BUFFER_SIZE];
    while (true)
    {

        if (recv(clientSock, m_buff, MAX_BUFFER_SIZE, MSG_DONTWAIT) == 0)
        {
            close(clientSock);
            clientSock = 0;
            printf("end\n");
            return;
        }

        std::time_t now = std::time(nullptr);

        // 이미지 데이터를 클라이언트로 보냄
        // std::string response = "data: Hello, World!\r\n\r\n";
        std::string response;
        response = "data: Hello";
        response += std::ctime(&now);
        response += "\r\n\r\n";
        send(clientSock, response.c_str(), response.length(), 0);
        packetSize += response.length();

        // 1초마다 이미지 갱신
        usleep(100000 * streamSpeed);
    }
}

void sseStreaming2(int clientSock)
{
    send(clientSock, SSE_HEADERS.c_str(), SSE_HEADERS.length(), 0);
    const int MAX_BUFFER_SIZE = 10000;
    uint8_t m_buff[MAX_BUFFER_SIZE];
    while (true)
    {

        if (recv(clientSock, m_buff, MAX_BUFFER_SIZE, MSG_DONTWAIT) == 0)
        {
            close(clientSock);
            clientSock = 0;
            printf("end\n");
            return;
        }

        std::string jpgData = generateJPG();
        // 이미지 데이터를 클라이언트로 보냄
        std::string response = "data: " + jpgData + "\r\n\r\n";
        send(clientSock, response.c_str(), response.length(), 0);
        packetSize += response.length();

        // 1초마다 이미지 갱신
        usleep(100000 * streamSpeed);
    }
}

void speadCk(int value)
{
    while (1)
    {
        packetSize = 0;
        sleep(1);
        float MB = packetSize / 1024000.0;
        printf("MB: %f \n", MB);
        if (MB > 1)
            streamSpeed = MB;
        else
            streamSpeed = 1;
    }
}

int main()
{
    // 소켓 생성
    int serverSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSock == -1)
    {
        std::cerr << "Socket creation failed" << std::endl;
        return 1;
    }

    // 서버 주소 설정
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    // 소켓에 주소 바인딩
    if (bind(serverSock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        std::cerr << "Bind failed" << std::endl;
        return 1;
    }

    // 소켓 수신 대기
    if (listen(serverSock, 1) < 0)
    {
        std::cerr << "Listen failed" << std::endl;
        return 1;
    }

    std::cout << "Server listening on port " << PORT << std::endl;

    // std::thread(speadCk, 0).detach();

    bool firstResponse = false;
    while (true)
    {
        // 클라이언트 연결 수락
        int clientSock = accept(serverSock, nullptr, nullptr);
        if (clientSock < 0)
        {
            std::cerr << "Accept failed" << std::endl;
            return 1;
        }

        // HTTP 요청 처리
        char buffer[BUFFER_SIZE];
        memset(buffer, 0, sizeof(buffer));
        int bytesRead = recv(clientSock, buffer, sizeof(buffer) - 1, 0);
        if (bytesRead > 0)
        {
            printf("buffer: %s\n", buffer);
            // 클라이언트에게 응답 전송
            if (strstr(buffer, "GET / HTTP"))
            {
                std::string response;
                response = "HTTP/1.1 200 OK\r\n";
                response += "Content-Type: text/html\r\n\r\n";
                // response += generateHTML();
                response += readFile("index.html");
                send(clientSock, response.c_str(), response.length(), 0);
                close(clientSock);
                continue;
            }

            if (strstr(buffer, "text/event-stream"))
            {
                if (strstr(buffer, "GET /stream1"))
                {
                    // 클라이언트에 SSE 헤더 전송
                    std::thread streamingThread(sseStreaming1, clientSock);
                    streamingThread.detach();
                    continue;
                }
                else if (strstr(buffer, "GET /stream2"))
                {
                    // 클라이언트에 SSE 헤더 전송
                    std::thread streamingThread(sseStreaming2, clientSock);
                    streamingThread.detach();
                    continue;
                }
            }

            close(clientSock);
        }
    }
    // 서버 소켓 닫기
    close(serverSock);

    return 0;
}
