#include <QCoreApplication>
#include <iostream>
#include <thread>
#include "Writer.h"
#include "MBServer.h"

using namespace std;
const uint16_t MAX_PACKET_SIZE = 4096;
const uint16_t INPUT_REGS_SIZE = 600;
const uint16_t HOLD_REGS_SIZE = 16;
uint16_t inputRegs[INPUT_REGS_SIZE];
uint16_t holdRegs[HOLD_REGS_SIZE];

static void PrintRegs(char* bfr, int sz)
{
    uint32_t cnt = *(unsigned int*) bfr;
    cout << "cnt = " << cnt << ", ";
    uint16_t* dataBuff = (uint16_t*) (bfr + 4);
    for(int pos = 0; pos < INPUT_REGS_SIZE - 2; ++pos)
        cout << dataBuff[pos] << ", " ;
    cout << endl;
}

void ADC_Task()
 {
     Writer wr(inputRegs, INPUT_REGS_SIZE);
     while(true)
         wr.Refresh();
 }

union ChUS
{
    short val;
    char buf[2];
};


 void InterfaceTask()
 {
    char symb;
    unsigned int cnt;
    char ioBuff[MAX_PACKET_SIZE];
    int err;
    uint16_t size = sizeof (uint16_t)* INPUT_REGS_SIZE;

    while(true)
    {
        cout << "press any key & <ENTER>" << endl;
        cin >> symb;
        cout << "ok, " << symb << " its work" << endl;
        MBServer* srv = new MBServer(holdRegs, inputRegs, HOLD_REGS_SIZE, INPUT_REGS_SIZE);

        srv->Server(ioBuff, size, &err);
        PrintRegs(ioBuff, size);
        delete srv;

    }

 }


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    thread adc(ADC_Task);
    thread interface(InterfaceTask);
    adc.join();
    interface.join();
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
