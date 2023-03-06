String text; 

void setup() {
  // put your setup code here, to run once:
  pinMode(13,OUTPUT);
  Serial1.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial1.available()){
    delay(10);
    char c = Serial1.read();
    text += c;
  }
  if (text.length() > 0){
    Serial1.println(text);
    if(text == "on"){
      digitalWrite(13,HIGH);
    }
    if(text == "off"){
      digitalWrite(13,LOW);
    }
    text="";
  }
}
