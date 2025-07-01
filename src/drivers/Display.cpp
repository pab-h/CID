#include "drivers/Display.hpp"
#include "pins.hpp"
#include "env.hpp"

Display::Display() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET) {

}

void Display::begin() {

    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {

        Serial.println(F("Display OLED não encontrado"));
        return;

    }

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    display.display();

}

void Display::showBatteryLevel(int percentage) {

    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Bateria: ");
    display.print(percentage);
    display.println("%");

    display.display();

}

void Display::showSystemStatus(const std::string& status) {

    display.fillRect(0, 16, SCREEN_WIDTH, 8, SSD1306_BLACK);
    display.setCursor(0, 16);
    display.print("Status: ");
    display.println(status.c_str());
    display.display();
    
}


void Display::showBatteryIcon(int percentage) {

    const int x = SCREEN_WIDTH - 30;  // posição X do ícone
    const int y = 0;                  // posição Y do ícone
    const int width = 24;
    const int height = 12;

    display.fillRect(x, y, width, height, SSD1306_BLACK);

    // Desenha o contorno da bateria
    display.drawRect(x, y + 2, width - 4, height - 4, SSD1306_WHITE);

    display.drawRect(x + width - 4, y + 5, 3, height - 8, SSD1306_WHITE);


    int fillWidth = map(percentage, 0, 100, 0, width - 6);
    if (fillWidth > 0) {
        display.fillRect(x + 2, y + 4, fillWidth, height - 8, SSD1306_WHITE);
    }

    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(x - 26, y + 2);
    display.print(percentage);
    display.print("%");

    display.display();
}



