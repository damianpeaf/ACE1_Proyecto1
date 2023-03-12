String text; 
bool login = false;
void setup() {
  // put your setup code here, to run once:
  pinMode(13,OUTPUT);
  Serial1.begin(9600);
  Serial.begin(9600);
  Serial.println("Conectado");
}

void startAdminMenu(){
  delay(3000);
  Serial1.write("admin");
  delay(3000);
  Serial1.write("name");
  String name = "";
  while(name != "Alvaro") {
    while(Serial1.available()){
      delay(10);
      char c = Serial1.read();
      name += c;
    }
  }
  Serial.println(name);
  delay(3000);
  Serial1.write("logout");
}
void startConsumerMenu() {
  Serial1.print("consumer");
  Serial.println("consumer");
  delay(4000);
  Serial.println("Show errors");
  Serial1.write("Error: Entrada no valida");
  delay(3000);
  startAdminMenu();
}
void sendToken() {
  Serial1.write("token");
  delay(5000);
  Serial1.write("123ABC");
  delay(4000);
  startConsumerMenu();
}
void loop() {
  // put your main code here, to run repeatedly:
  while(Serial1.available()){
    delay(10);
    char c = Serial1.read();
    text += c;
  }
  if (text.length() > 0){
    if(text == "disconnected"){
      Serial.println("Desconectado");
    }
    if(text == "connected"){
      Serial.println(text);
      sendToken();
    }
    text="";
  }
}
