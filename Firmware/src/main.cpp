/**
 * Intelligent Patient Health Monitoring with-IoT
 * Sensor used  : LM35, Blood Pressure (simulasi using potensiometer)
 * Database     : Firebase RTDB
 *
 * @author  Ira Adi Nata
 * @version v2024.10.07
 */


#include <WiFi.h>
#include <MQTT.h>
#include <NusabotSimpleTimer.h>

const char *ssid = "Wokwi-GUEST"; 
const char *password = "";         

const int potPin1 = 34;            // LM35 
const int potPin2 = 35;            // LM35
const int potPin3 = 32;            // Pulse sensor
int potValue1 = 0;
int potValue2 = 0;
int potValue3 = 0;

WiFiClient net;
MQTTClient client;
NusabotSimpleTimer timer;

//batas
HX711 scale;

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

const int LOADCELL_DOUT_PIN = 16;
const int LOADCELL_SCK_PIN = 4;

#define RXD2 16
#define TXD2 17

int data_sys = 0, data_dia = 0, data_bpm = 0, data_weight = 0, data_ambient = 0, data_temperature = 0;
uint8_t datasend[13] = {0};

char buff[64];
bool b_read, b_discard;
char discard;
int i, j = 0;
char final_buff[64];
int last_state = 0;
int hexSys = 0, hexDias = 0, hexBPM = 0;

void get_blood()
{
  if (Serial2.available())
  {
    if (b_read == 0)
    {
      buff[0] = Serial2.read();
      if (buff[0] == 'e')
      {
        buff[1] = Serial2.read();
        if (buff[1] == 'r')
        {
          buff[2] = Serial2.read();
          if (buff[2] == 'r')
          {
            buff[3] = Serial2.read();
            if (buff[3] == ':')
            {
              buff[4] = Serial2.read();
              if (buff[4] == '0')
              {
                b_read = 1;
                j = 0;
                b_discard = 0;
                i = 0;
              }
            }
          }
        }
      }
    }
    // Serial.println(buff);
    if (b_read)
    {
      if (b_discard == 0)
      {
        discard = Serial2.read();
        i++;
      }
      else if (j < 11)
      {
        final_buff[j] = Serial2.read();
        j++;
      }
      else
      {
        b_read = 0;
      }
      if (i == 30)
      {
        b_discard = 1;
      }
    }
  }

  if (final_buff[0] > '9')
  {
    hexSys = (final_buff[0] - '7') * 16;
  }
  else
  {
    hexSys = (final_buff[0] - '0') * 16;
  }
  if (final_buff[1] > '9')
  {
    hexSys += (final_buff[1] - '7');
  }
  else
  {
    hexSys += (final_buff[1] - '0');
  }

  if (final_buff[3] > '9')
  {
    hexDias = (final_buff[3] - '7') * 16;
  }
  else
  {
    hexDias = (final_buff[3] - '0') * 16;
  }
  if (final_buff[4] > '9')
  {
    hexDias += (final_buff[4] - '7');
  }
  else
  {
    hexDias += (final_buff[4] - '0');
  }

  if (final_buff[9] > '9')
  {
    hexBPM = (final_buff[9] - '7') * 16;
  }
  else
  {
    hexBPM = (final_buff[9] - '0') * 16;
  }
  if (final_buff[10] > '9')
  {
    hexBPM += (final_buff[10] - '7');
  }
  else
  {
    hexBPM += (final_buff[10] - '0');
  }

  Serial.printf("state: %d, sys: %-3d, dia: %-3d, BPM: %-3d \n", b_read, hexSys, hexDias, hexBPM);
  if (b_read == 0 && last_state == 1)
  {
    data_sys = hexSys;
    data_dia = hexDias;
    data_bpm = hexBPM;
  }
  last_state = b_read;
}

void connectWiFi() {
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }


  Serial.println("\nConnected to WiFi!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void connectMQTT() {
  Serial.print("Connecting to MQTT...");
  while (!client.connect("esp32", "lifesyncpens", "vGd5J6PcFyYpOnOn")) {
    Serial.print(".");
    delay(1000); 
  }
  Serial.println("\nConnected to MQTT broker!");
}

void publishData() {
  client.publish("belajar/iot/suhu", String(potValue1), false, 1);
  client.publish("belajar/iot/pulse", String(potValue3), false, 1);
}

void setup() {
  Serial.begin(115200);

  
  pinMode(potPin1, INPUT);
  pinMode(potPin2, INPUT);
  pinMode(potPin3, INPUT);

  connectWiFi();
  client.begin("lifesyncpens.cloud.shiftr.io", net);   connectMQTT();


  timer.setInterval(1000, publishData);
}

void loop() {

  potValue1 = analogRead(potPin1);
  potValue2 = analogRead(potPin2);
  potValue3 = analogRead(potPin3);


  Serial.print("Potentiometer Value1: ");
  Serial.println(potValue1);
  Serial.print("Potentiometer Value2: ");
  Serial.println(potValue2);
  Serial.print("Potentiometer Value3: ");
  Serial.println(potValue3);

  if (!client.connected()) {
    connectMQTT();
  }
  client.loop();

  timer.run();
}

