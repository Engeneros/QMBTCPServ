#include <QCoreApplication>



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    return a.exec();
}


//#include "FreeRTOS.h"
//#include "queue.h"

//#define BUF_SIZE 256

//// Создаем два буфера
//uint8_t buffer1[BUF_SIZE];
//uint8_t buffer2[BUF_SIZE];

//QueueHandle_t xPointerQueue;

//void vTaskWriter(void *pvParameters) {
//    uint8_t *pCurrentBuffer = buffer1; // Начинаем с первого

//    for(;;) {
//        // 1. Заполняем текущий буфер данными
//        fill_buffer_with_data(pCurrentBuffer, BUF_SIZE);

//        // 2. Отправляем УКАЗАТЕЛЬ на заполненный буфер в очередь
//        // Мы ждем максимум 100мс, если очередь полна
//        if (xQueueSend(xPointerQueue, &pCurrentBuffer, pdMS_TO_TICKS(100)) == pdPASS) {
//            // 3. Переключаемся на другой буфер (Double Buffering)
//            // Пока Читатель работает с одним, мы будем заполнять другой
//            pCurrentBuffer = (pCurrentBuffer == buffer1) ? buffer2 : buffer1;
//        } else {
//            // Ошибка: Читатель слишком медленный, очередь переполнена
//        }
//    }
//}

//void vTaskReader(void *pvParameters) {
//    uint8_t *pReceivedBuffer;

//    for(;;) {
//        // Ждем указатель из очереди (вечно)
//        if (xQueueReceive(xPointerQueue, &pReceivedBuffer, portMAX_DELAY) == pdPASS) {
//            // Читаем данные и отправляем в сеть
//            send_to_network(pReceivedBuffer, BUF_SIZE);
//            // Теперь этот буфер свободен, и Писатель сможет его использовать снова
//        }
//    }
//}

//// Инициализация
//void main() {
//    xPointerQueue = xQueueCreate(2, sizeof(uint8_t *));
//    xTaskCreate(vTaskWriter, "Writer", 1024, NULL, 2, NULL);
//    xTaskCreate(vTaskReader, "Reader", 1024, NULL, 1, NULL);
//    vTaskStartScheduler();
//}
