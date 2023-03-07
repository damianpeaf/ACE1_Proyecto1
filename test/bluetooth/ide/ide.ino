String text; 
bool login = false;
void setup() {
  // put your setup code here, to run once:
  pinMode(13,OUTPUT);
  Serial1.begin(9600);
  Serial.begin(9600);
  Serial.println("Conectado");
}
void sendToken() {
  delay(4000);
  Serial1.write("123ABC");
}
void loop() {
  // put your main code here, to run repeatedly:
  while(Serial1.available()){
    delay(10);
    char c = Serial1.read();
    text += c;
  }
  if (text.length() > 0){
    if(text == "on"){
      digitalWrite(13,HIGH);
    }
    if(text == "off"){
      digitalWrite(13,LOW);
    }
    if(text == "connected"){
      Serial.println(text);
      sendToken();
    }
    text="";
  }
}
