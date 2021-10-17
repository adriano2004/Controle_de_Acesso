#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9          
#define SS_PIN          10        

MFRC522 mfrc522(SS_PIN, RST_PIN); 

int led1 =2;
int led2 =4;
int led3 =3;

void setup() {
	Serial.begin(9600);		
	while (!Serial);		
	SPI.begin();		
	mfrc522.PCD_Init();		
	mfrc522.PCD_DumpVersionToSerial();	
	Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

}

void loop() {
  digitalWrite(led3,HIGH);
	if ( ! mfrc522.PICC_IsNewCardPresent()) {
		return;
	}

	if ( ! mfrc522.PICC_ReadCardSerial()) {
		return;
	}
 Serial.print("UID da tag :");
  String conteudo= "";
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Mensagem : ");
  conteudo.toUpperCase();

  if ( conteudo.substring(1) == "4A 61 36 BE"){
    digitalWrite(led1,HIGH);
    digitalWrite(led2,LOW);
    digitalWrite(led3,LOW);
    Serial.println("Acesso liberado");
    delay(2000);
    digitalWrite(led3,HIGH);
    digitalWrite(led1,LOW);
    
  }
  else if(conteudo.substring(1) != "4A 61 36 BE"){
    digitalWrite(led2,HIGH);
    digitalWrite(led1,LOW);
    digitalWrite(led3,LOW);
    Serial.println("Acesso negado");
    delay(2000);
    digitalWrite(led3,HIGH);
    digitalWrite(led2,LOW);
    
    }
  else{
    digitalWrite(led3,HIGH);
   }

  Serial.println("Esperando Cartão");
}
