#include <SPI.h>
#include <SD.h>

// gunakan pin D10 untuk pin CS
#define PIN_SD_SS 10

// jumlah kolom sebanyak 6
#define JUMLAH_KOLOM 6

// ukuran buffer untuk menyimpan 1 baris data
#define BUFFER_BARIS 50

File fileSDCard;
String buffer_string;
boolean SDfound;
char *strings_dataSD[JUMLAH_KOLOM];
char *ptr = NULL;

int co2;
float kelembaban;
float pm10;
float pm25;
float suhu;
float voc;


void setup() {
  Serial.begin(9600);
  while (!Serial);
  delay(1000);
  
  if (SDfound == 0) {
    if (!SD.begin(PIN_SD_SS)) {
      Serial.print("SD Card tidak ditemukan!");
      while(1);
    }
  }
  SDfound = 1;
  Serial.print("SD Card ditemukan!");
  fileSDCard = SD.open("UDARA.txt", FILE_READ);

  if (!fileSDCard) {
    Serial.print("File tidak dapat dibaca!");
    while(1);
  }

  while (fileSDCard.available()) {
    Serial.println("\nHasil baca baris dari SD Card:");
	// baca sampai baris terakhir (bertemu ENTER)
    buffer_string = fileSDCard.readStringUntil('\n');
    Serial.println(buffer_string); 
  
	//Ubah String ke array char untuk tiap data 
	char charBuf[BUFFER_BARIS];
	buffer_string.toCharArray(charBuf, BUFFER_BARIS);
             
    //pecah string sesuai delimiter (kita pakai koma)
    byte index = 0;
    ptr = strtok(charBuf, ","); //demiter koma
    while (ptr != NULL){
		strings_dataSD[index] = ptr;
		index++;
		ptr = strtok(NULL, ",");
    }
  
	// konversi array char ke int atau float
	co2 = atoi(strings_dataSD[0]);  //integer
	kelembaban = atof(strings_dataSD[1]); //float
	pm10 = atof(strings_dataSD[2]);
	pm25 = atof(strings_dataSD[3]);
	suhu = atof(strings_dataSD[4]);
	voc = atof(strings_dataSD[5]);
  
	// print hasil konversi
	Serial.print("\nCO2 = ");
	Serial.println(co2);
	Serial.print("Kelembaban = ");
	Serial.println(kelembaban);
	Serial.print("Particulate Matter PM10 = ");
	Serial.println(pm10);
	Serial.print("Particulate Matter PM2.5 = ");
	Serial.println(pm25);
	Serial.print("Suhu = ");
	Serial.println(suhu);
	Serial.print("Volatile Organic Compound (VOC) = ");
	Serial.println(voc); 
    
	delay(1000);
  }

  fileSDCard.close();
}

void loop() {
   // tidak melakukan apa-apa
}
