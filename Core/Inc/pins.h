/*
 * pins.h
 *
 */

#ifndef INC_PINS_H_
#define INC_PINS_H_

#define RangePort GPIOB
#define TrigPin GPIO_PIN_1
#define EchoPin GPIO_PIN_2

// defining pins for data
#define Data_Port GPIOD
#define D4_PIN GPIO_PIN_8
#define D5_PIN GPIO_PIN_9
#define D6_PIN GPIO_PIN_10
#define D7_PIN GPIO_PIN_11

//defining rs and e pins
#define RS_Pin GPIO_PIN_0
#define Write_Port GPIOE
#define Write_Pin GPIO_PIN_1

#define LED_Port GPIOD
#define Blue_Pin GPIO_PIN_15




#endif /* INC_PINS_H_ */