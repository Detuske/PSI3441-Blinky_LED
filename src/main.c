

#include <zephyr.h>
#include <device.h>
#include <drivers/gpio.h>

// Definições de Portas (Aliases do Device Tree para a KL25Z)
#define PORT_B "GPIO_1"
#define PORT_D "GPIO_3"

// Definições de Pinos
#define LED_RED_PIN    18  // PTB18
#define LED_GREEN_PIN  19  // PTB19
#define LED_YELLOW_PIN   1   // PTD1 (Usaremos como Amarelo)

// Estados do Semáforo
typedef enum {
    STATE_RED,
    STATE_GREEN,
    STATE_YELLOW
} traffic_light_state_t;

void main(void)
{
    // Obtém os dispositivos de porta
    const struct device *dev_b = device_get_binding(PORT_B);
    //const struct device *dev_d = device_get_binding(PORT_D);

    //if (dev_b == NULL || dev_d == NULL) {
    //    return; // Erro ao carregar drivers
    //}

    // Configura os pinos como saída
    gpio_pin_configure(dev_b, LED_RED_PIN, GPIO_OUTPUT_ACTIVE);
    gpio_pin_configure(dev_b, LED_GREEN_PIN, GPIO_OUTPUT_ACTIVE);
    gpio_pin_configure(dev_b, LED_YELLOW_PIN, GPIO_OUTPUT_ACTIVE);

    traffic_light_state_t current_state = STATE_RED;

    while (1) {
        switch (current_state) {
            case STATE_RED:
                // Lógica: Vermelho ON, outros OFF
                gpio_pin_set(dev_b, LED_RED_PIN, 1);
                gpio_pin_set(dev_b, LED_GREEN_PIN, 0);
                gpio_pin_set(dev_b, LED_YELLOW_PIN, 0);
                
                k_msleep(1000); // Fica no vermelho por 5s
                current_state = STATE_GREEN;
                break;

            case STATE_GREEN:
                // Lógica: Verde ON, outros OFF
                gpio_pin_set(dev_b, LED_RED_PIN, 0);
                gpio_pin_set(dev_b, LED_GREEN_PIN, 1);
                gpio_pin_set(dev_b, LED_YELLOW_PIN, 0);
                
                k_msleep(1000); // Fica no verde por 5s
                current_state = STATE_YELLOW;
                break;

            case STATE_YELLOW:
                // Lógica: "Amarelo" (Azul) ON, outros OFF
                gpio_pin_set(dev_b, LED_RED_PIN, 0);
                gpio_pin_set(dev_b, LED_GREEN_PIN, 0);
                gpio_pin_set(dev_b, LED_YELLOW_PIN, 1);
                
                k_msleep(400); // Amarelo dura menos: 2s
                current_state = STATE_RED;
                break;
        }
    }
}