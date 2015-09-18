#include <PN532.h>

// Shield NFC:
#define SCK  13
#define MOSI 11
#define SS   10
#define MISO 12
#define PN532_CS 10

PN532 nfc(SCK, MISO, MOSI, SS);

uint8_t written=0;
uint8_t written2=0;
uint8_t written3=0;


String Cadena;

String Cod;
String Ced;
String Tip;
byte Codigo[16];
byte Cedula[16];
byte Tipo[16];


void setup()
{
   Serial.begin(9600);
   Serial.println("¡¡¡Bienvenido!!!");  
   nfc.begin();
   nfc.SAMConfig();
}


void loop()
{

      Cadena = Serial.readString();

      Serial.println(Cadena);

      Cod=Cadena.substring(0,12);
      Ced=Cadena.substring(12,23);
      Tip=Cadena.substring(25);
        
      Serial.println("\n");
      Cod.getBytes(Codigo,Cod.length());

      Serial.println("Codigo");
     
      for(int i=0;i<=11;i++){
        Serial.print(Codigo[i],HEX);
      }

      Serial.println("\n");
      Ced.getBytes(Cedula,Ced.length());

      Serial.println("Cedula");
      
      for(int i=0;i<=10;i++){
        Serial.print(Cedula[i],HEX);
      }
      Serial.println("\n");
      Tip.getBytes(Tipo,Tip.length());
      
      Serial.println("Tipo");
      for(int i=0;i<=1;i++){
        Serial.print(Tipo[i],HEX);
      }

  
  uint32_t id;
  id = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A);
  
  if (id !=0){
  Serial.println();
  Serial.print("Tarjeta #"); Serial.print(id);
  Serial.println();  
  uint8_t keys[]={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
  //uint8_t writeBuffer[11];
  if(nfc.authenticateBlock(1,id,0x08,KEY_A,keys))
  {
      if(written == 0)
      {
        written = nfc.writeMemoryBlock(1,0x08,Codigo);
        if(written)
        Serial.println("Escritura Realizada con exito");
      }
      
      uint8_t block8[16];
      if(nfc.readMemoryBlock(1,0x08,block8))
      {
      Serial.println(" ");
      Serial.println("Leer Bloque 0x08:");   
      //if read operation is successful
      for(uint8_t i=0;i<16;i++)
      {
        Serial.print(block8[i],HEX);
        Serial.print(" ");
      }
      Serial.println();
  }

  if(nfc.authenticateBlock(1,id,0x09,KEY_A,keys))
  {
      if(written2 == 0)
      {
        written2= nfc.writeMemoryBlock(1,0x09,Cedula);
        if(written2)
        Serial.println("Escritura Realizada con exito");
      }
      
      uint8_t block9[16];
      if(nfc.readMemoryBlock(1,0x09,block9))
      {
      Serial.println(" ");
      Serial.println("Leer Bloque 0x09:");   
      //if read operation is successful
      for(uint8_t i=0;i<16;i++)
      {
        Serial.print(block9[i],HEX);
        Serial.print(" ");
      }
      Serial.println();
  }
  }

  if(nfc.authenticateBlock(1,id,0xA,KEY_A,keys))
  {
      if(written3 == 0)
      {
        written3= nfc.writeMemoryBlock(1,0xA,Tipo);
        if(written3)
        Serial.println("Escritura Realizada con exito");
      }
      
      uint8_t block10[16];
      if(nfc.readMemoryBlock(1,0xA,block10))
      {
      Serial.println(" ");
      Serial.println("Leer Bloque 0xA:");   
      //if read operation is successful
      for(uint8_t i=0;i<16;i++)
      {
        Serial.print(block10[i],HEX);
        Serial.print(" ");
      }
      Serial.println();
  }
  }

  }
  delay(1000);
 }
}
