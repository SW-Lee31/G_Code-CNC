#define EN 8      /* Enable pin for all stepper outputs */

#define X_DIR 5   /* Direction pin for X axis */
#define X_STEP 2  /* Step pin for X axis */

#define Y_DIR 6   /* Direction pin for Y axis */
#define Y_STEP 3  /* Step pin for Y axis */

#define A_DIR 13  /* Direction pin for Aux driver. Requires D13 and A-DIR pins to be shorted */
#define A_STEP 12 /* Direction pin for Aux driver. Requires D12 and A-STEP pins to be shorted */

#define X_ENDSTOP 9   /* X axis endstop input pin */
#define Y_ENDSTOP 10  /* Y axis endstop input pin */
#define Z_ENDSTOP 11  /* Z axis endstop input pin */
#define ABORT A0  /* Abort input pin */
#define HOLD A1   /* Hold input pin */
#define RESUME A2 /* Resume input pin */

boolean Direction = LOW; /* Rotational direction of stepper motors */
 
void setup() {
/* Initialize serial */
  Serial.begin(115200);
 
  /* Configure the steper drive pins as outputs */
  pinMode(EN, OUTPUT);
  pinMode(X_DIR, OUTPUT);
  pinMode(X_STEP, OUTPUT);
  pinMode(Y_DIR, OUTPUT);
  pinMode(Y_STEP, OUTPUT);
 
  /* Configure the control pins as inputs with pullups */
  pinMode(X_ENDSTOP, INPUT_PULLUP);
  pinMode(Y_ENDSTOP, INPUT_PULLUP);

  pinMode(ABORT, INPUT_PULLUP);
  pinMode(HOLD, INPUT_PULLUP);
  pinMode(RESUME, INPUT_PULLUP);

  /* Enable the X, Y, Z & Aux stepper outputs */
  digitalWrite(EN, LOW); //Low to enable

}
void loop() 
{

    digitalWrite(X_DIR,LOW); 
    digitalWrite(X_STEP,LOW); 
    delayMicroseconds(500); 
    digitalWrite(X_STEP,HIGH); 
    delayMicroseconds(500);
}
