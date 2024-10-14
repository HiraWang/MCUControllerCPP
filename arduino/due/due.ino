// Component 1 : monitor
// Output : no output pin
#undef HID_ENABLED

volatile int bufn, obufn;
uint16_t buf[4][256];   // 4 buffers of 256 readings

// Component 2 : pwm signal generator
// Output : digital pin 6
const int PWM_OUTPUT_PIN = 6;

#include <DuePWM.h>
#define PWM_FREQ1 1000
#define PWM_FREQ2 10000
#define PWM_DUTY_CYCLE 0

int period = 0; // us
int freq = 0;
int duty_cycle = PWM_DUTY_CYCLE;
int pre_period = 0;
int pre_duty_cycle = 0;
String str_period = "0";
String str_duty_cycle = "0";

DuePWM pwm(PWM_FREQ1, PWM_FREQ2);

// Component 3 : pump
// Output : communication 18(TX), 19(RX)
#include <ModbusMaster.h>
#define MAX485_DE      3
#define MAX485_RE_NEG  2

ModbusMaster node;
bool state = false;
uint8_t result = {  };
uint16_t pump_data[10];

void preTransmission()
{
  digitalWrite(MAX485_RE_NEG, 1);
  digitalWrite(MAX485_DE, 1);
}

void postTransmission()
{
  digitalWrite(MAX485_RE_NEG, 0);
  digitalWrite(MAX485_DE, 0);
}

int pump_command_1 = 0;
int pump_command_2 = 0;
int pump_command_3 = 0;
unsigned short g_pump_command_1 = 0;
unsigned short g_pump_command_2 = 0;
unsigned short g_pump_command_3 = 0;
String str_pump_command_1 = "0";
String str_pump_command_2 = "0";
String str_pump_command_3 = "0";

// Component 4 : valve
// Output : digital pin 2, 3, 4
const int VALVE_OUTPUT_PIN_1 = 2;
const int VALVE_OUTPUT_PIN_2 = 3;
const int VALVE_OUTPUT_PIN_3 = 4;
int valve_1 = 0;
int valve_2 = 0;
int valve_3 = 0;
int g_valve_1 = 0;
int g_valve_2 = 0;
int g_valve_3 = 0;
String str_valve_1 = "0";
String str_valve_2 = "0";
String str_valve_3 = "0";

void ADC_Handler() { // move DMA pointers to next buffer
  int f = ADC->ADC_ISR;
  if (f & (1 << 27)) {
   bufn = (bufn + 1) & 3;
   ADC->ADC_RNPR = (uint32_t)buf[bufn];
   ADC->ADC_RNCR = 256;
  } 
}

void setup() {
  // Component 1 : monitor
  pinMode(VALVE_OUTPUT_PIN_1, OUTPUT);
  pinMode(VALVE_OUTPUT_PIN_2, OUTPUT);
  pinMode(VALVE_OUTPUT_PIN_3, OUTPUT);
  analogWriteResolution(12);

  // while(!SerialUSB);
  pmc_enable_periph_clk(ID_ADC);
  adc_init(ADC, SystemCoreClock, ADC_FREQ_MAX, ADC_STARTUP_FAST);
  ADC->ADC_MR |= 0x80; // free running

  ADC->ADC_CHER = 0x80; 

  NVIC_EnableIRQ(ADC_IRQn);
  ADC->ADC_IDR = ~(1<<27);
  ADC->ADC_IER = 1<<27;
  ADC->ADC_RPR = (uint32_t)buf[0]; // DMA buffer
  ADC->ADC_RCR = 256;
  ADC->ADC_RNPR = (uint32_t)buf[1]; // next DMA buffer
  ADC->ADC_RNCR = 256;
  // bufn = obufn = 1;
  bufn = 1;
  obufn = 0;
  ADC->ADC_PTCR = 1;
  ADC->ADC_CR = 2;

  // Component 2 : pwm signal generator
  SerialUSB.begin(9600);
  pinMode(PWM_OUTPUT_PIN, OUTPUT);
  pwm.setFreq1(PWM_FREQ1);
  pwm.pinFreq1(PWM_OUTPUT_PIN); // Pin 6 freq set to "pwm_freq1" on clock A
  pwm.pinDuty(PWM_OUTPUT_PIN, 128); // 50% duty cycle on Pin 6

  // Component 3 : pump
  Serial1.begin(9600);
  node.begin(1, Serial1);
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);
}

void loop() {
  if (SerialUSB.available()) {
    str_period = SerialUSB.readStringUntil('p');
    str_duty_cycle = SerialUSB.readStringUntil('d');
    str_pump_command_1 = SerialUSB.readStringUntil('ra');
    str_pump_command_2 = SerialUSB.readStringUntil('rb');
    str_pump_command_3 = SerialUSB.readStringUntil('rc');
    str_valve_1 = SerialUSB.readStringUntil('va');
    str_valve_2 = SerialUSB.readStringUntil('vb');
    str_valve_3 = SerialUSB.readStringUntil('vc');
    period = str_period.toInt();
    freq = 1000000 / period;
    duty_cycle = str_duty_cycle.toInt();
    pump_command_1 = str_pump_command_1.toInt();
    pump_command_2 = str_pump_command_2.toInt();
    pump_command_3 = str_pump_command_3.toInt();
    valve_1 = str_valve_1.toInt();
    valve_2 = str_valve_2.toInt();
    valve_3 = str_valve_3.toInt();

    if (pump_command_1 == g_pump_command_1 && 
        pump_command_2 == g_pump_command_2 && 
        pump_command_3 == g_pump_command_3) {
      state = false;
    } else {
      state = true;
      g_pump_command_1 = pump_command_1;
      g_pump_command_2 = pump_command_2;
      g_pump_command_3 = pump_command_3;
    }

    if (valve_1 == 1 || valve_1 == 2) {
      g_valve_1 = valve_1;
    }
    if (valve_2 == 1 || valve_2 == 2) {
      g_valve_2 = valve_2;
    }
    if (valve_3 == 1 || valve_3 == 2) {
      g_valve_3 = valve_3;
    }

    // Component 2 : pwm signal generator
    if (period != 0 && duty_cycle != 0) {
      pwm.setFreq1(freq);
      pwm.pinFreq1(PWM_OUTPUT_PIN);
      pre_period = period;
      pwm.pinDuty(PWM_OUTPUT_PIN, duty_cycle);
      pre_duty_cycle = duty_cycle;
      SerialUSB.println("PWM set");
    } else if (period == -1) {
      pwm.stop(PWM_OUTPUT_PIN);
    }

    // Component 3 : pump
    pump_data[1] = g_pump_command_1; // Speed
    // pump_data[2] = (g_pump_command_2 >> 4) & 0x0000FFFF; // Flow Rate HB
    // pump_data[3] = g_pump_command_2 & 0x0000FFFF; // Flow Rate LB
    if (g_pump_command_2 != 0) {
      pump_data[4] = 0x0010 ^ g_pump_command_3; // Pump State

    } else {
      pump_data[4] = g_pump_command_3; // Pump State
    }
    pump_data[5] = 0x0001; // Pump Address
    pump_data[6] = 0x0004; // Baud Rate
    pump_data[7] = 0x0001; // Parity 
    pump_data[8] = 0x0001; // Stop Bit
    pump_data[9] = 0x0001; // Keypad Lock
  }

  if (state) {
    SerialUSB.read();
    SerialUSB.end();
    Serial1.begin(9600);
    node.preTransmission(preTransmission);
    node.postTransmission(postTransmission);
    for (int i = 0; i < 3; i++) {
      result = node.writeSingleRegister(0x0001, pump_data[1]);
      result = node.writeSingleRegister(0x0004, pump_data[4]);
      result = node.writeSingleRegister(0x0005, pump_data[5]);
      result = node.writeSingleRegister(0x0006, pump_data[6]);
      result = node.writeSingleRegister(0x0007, pump_data[7]);
      result = node.writeSingleRegister(0x0008, pump_data[8]);
      result = node.writeSingleRegister(0x0009, pump_data[9]);
    }
    state = false;
    Serial1.read();
    Serial1.end();
    SerialUSB.begin(9600);
  } else {
    while ((obufn + 1) % 4 == bufn); 
    SerialUSB.write((uint8_t *)buf[obufn], 512);
    obufn = (obufn + 1) & 3;
  }

  if (g_valve_1 == 1)
    digitalWrite(VALVE_OUTPUT_PIN_1, HIGH);
  else
    digitalWrite(VALVE_OUTPUT_PIN_1, LOW);

  if (g_valve_2 == 1)
    digitalWrite(VALVE_OUTPUT_PIN_2, HIGH);
  else
    digitalWrite(VALVE_OUTPUT_PIN_2, LOW);

  if (g_valve_3 == 1)
    digitalWrite(VALVE_OUTPUT_PIN_3, HIGH);
  else
    digitalWrite(VALVE_OUTPUT_PIN_3, LOW);
}