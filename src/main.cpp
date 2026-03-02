#include <Arduino.h>

int boost = 0; // bost in kpi
int rpm =0;    // rpm
float rpm_scale = 2.0;

uint8_t solenoid = 0;

// load columns: 0, 25, 50, 75, 100 (%)

int rpm_0000[] = { 100, 117, 168, 255, 255 };
int rpm_1000[] = { 100, 135, 179, 220, 255 };
int rpm_2000[] = { 100, 139, 178, 217, 255 };
int rpm_3000[] = { 100, 139, 178, 217, 255 };
int rpm_4000[] = { 100, 139, 178, 217, 255 };
int rpm_5000[] = { 100, 139, 178, 217, 255 };
int rpm_6000[] = { 100, 139, 178, 217, 255 };
int rpm_7000[] = { 100, 139, 178, 217, 255 };
int rpm_8000[] = { 100, 135, 179, 220, 255 };
int rpm_9000[] = { 100, 117, 168, 255, 255 };

int* table[] = {
  rpm_0000,
  rpm_1000,
  rpm_2000,
  rpm_3000,
  rpm_4000,
  rpm_5000,
  rpm_6000,
  rpm_7000,
  rpm_8000,
  rpm_9000
};


// interpolate between two values 
int interpolate(int rpm, int load){
  // clamp inputs
  if (rpm < 0) rpm = 0;
  if (rpm > 9000) rpm = 9000;
  if (load < 0) load = 0;
  if (load > 100) load = 100;

  int base = (rpm/1000)*1000;
  int top  = base + 1000;
  if (top > 9000) top = 9000; // verhindert table[10]

  int *from_tmp = table[base/1000];
  int *to_tmp   = table[top/1000];

  int load1 = load/25;      // 0..4
  int load2 = load1;
  if (load1 >= 4) {         // load==100
    load1 = 3;
    load2 = 4;
  } else {
    load2 = load1 + 1;
  }

  long from = map(load, load1*25, load2*25, from_tmp[load1], from_tmp[load2]);
  long to   = map(load, load1*25, load2*25, to_tmp[load1],   to_tmp[load2]);

  if (base == top) return (int)from; // safety

  long out = map(rpm, base, top, from, to);

  // clamp to PWM range
  if (out < 0) out = 0;
  if (out > 255) out = 255;
  return (int)out;
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

}

void loop() {
  boost = round((analogRead(1)/4095.0)*100);
  rpm   = round((analogRead(2)*rpm_scale));
//  Serial.println(boost);
//  Serial.println(rpm);
  solenoid = interpolate(rpm,boost);
  Serial.print("solenoid: ");
  Serial.print(solenoid);
  Serial.print(" rpm: ");
  Serial.print(rpm);
  Serial.print(" boost: ");
  Serial.println(boost);
  analogWrite(37, solenoid);
  delay(10); // this speeds up the simulation
}
