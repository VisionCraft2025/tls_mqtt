# MQTT GUI Client

Qt6 Widgets를 사용한 TLS 암호화 MQTT GUI 클라이언트

## 빌드 방법

```bash
mkdir build && cd build
export CMAKE_PREFIX_PATH="../qt6_local/usr/lib/x86_64-linux-gnu/cmake:/usr/lib/x86_64-linux-gnu/cmake"
cmake .. -DQT_NO_PACKAGE_VERSION_CHECK=TRUE
make
```

## 실행 방법

```bash
# ca.crt 파일을 build 디렉토리에 복사
cp ../build_cmake/ca.crt .

# Publisher GUI 실행
./mqtt_pub_gui

# Subscriber GUI 실행
./mqtt_sub_gui
```

## 기능

- **공통**: 토픽 입력, 연결/해제, 상태 표시
- **Publisher**: 메시지 입력 및 발행, 로그 출력
- **Subscriber**: 토픽 구독/해제, 실시간 메시지 수신