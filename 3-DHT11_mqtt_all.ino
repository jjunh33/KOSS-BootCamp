#include <ESP8266WiFi.h> // Wifi 라이브러리 추가
#include <PubSubClient.h> // MQTT client 라이브러리 
#include "DHT.h" //DHT11 라이브러리 추가

DHT dht(D3, DHT11); // D3번 핀에 연결된 DHT11센서를 dht라는 객체로 생성
int led_pin = D5; //led 핀 설정

const char* ssid = "KMU_SW"; //사용하는 Wifi 이름
const char* password = "kookminsw"; // 비밀번호
const char* mqtt_server = "192.168.xxx.xxx"; //mqtt 서버 주소(라즈베리파이에서 ifconfig로 inet 주소 확인)**꼭 수정!!!!!!!!!!!!!
const char* clientName = "030404Client"; // client 이름(생일 추천드려요~)

WiFiClient espClient; // 인터넷과 연결할 수 있는 client 생성
PubSubClient client(espClient); // 해당 client를 mqtt client로 사용할 수 있도록 설정

//Wifi 연결
void setup_wifi() {
   delay(10);
   Serial.println();
   Serial.print("Connecting to ");
   Serial.println(ssid);
   WiFi.mode(WIFI_STA);
   WiFi.begin(ssid, password);
   while(WiFi.status() != WL_CONNECTED)
   {
     delay(500);
     Serial.print(".");
   }
   Serial.println("");
   Serial.println("WiFi connected");
   Serial.println("IP address: ");
   Serial.println(WiFi.localIP()); 
}

//메시지가 들어왔을 때 처리하는 callback 함수
void callback(char* topic, byte* payload, unsigned int uLen) {
  char pBuffer[uLen+1];
  int i;
  for(i = 0; i < uLen; i++)
  {
    pBuffer[i]=(char)payload[i];
  }
  Serial.println(pBuffer); // 1 or 2
  if(pBuffer[0]=='1')
  {
    digitalWrite(led_pin, HIGH); // 1이면 led 켜기
  }
  else if(pBuffer[0]=='2')
  {
    digitalWrite(led_pin, LOW); // 2면 led 끄기
  } 
}

//mqtt 연결
void reconnect() {
  //연결될 때까지 시도
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(clientName))
    {
      //연결 성공
      Serial.println("connected");
      client.subscribe("led"); // led 토픽 구독
    } 
    else 
    {
      //연결실패하면 현재 상태 출력하고 5초 후 다시 시도
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  pinMode(led_pin, OUTPUT);
  Serial.begin(115200);//시리얼 통신 시작
  Serial.println("Start sensor");
  dht.begin(); //dht센서 가동
  setup_wifi(); //Wifi 연결
  client.setServer(mqtt_server, 1883); //mqtt 서버와 연결(ip, 1883)
  client.setCallback(callback); //callback 함수 세팅
}

void loop() {
  if (!client.connected())
  {
    reconnect(); //mqtt 연결이 안되어있다면 다시 연결
  }
  client.loop(); //연결을 계속해서 유지하고 들어오는 메시지를 확인할 수 있도록 함
  float t = dht.readTemperature(); //섭씨 온도 가져오기(dht.readTemperature(true) -> 화씨 온도)
  float h = dht.readHumidity(); //습도 가져오기

  char message[50] = ""; // 문자열을 위한 공간 마련
  sprintf(message, "{\"tmp\":%f,\"humi\":%f}", t, h); //JSON 문자열의 형식으로 온도, 습도 데이터 담기

  Serial.print("Publish message: ");
  Serial.println(message);
  client.publish("dht", message); // 만든 문자열을 mqtt 서버에 publish *토픽에 숫자 XXX
  
  delay(3000); // 3초(3000ms) 주기
}
