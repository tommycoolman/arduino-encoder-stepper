#define ROT_CLOCK A5    // Encoder Clock Pin
#define ROT_DATA  A4    // Encoder Data Pin
#define PUL_PIN 9       // Stepper Pulse Pin (sometimes called a step pin)
#define DIR_PIN 10      // Stepper Direction Pin

// Encoder Variables
int counter = 0; 
int current_clock;
int last_clock; 
String direction = "";

// Stepper Variables
int stepCount = 200;
int pulse = LOW;
unsigned int stepTimeCurrent;
unsigned int stepTimeLast;
int stepDelay = 5000;

void setup() { 
    pinMode (ROT_CLOCK,INPUT);
    pinMode (ROT_DATA,INPUT);
    pinMode(PUL_PIN, OUTPUT);
    pinMode(DIR_PIN, OUTPUT);
 
    digitalWrite(DIR_PIN, HIGH);

    Serial.begin (9600);
    last_clock = digitalRead(ROT_CLOCK);
    stepTimeLast = micros();
} 

void loop() { 

    // Check if encoder position changed
    current_clock = digitalRead(ROT_CLOCK);
    if (current_clock != last_clock){ 
        
        if (digitalRead(ROT_DATA) != current_clock) { 
            counter--;
            direction = "CCW";
        }
        else {
            counter++;
            direction = " CW";
        }
        Serial.print(direction);
        Serial.print(" POS: ");
        Serial.println(counter);
    } 
    last_clock = current_clock;


    // Pulse stepper pin with delay
    stepTimeCurrent = micros();
    if(stepTimeCurrent - stepTimeLast > stepDelay){
        pulse = pulse == LOW ? HIGH : LOW;
        digitalWrite(PUL_PIN, pulse);
        stepTimeLast = stepTimeCurrent;
    }
}
