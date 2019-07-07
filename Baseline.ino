void setup(){
    pinMode(13,OUTPUT);
}

void loop(){
    digitalWrite(13,HIGH);
    delay(1000);
    digitalWrite(13,LOW);
    delay(100);
    digitalWrite(13,HIGH);
    delay(100);
    digitalWrite(13,LOW);
    delay(100);
}
/*
Ô­Ê¼³ÌÐò
ÁÁ1s£¬Ãð0.1s,ÁÁ0.1s£¬Ãð0.1s
 */