#include "drivers/Display.hpp"
#include "pins.hpp"
#include "env.hpp"

using namespace drivers;

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

void Display::showActivity(const std::string& status) {

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

void Display::showWiFiSignal(int level) {
    display.fillRect(0, 0, 24, 16, SSD1306_BLACK);

    const int centerX = 10;
    const int centerY = 7;
    const int xOffset = 1;
    const int lineHalfLen = 4;

    display.fillRect(0, 0, 24, 16, SSD1306_BLACK);

    if (level == 0) {
        drawArc(centerX, centerY, 4, 225, 315, SSD1306_WHITE);
        drawArc(centerX, centerY, 7, 225, 315, SSD1306_WHITE);
        //drawArc(centerX, centerY, 10, 225, 315, SSD1306_WHITE);
        display.fillCircle(centerX, centerY, 1, SSD1306_WHITE);

        for (int i = -lineHalfLen; i <= lineHalfLen; i++) {
            int x = centerX + xOffset + i;
            int y = centerY + i;
            if (x >= 0 && x < 24 && y >= 0 && y < 16) {
                display.drawPixel(x, y, SSD1306_WHITE);
        }
    }
    
    } else {
        if (level >= 1) display.fillCircle(centerX, centerY, 1, SSD1306_WHITE);
        if (level >= 2) drawArc(centerX, centerY, 4, 225, 315, SSD1306_WHITE);
        if (level >= 3) drawArc(centerX, centerY, 7, 225, 315, SSD1306_WHITE);
        if (level >= 4) drawArc(centerX, centerY, 10, 225, 315, SSD1306_WHITE);
    }

    display.display();
}

void Display::updateFromSystemStatus(const application::SystemStatus& status) {

    display.clearDisplay();

    // 1. Mostra ícone de Wi-Fi
    int wifiLevel = status.getConnectionLevel();
    showWiFiSignal(wifiLevel);

    // 2. Mostra ícone e porcentagem da bateria
    int battery = static_cast<int>(status.getBatteryLevel());
    showBatteryIcon(battery);

    // 3. Mostra a atividade atual
    std::string activity = status.activityToString() + " - " + status.getCurrentSector();
    showActivity(activity);

    display.display();
    
}

void Display::drawArc(int16_t x0, int16_t y0, int16_t r, int16_t start_angle, int16_t end_angle, uint16_t color) {
    for (int16_t angle = start_angle; angle <= end_angle; angle++) {
        float rad = angle * 3.14159 / 180.0;
        int16_t x = x0 + r * cos(rad);
        int16_t y = y0 + r * sin(rad);
        display.drawPixel(x, y, color);
    }
}


