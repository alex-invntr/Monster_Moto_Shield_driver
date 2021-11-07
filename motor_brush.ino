// Monster Moto Shield Example 
// code by: Alex Maximov

#define MOTOR_CNT 2

#define MOTOR_1 0
#define MOTOR_2 1

enum action{
    FLY,
    CW,
    CCW,
    BRK
}; 
 
uint8_t INA_pin[MOTOR_CNT] = {7, 4};  // INA: Clockwise input
uint8_t INB_pin[MOTOR_CNT] = {8, 9};  // INB: Counter-clockwise input
uint8_t PWM_pin[MOTOR_CNT] = {5, 6};  // PWM: pwm input

uint8_t  CS_pin[MOTOR_CNT] = {2, 3};  // CS: Current sense analog input
uint8_t  EN_pin[MOTOR_CNT] = {0, 1};  // EN: Status of switches output or analog pin

uint8_t LED_pin = 13;



void setup(){

    //Serial.begin(9600);

    pinMode     (LED_pin, OUTPUT);
    digitalWrite(LED_pin, LOW);

    for (uint8_t i = 0; i < MOTOR_CNT; i++){ // Initialize digital pins as outputs
          
        pinMode(INA_pin[i], OUTPUT);
        pinMode(INB_pin[i], OUTPUT);
        pinMode(PWM_pin[i], OUTPUT);

        motor_FLY(i);

        pinMode( CS_pin[i], OUTPUT);
        pinMode( EN_pin[i], OUTPUT);

        digitalWrite(EN_pin[i], HIGH);

    }
}



void loop(){
    
    
    delay (500);
    motor_DRIVE( MOTOR_1,  CW, 20);
    
        digitalWrite(LED_pin, !digitalRead(LED_pin));

    
    delay (500);
    motor_DRIVE( MOTOR_1, FLY, 20);
    
        digitalWrite(LED_pin, !digitalRead(LED_pin));

    delay (500);
    motor_DRIVE( MOTOR_1, CCW, 20);
    
        digitalWrite(LED_pin, !digitalRead(LED_pin));
    
    delay (500);
    motor_DRIVE( MOTOR_1, BRK, 20);
    
        digitalWrite(LED_pin, !digitalRead(LED_pin));

}



void motor_DRIVE(uint8_t motor, uint8_t direct, uint8_t pwm){
    
    if( motor > (MOTOR_CNT - 1) ){ return; };

    switch( direct ){
        
        case FLY: motor_FLY( motor );      break;
        case  CW: motor_CW ( motor, pwm ); break;
        case CCW: motor_CCW( motor, pwm ); break;
        case BRK: motor_BRK( motor );      break;

        default:  motor_FLY( motor );      break;
    }
}



void motor_FLY(uint8_t motor){
    
    if( motor > (MOTOR_CNT - 1) ){ return; };

    digitalWrite(INA_pin[motor], HIGH);
    digitalWrite(INB_pin[motor], HIGH);
     analogWrite(PWM_pin[motor], 0   );
}

void motor_CW(uint8_t motor, uint8_t pwm){
    
    if( motor > (MOTOR_CNT - 1) ){ return; };
    
    digitalWrite(INA_pin[motor], HIGH);         
    digitalWrite(INB_pin[motor], LOW ); 
     analogWrite(PWM_pin[motor], pwm );
}

void motor_CCW(uint8_t motor, uint8_t pwm){
    
    if( motor > (MOTOR_CNT - 1) ){ return; };

    digitalWrite(INA_pin[motor], LOW );
    digitalWrite(INB_pin[motor], HIGH);  
     analogWrite(PWM_pin[motor], pwm );
}

void motor_BRK(uint8_t motor){
    
    if( motor > (MOTOR_CNT - 1) ){ return; };

    digitalWrite(INA_pin[motor], LOW);
    digitalWrite(INB_pin[motor], LOW);
     analogWrite(PWM_pin[motor], 0  );
}
