/**
 * Intelligent Patient Health Monitoring with-IoT
 * Sensor used  : HX711, GY-906, Blood Pressure
 * Database     : Firebase RTDB
 *
 * @author  Ira Adi Nata
 * @version v2024.10.07
 */

#include <Arduino.h>
#include "soc/rtc.h"
#include "HX711.h"
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_MLX90614.h>

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

void init_temperature()
{
  if (!mlx.begin())
  {
    Serial.println("Error connecting to MLX sensor. Check wiring.");
  }

  Serial.print("Emissivity = ");
  Serial.println(mlx.readEmissivity());
}

void get_temperature()
{
  Serial.print("Ambient = ");
  Serial.print(mlx.readAmbientTempC());
  Serial.print("*C\tObject = ");
  Serial.print(mlx.readObjectTempC());
  Serial.println("*C");
  Serial.print("Ambient = ");
  Serial.print(mlx.readAmbientTempF());
  Serial.print("*F\tObject = ");
  Serial.print(mlx.readObjectTempF());
  Serial.println("*F");
  Serial.println();
  data_temperature = (int)mlx.readAmbientTempC();
}

void calib_weight()
{
  rtc_cpu_freq_config_t config;
  rtc_clk_cpu_freq_get_config(&config);
  rtc_clk_cpu_freq_to_config(RTC_CPU_FREQ_80M, &config);
  rtc_clk_cpu_freq_set_config_fast(&config);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  while (1)
  {
    if (scale.is_ready())
    {
      scale.set_scale();
      Serial.println("Tare... remove any weights from the scale.");
      delay(5000);
      scale.tare();
      Serial.println("Tare done...");
      Serial.print("Place a known weight on the scale...");
      delay(5000);
      long reading = scale.get_units(10);
      Serial.print("Result: ");
      Serial.println(reading);
    }
    else
    {
      Serial.println("HX711 not found.");
    }
    delay(1000);
  }
}

void init_weight()
{
  rtc_cpu_freq_config_t config;
  rtc_clk_cpu_freq_get_config(&config);
  rtc_clk_cpu_freq_to_config(RTC_CPU_FREQ_80M, &config);
  rtc_clk_cpu_freq_set_config_fast(&config);

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  Serial.println("HX711 Demo");
  Serial.println("Initializing the scale");

  Serial.println("Before setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale.read()); // print a raw reading from the ADC
  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20)); // print the average of 20 readings from the ADC
  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5)); // print the average of 5 readings from the ADC minus the tare weight (not set yet)
  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1); // print the average of 5 readings from the ADC minus tare weight (not set) divided
                                         // by the SCALE parameter (not set yet)

  scale.set_scale(0); // INSERT YOUR CALIBRATION FACTOR
  // scale.set_scale(-471.497);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare(); // reset the scale to 0

  Serial.println("After setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale.read()); // print a raw reading from the ADC
  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20)); // print the average of 20 readings from the ADC
  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5)); // print the average of 5 readings from the ADC minus the tare weight, set with tare()
  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1); // print the average of 5 readings from the ADC minus tare weight, divided by the SCALE parameter set with set_scale
}

void get_weight()
{
  Serial.print("one reading:\t");
  Serial.print(scale.get_units(), 1);
  Serial.print("\t| average:\t");
  Serial.println(scale.get_units(10), 5);

  // scale.power_down(); // put the ADC in sleep mode
  // delay(5000);
  // scale.power_up();
}

void setup()
{
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
  Serial.begin(115200);
  // calib_weight();
  // init_weight();
  // init_temperature();
}

void loop()
{
  get_blood();
  // get_weight();
  // get_temperature();

  datasend[0] = '!';
  datasend[1] = data_sys;
  datasend[2] = '@';
  datasend[3] = data_dia;
  datasend[4] = '#';
  datasend[5] = data_bpm;
  datasend[6] = '$';
  datasend[7] = data_weight;
  datasend[8] = '%';
  datasend[9] = data_ambient;
  datasend[10] = '^';
  datasend[11] = data_temperature;
  datasend[12] = '&';
  Serial2.write(datasend, sizeof(datasend));
}
