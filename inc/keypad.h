#include "stm8s.h"
// pomoc� maker konfigurujeme zapojen� kl�vesnice k MCU
#define SLP1_GPIO GPIOF
#define SLP1_PIN	GPIO_PIN_7

#define SLP2_GPIO GPIOF
#define SLP2_PIN	GPIO_PIN_6

#define SLP3_GPIO GPIOF
#define SLP3_PIN	GPIO_PIN_5

#define SLP4_GPIO GPIOF
#define SLP4_PIN	GPIO_PIN_4

#define RDK1_GPIO GPIOE
#define RDK1_PIN 	GPIO_PIN_0

#define RDK2_GPIO GPIOF
#define RDK2_PIN 	GPIO_PIN_3

#define RDK3_GPIO GPIOF
#define RDK3_PIN 	GPIO_PIN_0

#define RDK4_GPIO GPIOE
#define RDK4_PIN 	GPIO_PIN_3


// n�sleduj�c� makra u� nen� pot�eba m�nit (leda p�i portov�n� na jinou platformu, AVR, ARM atp.)
#define STAV_RDK1 (GPIO_ReadInputPin(RDK1_GPIO, RDK1_PIN)==RESET)
#define STAV_RDK2 (GPIO_ReadInputPin(RDK2_GPIO, RDK2_PIN)==RESET)
#define STAV_RDK3 (GPIO_ReadInputPin(RDK3_GPIO, RDK3_PIN)==RESET)
#define STAV_RDK4 (GPIO_ReadInputPin(RDK4_GPIO, RDK4_PIN)==RESET)

#define AKT_SLP1 GPIO_WriteLow(SLP1_GPIO,SLP1_PIN)
#define AKT_SLP2 GPIO_WriteLow(SLP2_GPIO,SLP2_PIN)
#define AKT_SLP3 GPIO_WriteLow(SLP3_GPIO,SLP3_PIN)
#define AKT_SLP4 GPIO_WriteLow(SLP4_GPIO,SLP4_PIN)

#define DEAKT_SLP1 GPIO_WriteHigh(SLP1_GPIO,SLP1_PIN)
#define DEAKT_SLP2 GPIO_WriteHigh(SLP2_GPIO,SLP2_PIN)
#define DEAKT_SLP3 GPIO_WriteHigh(SLP3_GPIO,SLP3_PIN)
#define DEAKT_SLP4 GPIO_WriteHigh(SLP4_GPIO,SLP4_PIN)

// funkce "knihovny" 
void keypad_init(void); // inicializace vybran�ch GPIO
uint8_t keypad_scan(void); // vrac� stav kl�vesnice