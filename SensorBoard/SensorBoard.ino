/* Code used for the Adafruit Feather 32u4, Sensor Board.
   Reads data from the Plantower sensor, processes the data,
   and transmits the data to the LoRa board using Serial/UART
   communcation
*/

byte DataBuf1[32];

unsigned long Small1;
unsigned long NotSmall1;
unsigned long SumSmall1;
unsigned long AvgSmall1;
unsigned long PM25;
unsigned long SumNotSmall1;
unsigned long AvgNotSmall1;

int sum1;
int chksum1;
// count the number of valid data strings received
int PMcounter1;
int sampleNum; // how many samples to be averaged
int kount1;//count the number of data read iterations - to be compared to sampleNum

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //for printing to computer
  Serial1.begin(9600); //for reading from sensor and sending over UART
  Serial.println("setup");
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.begin(9600);
  while (Serial1.available() == 0) {} // wait for input
  Serial1.readBytes(DataBuf1, 32);
  Serial.println("loop");
  
  //Process the data
  if (DataBuf1[0] == 0x32 && DataBuf1[1] == 0x3d) // check that the two start bytes are valid
  {
    Serial.println("enter if");
    Small1 = (DataBuf1[6] * 256 + DataBuf1[7]); // get count for smaller size range
    
    //Index 6 and 7 of DataBuf1 store the PM2.5 data
    Serial.print("Data Buf 6 = ");
    Serial.println(DataBuf1[6]);
    Serial.print("Data Buf 7 = ");
    Serial.println(DataBuf1[7]);
    
    // sum the counts for averaging
    SumSmall1 = SumSmall1 + Small1;
    Serial.println(SumSmall1);
    PMcounter1 = PMcounter1 + 1;
    chksum1 = 0;
    sum1 = 0;
  }
  
  AvgSmall1 = SumSmall1 / PMcounter1;
  PM25 = AvgSmall1;

  //Print to serial monitor
  Serial.print("PM2.5 Value = "); 
  Serial.println(PM25); 

  //Send over UART to LoRa Board
  Serial1.print(PM25);
  Serial1.print('!');

  //Print to serial moniotr
  Serial.println("sent");

  PMcounter1 = 0;
  SumSmall1 = 0;
  AvgSmall1 = 0;

}


