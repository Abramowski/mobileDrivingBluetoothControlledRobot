#include <TimerOne.h>
#define trig1 2
#define echo1 3
#define trig2 A4
#define echo2 A3
#define trig3 A2
#define echo3 A1
#define in1 12
#define in2 11
#define in3 10
#define in4 9
#define enA 5
#define enB 6
int dataIn[5] = {0, 0, 125, 125, 125};
int i, in_byte;
int motorL_speed = 125;
int motorR_speed = 125;
float min_dist = 20.0;
void setup()
{
    pinMode(trig1, OUTPUT);
    pinMode(echo1, INPUT);
    pinMode(trig2, OUTPUT);
    pinMode(echo2, INPUT);
    pinMode(trig3, OUTPUT);
    pinMode(echo3, INPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    pinMode(enA, OUTPUT);
    pinMode(enB, OUTPUT);
    analogWrite(enA, motorL_speed);
    analogWrite(enB, motorR_speed);
    Serial.begin(9600);
    Timer1.initialize(10000);
    Timer1.attachInterrupt(readDataFromBT);
}
void loop()
{
    if (dataIn[1] == 0)
        Stop();
    else if (dataIn[1] == 1)
        manualDrive();
    else if (dataIn[1] == 2)
        autoDrive();
}
float measure(int trig, int echo)
{
    unsigned long t;
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    t = pulseIn(echo, HIGH);
    return t * 0, 034 / 2;
}
void readDataFromBT()
{
    for (int j = 0; j < 10; j++)
    {
        if (Serial.available() > 0)
        {
            in_byte = Serial.read();
            if (in_byte == (255))
                i = 0;
            dataIn[i] = in_byte;
            i++;
        }
    }
}
void manualDrive()
{
    motorL_speed = dataIn[4];
    motorR_speed = dataIn[4];
    analogWrite(enA, motorL_speed);
    analogWrite(enB, motorR_speed);
    if (dataIn[3] < 80)
    {
        if (dataIn[2] < 80)
            forwardleft();
        else if (dataIn[2] > 170)
            forwardright();
        else
            forward();
    }
    else if (dataIn[3] > 170)
    {
        if (dataIn[2] < 80)
            backleft();
        else if (dataIn[2] > 170)
            backright();
        else
            back();
    }
    else
    {
        if (dataIn[2] < 80)
            left();
        else if (dataIn[2] > 170)
            right();
        else
            Stop();
    }
}
void autoDrive()
{
    motorL_speed = 90;
    motorR_speed = 90;
    analogWrite(enA, motorL_speed);
    analogWrite(enB, motorR_speed);

    if (measure(trig2, echo2) > min_dist)
        forward();
    else if (measure(trig1, echo1) < measure(trig3, echo3))
    {
        back();
        delay(200);
        right();
        delay(200);
    }
    else
    {
        back();
        delay(200);
        left();
        delay(200);
    }
}
void forward()
{
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
}
void back()
{
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
}
void left()
{
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
}
void right()
{
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
}
void forwardleft() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
}
void forwardright() {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
}
void backright() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
}
void backleft() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
}
void Stop() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
}
