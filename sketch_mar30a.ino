#include <Keypad.h>

#define ROW 4
#define COLUMNS 4
#define LENGHT 5

static const char keymap[ROW][COLUMNS] = 
                                         {{'1', '2', 'A', '3'}, 
                                          {'4', '5', 'B', '6'}, 
                                          {'7', '8', 'C', '9'}, 
                                          {'*', '0', 'D', '#'}};
static const byte rowPins[ROW] = {13, 12, 11, 10};
static const byte columnsPins[COLUMNS] = {7, 6, 5, 4};
static Keypad keypad = Keypad{makeKeymap(keymap), rowPins, columnsPins, ROW, COLUMNS};

static const char password[] = {'A', '#', '1', '5', '9'};
static char input[LENGHT] = {0};
static byte index = 0;
static boolean bUserInput = true;
static boolean bIsGoodPassword = false;


static byte pinLedOk = 2;
static byte pinLedNo = 3;
static byte pinBuzzer = 9;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pinLedOk, OUTPUT);
  pinMode(pinLedNo, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  char key = keypad.getKey();

  if(key != NO_KEY && bUserInput)
  {
     Serial.println(key);
     input[index] = key;
     index++;
                                    
     if(index == LENGHT)
     {
        Serial.println("CODE VERIFICATION");
        bUserInput = false;
         
        for(int i = 0; i < LENGHT; i++)
        {
           if(input[i] == password[i])
           {
              bIsGoodPassword = true;
           }
           else 
           {
              Serial.println("BAD PASSWORD");
              bIsGoodPassword = false;
              bUserInput = true;
              index = 0;

              tone(pinBuzzer, 200);
              digitalWrite(pinLedNo, HIGH);
              delay(3000);
              digitalWrite(pinLedNo, LOW);
              noTone(pinBuzzer);
              break;
           }
        }
     }
  }
  else if(!bUserInput && bIsGoodPassword)
  {
    Serial.println("YOU CAN ENTER !");
    tone(pinBuzzer, 450);
    digitalWrite(pinLedOk, HIGH);
    delay(5000);
    digitalWrite(pinLedOk, LOW);
    noTone(pinBuzzer);


    bUserInput = true;
    bIsGoodPassword = false;
    index = 0;f
  }
}
