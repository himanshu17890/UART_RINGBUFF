#include <Wire.h>git
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define BUFFER_SIZE 16

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

typedef struct
{
    uint8_t buffer[BUFFER_SIZE];
    volatile uint8_t head;
    volatile uint8_t tail;
} RingBuffer;

RingBuffer uartBuffer = {0};

char lastChar = '-';

bool isEmpty(void)
{
    return (uartBuffer.head == uartBuffer.tail);
}

bool isFull(void)
{
    return (((uartBuffer.head + 1) % BUFFER_SIZE) == uartBuffer.tail);
}

void push(uint8_t data)
{
    if (!isFull())
    {
        uartBuffer.buffer[uartBuffer.head] = data;
        uartBuffer.head = (uartBuffer.head + 1) % BUFFER_SIZE;

        Serial.print("Push : ");
        Serial.println((char)data);
    }
    else
    {
        Serial.println("Buffer Full!");
    }
}

uint8_t pop(void)
{
    uint8_t data = 0;

    if (!isEmpty())
    {
        data = uartBuffer.buffer[uartBuffer.tail];
        uartBuffer.tail = (uartBuffer.tail + 1) % BUFFER_SIZE;
    }

    return data;
}

void updateOLED(void)
{
    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    display.setCursor(0, 0);
    display.println("UART Ring Buffer");

    display.setCursor(0, 18);
    display.print("Last RX : ");
    display.println(lastChar);

    display.setCursor(0, 36);
    display.print("Head : ");
    display.println(uartBuffer.head);

    display.setCursor(0, 50);
    display.print("Tail : ");
    display.println(uartBuffer.tail);

    display.display();
}

void setup()
{
    Serial.begin(115200);

    Wire.begin(21, 22);

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println("OLED Failed");

        while (1);
    }

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    display.setCursor(0, 0);
    display.println("UART Ring Buffer");

    display.setCursor(0, 18);
    display.println("Ready...");

    display.display();

    Serial.println("----------------------------");
    Serial.println("UART Ring Buffer Ready");
    Serial.println("Type in Serial Monitor...");
    Serial.println("----------------------------");
}

void loop()
{
    while (Serial.available())
    {
        char ch = Serial.read();

        Serial.print("UART RX : ");
        Serial.println(ch);

        push(ch);
    }

    while (!isEmpty())
    {
        lastChar = pop();

        Serial.print("POP : ");
        Serial.println(lastChar);
    }

    updateOLED();

    delay(100);
}