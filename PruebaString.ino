String Cadena;

String Cod;
String Ced;
String Tip;
byte Codigo[16];
byte Cedula[16];
byte Tipo[16];
byte posicion=0;

void setup() {
  Serial.begin(9600);
  Serial.println("Digite la cadena");
}

void loop() {

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
      
  delay(1000);

}
