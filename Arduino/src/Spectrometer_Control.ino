
// This code is a modified from the original sketch from Peter Jansen
// also this code just prints the output to csv output to the terminal.

//sudo chmod a+rw /dev/ttyACM0


//#define SPEC_EOS         NA
#define SPEC_ST          A1
#define SPEC_CLK         A2
#define SPEC_VIDEO       A3


#define SPEC_CHANNELS    256
uint16_t data[SPEC_CHANNELS];

void setup() {


  pinMode(SPEC_ST, OUTPUT);
  pinMode(SPEC_CLK, OUTPUT);

  digitalWrite(SPEC_ST, HIGH);
  digitalWrite(SPEC_CLK, HIGH);

  Serial.begin(9600); 
}

  void readSpectrometer()
  {
  int delay_time = 100;     // delay per half clock (in microseconds).  This ultimately conrols the integration time.
  int idx = 0;
  int read_time = 30;      // Amount of time that the analogRead() procedure takes (in microseconds) (different micros will have different times)
  int intTime = 300;
  int i;
  long int numIntegrationBlocks = 1000;


  // Step 2: Send start pulse to signal start of integration/light collection
  digitalWrite(SPEC_CLK, LOW);
  delayMicroseconds(delay_time);
  digitalWrite(SPEC_CLK, HIGH);
  digitalWrite(SPEC_ST, LOW);
  delayMicroseconds(delay_time);
  digitalWrite(SPEC_CLK, LOW);
  delayMicroseconds(delay_time);
  digitalWrite(SPEC_CLK, HIGH);
  digitalWrite(SPEC_ST, HIGH);
  delayMicroseconds(delay_time);

  // Step 3: Integration time -- sample for a period of time determined by the intTime parameter

  for (int i = 0; i < numIntegrationBlocks; i++) {
    digitalWrite(SPEC_CLK, LOW);
    delayMicroseconds(delay_time);
    digitalWrite(SPEC_CLK, HIGH);
  delayMicroseconds(delay_time);
 
    digitalWrite(SPEC_CLK, LOW);
    delayMicroseconds(delay_time);
    digitalWrite(SPEC_CLK, HIGH);
    delayMicroseconds(delay_time);

    digitalWrite(SPEC_CLK, LOW);
    delayMicroseconds(delay_time);
    digitalWrite(SPEC_CLK, HIGH);
    delayMicroseconds(delay_time);
    digitalWrite(SPEC_CLK, LOW);
    delayMicroseconds(delay_time);
    digitalWrite(SPEC_CLK, HIGH);
    delayMicroseconds(delay_time);
    
  }


  // Step 4: Send start pulse to signal end of integration/light collection
  digitalWrite(SPEC_CLK, LOW);
  delayMicroseconds(delay_time);
  digitalWrite(SPEC_CLK, HIGH);
  digitalWrite(SPEC_ST, LOW);
  delayMicroseconds(delay_time);
  digitalWrite(SPEC_CLK, LOW);
  delayMicroseconds(delay_time);
  digitalWrite(SPEC_CLK, HIGH);
  digitalWrite(SPEC_ST, HIGH);
  delayMicroseconds(delay_time);

  // Step 5: Read Data 2 (this is the actual read, since the spectrometer has now sampled data)
  idx = 0;
  for (int i = 0; i < SPEC_CHANNELS; i++) {

    digitalWrite(SPEC_CLK, LOW);
    delayMicroseconds(delay_time);
   

   
      data[idx] = analogRead(SPEC_VIDEO);
   
    
    idx += 1;
    if (delay_time > read_time) delayMicroseconds(delay_time - read_time);   // Read takes about 135uSec

    digitalWrite(SPEC_CLK, HIGH);
    delayMicroseconds(delay_time);


  }

  }

void print_data()
{
  for (int i = 0; i < SPEC_CHANNELS; i++)
  {
    Serial.print(data[i]);
    Serial.print(',');
  }
  Serial.print("\n");
  
}

void loop()
{

 readSpectrometer();
  print_data();
  delay(10);
}
