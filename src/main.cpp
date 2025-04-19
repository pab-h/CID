#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/* Definições de pinos */
#define LED1 2 // LED 1
#define LED2 4 // LED 2 G2
#define LED3 23 // LED 2

/* Handles das tasks */
TaskHandle_t xTask1Handle = NULL;
TaskHandle_t xTask2Handle = NULL;
TaskHandle_t xTask3Handle = NULL;

/* Protótipos das tasks */
void vTask1(void *pvParameters);
void vTask2(void *pvParameters);
void vTask3(void *pvParameters);

/* Variável global compartilhada */
volatile int contador = 0;

void setup() {
    Serial.begin(9600);

    // Criação das tasks com passagem de parâmetros
    xTaskCreate(vTask1, "Task1", configMINIMAL_STACK_SIZE, (void *)&contador, 1, &xTask1Handle);
    xTaskCreate(vTask2, "Task2", configMINIMAL_STACK_SIZE + 1024, (void *)&contador, 2, &xTask2Handle);
}

void loop() {
    // Não usamos o loop no FreeRTOS
}

/* Task 1: Controla LED1 */
void vTask1(void *pvParameters) {
    Serial.println("Iniciando task1");
    pinMode(LED1, OUTPUT);

    // Recebendo o ponteiro do contador
    int *pContador = (int *)pvParameters;

    while (1) {
        if (*pContador % 2 == 0) { // Verifica se o contador é par
            digitalWrite(LED1, HIGH);
            vTaskDelay(pdMS_TO_TICKS(500));
            digitalWrite(LED1, LOW);
            vTaskDelay(pdMS_TO_TICKS(500));
        } else { // Caso contrário, LED pisca mais rápido
            digitalWrite(LED1, HIGH);
            vTaskDelay(pdMS_TO_TICKS(200));
            digitalWrite(LED1, LOW);
            vTaskDelay(pdMS_TO_TICKS(200));
        }
    }
}

/* Task 2: Incrementa o contador */
void vTask2(void *pvParameters) {
    // Recebendo o ponteiro do contador
    int *pContador = (int *)pvParameters;
    Serial.println(" task2");
    while (1) {
        (*pContador)++; // Incrementa o valor do contador
        Serial.println("Contador: " + String(*pContador));

        // Suspende ou retoma a Task1 com base no valor do contador
        if (*pContador == 10) {
            vTaskSuspend(xTask1Handle);
            Serial.println("Suspendendo task1");
        }
        if (*pContador > 30 && eTaskGetState(xTask1Handle) == eSuspended) {
            vTaskResume(xTask1Handle);
            Serial.println("Resumindo task1");
        }
        if (*pContador == 45 && xTask3Handle == NULL) {
            xTaskCreate(vTask3, "Task3", configMINIMAL_STACK_SIZE, NULL, 3, &xTask3Handle);
            Serial.println("Iniciando Task3");
        }

        vTaskDelay(pdMS_TO_TICKS(1000));
        
    }
    Serial.println("Saindo task2");
}

/* Task 3: Controla LED2 */
void vTask3(void *pvParameters) {
    Serial.println(" Task3");
    pinMode(LED3, OUTPUT);
    int i = 0;
    while(true){
        digitalWrite(LED3, HIGH); // Liga o LED
        vTaskDelay(pdMS_TO_TICKS(500)); // Espera 500ms
        digitalWrite(LED3, LOW); // Desliga o LED
        vTaskDelay(pdMS_TO_TICKS(500)); // Espera mais 500ms
        // Após piscar 10 vezes, apaga o LED e deleta as tarefas
        digitalWrite(LED3, LOW);
        i++;
        if (i==10) break;
        
    }
    if (xTask1Handle != NULL) {
        vTaskDelete(xTask1Handle);
        Serial.println("Deleta task1");
    }
    vTaskDelete(NULL);
    Serial.println("Deleta task3");
}

