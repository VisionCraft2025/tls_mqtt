# Qt6 MQTT TLS Client

Qt6를 사용한 TLS 암호화 MQTT Publisher/Subscriber 클라이언트 구현

## 개요

이 프로젝트는 Qt6 QMqttClient를 사용하여 TLS/SSL 암호화된 MQTT 통신을 구현합니다. CA 인증서를 사용한 서버 인증을 통해 안전한 MQTT 메시지 송수신이 가능합니다.

### 주요 기능

- **TLS/SSL 암호화**: CA 인증서를 사용한 안전한 MQTT 연결
- **Publisher**: 콘솔 입력을 통한 메시지 발행
- **Subscriber**: 실시간 메시지 수신 및 출력
- **Qt6 호환**: 최신 Qt6 QMqttClient API 사용

## 시스템 요구사항

- Ubuntu 22.04 LTS (또는 호환 Linux 배포판)
- Qt6 Base Development packages
- CMake 3.16+
- GCC 11+
- Git

## 설치 및 빌드

### 1. 시스템 패키지 설치

```bash
sudo apt update
sudo apt install -y qt6-base-dev qmake6 cmake build-essential git
```

### 2. Qt6 MQTT 모듈 빌드

Qt6 MQTT 모듈은 오픈소스 사용자에게 기본 제공되지 않으므로 소스에서 빌드해야 합니다.

```bash
# 프로젝트 디렉토리로 이동
cd QT_mqtt/tls

# Qt6 MQTT 소스 다운로드
git clone https://github.com/qt/qtmqtt.git
cd qtmqtt

# Qt 6.2 브랜치로 체크아웃 (시스템 Qt 버전과 호환)
git checkout 6.2

# 빌드 디렉토리 생성 및 빌드
mkdir build && cd build
cmake .. -DQT_NO_PACKAGE_VERSION_CHECK=TRUE -DQT_NO_PACKAGE_VERSION_INCOMPATIBLE_WARNING=TRUE
make -j4

# 로컬 설치
make install DESTDIR=../../../qt6_local
```

### 3. 프로젝트 빌드

```bash
# tls 디렉토리로 이동
cd ../../

# 빌드 디렉토리 생성
mkdir build_cmake && cd build_cmake

# CMake 설정 및 빌드
export CMAKE_PREFIX_PATH="/home/$USER/Documents/QT_mqtt/tls/qt6_local/usr/lib/x86_64-linux-gnu/cmake:/usr/lib/x86_64-linux-gnu/cmake"
cmake .. -DQT_NO_PACKAGE_VERSION_CHECK=TRUE
make
```

## 인증서 설정

TLS 연결을 위해 CA 인증서가 필요합니다.

```bash
# CA 인증서를 빌드 디렉토리에 복사
cp ca.crt build_cmake/
```

## 실행 방법

### Publisher 실행

```bash
cd build_cmake
./mqtt_pub
```

실행 후 메시지를 입력하고 Enter를 누르면 `test/topic`으로 메시지가 발행됩니다.
종료하려면 `quit`을 입력하세요.

### Subscriber 실행

```bash
cd build_cmake
./mqtt_sub
```

`test/topic`을 구독하여 실시간으로 메시지를 수신합니다.

### 동시 실행 테스트

1. 터미널 1에서 Subscriber 실행:
```bash
./mqtt_sub
```

2. 터미널 2에서 Publisher 실행:
```bash
./mqtt_pub
```

3. Publisher에서 메시지 입력 시 Subscriber에서 실시간 수신 확인

## 설정

### MQTT 브로커 설정

`publisher.cpp`와 `subscriber.cpp`에서 브로커 정보 수정:

```cpp
m_client->setHostname("your-mqtt-broker.com");  // 브로커 주소
m_client->setPort(8883);                        // TLS 포트
```

### 토픽 설정

기본 토픽은 `test/topic`입니다. 변경하려면:

```cpp
// Publisher
m_client->publish(QMqttTopicName("your/topic"), input.toUtf8())

// Subscriber  
m_client->subscribe(QMqttTopicFilter("your/topic"))
```

## 프로젝트 구조

```
QT_mqtt/
├── tls/
│   ├── build_cmake/          # 빌드 출력 디렉토리
│   ├── qtmqtt/              # Qt6 MQTT 소스
│   ├── qt6_local/           # 로컬 Qt6 MQTT 설치
│   ├── CMakeLists.txt       # CMake 설정
│   ├── publisher.h/cpp      # Publisher 구현
│   ├── subscriber.h/cpp     # Subscriber 구현
│   ├── main_pub.cpp         # Publisher 메인
│   ├── main_sub.cpp         # Subscriber 메인
│   └── ca.crt              # CA 인증서
└── README.md
```

## 문제 해결

### Qt6 MQTT 모듈을 찾을 수 없는 경우

```bash
export CMAKE_PREFIX_PATH="/home/$USER/Documents/QT_mqtt/tls/qt6_local/usr/lib/x86_64-linux-gnu/cmake:$CMAKE_PREFIX_PATH"
```

### SSL 연결 오류

1. CA 인증서 파일 경로 확인
2. 브로커의 TLS 설정 확인
3. 방화벽 포트 8883 개방 확인

### 빌드 오류

Qt6 버전 호환성 문제 시:
```bash
cmake .. -DQT_NO_PACKAGE_VERSION_CHECK=TRUE -DQT_NO_PACKAGE_VERSION_INCOMPATIBLE_WARNING=TRUE
```

## 라이선스

이 프로젝트는 Qt6 MQTT 모듈의 GPLv3 라이선스를 따릅니다.

## 기술 스택

- **Qt6**: GUI 프레임워크 및 네트워크 라이브러리
- **QMqttClient**: Qt6 MQTT 클라이언트 라이브러리
- **QSslConfiguration**: TLS/SSL 암호화 설정
- **CMake**: 빌드 시스템
- **C++17**: 프로그래밍 언어