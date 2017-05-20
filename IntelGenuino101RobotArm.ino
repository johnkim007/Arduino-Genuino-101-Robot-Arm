/*
 차량 장착용 수평집게
*/
#include "CurieIMU.h"

#include <Servo.h>
Servo servo1;  // 집게 서보
Servo servo2;  // 올리는 서보
#define Servo1Pin 5	  // 집게 서보 모터 오렌지핀에 연결
#define Servo2Pin 6   // 올리는 서보 모터 오렌지핀에 연결  

void Accelerometer(){
	int x, y, z, accX, accY;
    x = CurieIMU.readAccelerometer(X_AXIS); // X축 가속 읽기
    y = CurieIMU.readAccelerometer(Y_AXIS); // Y축 가속 읽기
    z = CurieIMU.readAccelerometer(Z_AXIS); // Z축 가속 읽기

	// 가속기 최소 최대 범위 제한 설정
	if(x > 15000)  x=13000;
	if(x < -15000) x=-13000;
	if(y > 15000)  x=13000;
	if(y < -15000) x=-13000;

	// 가속기 최대 최소값을 0~179 범위내로 변환
	accX = map(x, -13000, 13000, 10, 169);
	accY = map(y, -13000, 13000, 10, 169);

	servo1.write(accX); // 변환된 X 값 서보에 적용 동작
	servo2.write(accY); // 변환된 X 값 서보에 적용 동작

	Serial.print(accX);
	Serial.print(" / ");
	Serial.println(accY);
	delay(100);
}

void setup() {
    Serial.begin(9600);                   // 시리얼 초기화
    CurieIMU.begin();                      // 가속기 초기화
    CurieIMU.setAccelerometerRange(2); // 가속기 범위 설정
    pinMode(Servo1Pin, OUTPUT);           // 서버1 핀 출력설정
    pinMode(Servo2Pin, OUTPUT);           // 서버2 핀 출력설정
	servo1.attach(Servo1Pin);               // 서버1 핀 연결설정
	servo2.attach(Servo2Pin);               // 서버2 핀 연결설정
}

void loop() {
	Accelerometer();
}
