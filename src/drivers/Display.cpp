#include "drivers/Display.hpp"
#include "pins.hpp"
#include "env.hpp"

using namespace drivers;

static const uint8_t locationIconBitmap[32] PROGMEM = {
    0b00000111, 0b11100000,
    0b00011111, 0b11111000,
    0b00111111, 0b11111100,
    0b00111100, 0b00111100,
    0b01111000, 0b00011110,
    0b01111000, 0b00011110,
    0b01111000, 0b00011110,
    0b01111000, 0b00011110,
    0b00111100, 0b00111100,
    0b00111111, 0b11111100,
    0b00011111, 0b11111000,
    0b00011111, 0b11111000,
    0b00001111, 0b11110000,
    0b00000111, 0b11100000,
    0b00000011, 0b11000000,
    0b00000001, 0b10000000,
};

static const uint8_t activityIconBitmap[32] PROGMEM = {
    0b00000000, 0b00000000,
    0b00001000, 0b00000000,
    0b00001000, 0b00000000,
    0b00010100, 0b00000000,
    0b00010100, 0b00000000,
    0b00100010, 0b00000000,
    0b00100010, 0b00000000,
    0b00100010, 0b00000001,
    0b11000001, 0b00000110,
    0b00000000, 0b10001000,
    0b00000000, 0b10001000,
    0b00000000, 0b01010000,
    0b00000000, 0b01010000,
    0b00000000, 0b00100000,
    0b00000000, 0b00100000,
    0b00000000, 0b00000000
};

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

}

void Display::showWiFiSignal(uint8_t level) {
    display.fillRect(0, 0, 28, 18, SSD1306_BLACK);

    const int centerX = 9;
    const int centerY = 10;

    if (level == 0) {
        // Desenha setores preenchidos (de dentro até fora)
        for (int r = 1; r <= 10; r++) {
            for (int angle = 225; angle <= 315; angle++) {
                float rad = angle * 3.14159 / 180.0;
                int x = centerX + r * cos(rad);
                int y = centerY + r * sin(rad);
                display.drawPixel(x, y, SSD1306_WHITE);
            }
        }

        // Linha branca atravessando o arco na diagonal (corte central)
        for (int i = 3; i <= 13; i++) {

            int x1 = i;
            int y1 = x1-5;
            
            int x2 = i;
            int y2 = -x2-5;
        
            display.drawPixel(x1, y1, SSD1306_WHITE);

            display.drawPixel(x1, y1-1, SSD1306_BLACK);
            display.drawPixel(x1, y1+1, SSD1306_BLACK);
            display.drawPixel(x1, y1-2, SSD1306_BLACK);
            display.drawPixel(x1, y1+2, SSD1306_BLACK);

            display.drawPixel(x2, y2-1, SSD1306_BLACK);
            display.drawPixel(x2, y2+1, SSD1306_BLACK);
            display.drawPixel(x2, y2-2, SSD1306_BLACK);
            display.drawPixel(x2, y2+2, SSD1306_BLACK);

        }


    } else {
        if (level >= 1) display.fillCircle(centerX, centerY, 1, SSD1306_WHITE);
        if (level >= 2) drawArc(centerX, centerY, 4, 225, 315, SSD1306_WHITE);
        if (level >= 3) drawArc(centerX, centerY, 7, 225, 315, SSD1306_WHITE);
        if (level >= 4) drawArc(centerX, centerY, 10, 225, 315, SSD1306_WHITE);
    }
}

void Display::showBatteryIcon(uint8_t percentage) {
    const int x = SCREEN_WIDTH - 32;  // posição X do ícone
    const int y = 0;                  // agora começa no topo do display
    const int width = 28;
    const int height = 14;

    // Limpa a área onde o ícone será desenhado
    display.fillRect(x - 30, y, width + 30, height, SSD1306_BLACK); // inclui área do texto

    // Desenha o contorno da bateria
    display.drawRect(x, y + 2, width - 4, height - 4, SSD1306_WHITE);

    // Desenha o bico da bateria centralizado verticalmente
    int tipHeight = 4;
    int tipY = y + 2 + ((height - 4 - tipHeight) / 2);
    display.drawRect(x + width - 4, tipY, 3, tipHeight, SSD1306_WHITE);

    // Desenha o preenchimento da bateria proporcional ao nível
    int fillWidth = map(percentage, 0, 100, 0, width - 6);
    if (fillWidth > 0) {
        display.fillRect(x + 2, y + 4, fillWidth, height - 8, SSD1306_WHITE);
    }

    // Texto de porcentagem ao lado esquerdo do ícone
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    int textY = y + (height / 2) - 3;
    display.setCursor(x - 26, textY);
    display.print(percentage);
    display.print("%");

}

void Display::showActivity(const std::string& status) {

    display.fillRect(0, 24, SCREEN_WIDTH, 16, SSD1306_BLACK);

    drawIcon(0, 22, activityIconBitmap, 16, 16);

    display.setCursor(20, 26);
    display.print(status.c_str());

}

void Display::showLocation(const std::string& location) {

    display.fillRect(0, 42, SCREEN_WIDTH, 10, SSD1306_BLACK);
    
    drawIcon(0, 42, locationIconBitmap, 16, 16);

    display.setCursor(20, 44);
    display.print(location.c_str());

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
    std::string activity = status.activityToString();
    showActivity(" Act-> " + activity);

    // 4. Mostra a localização do CID
    std::string location = status.getCurrentSector();
    showLocation(" Loc-> " + location);

    display.display();
}

/* Private functions */

void Display::drawArc(uint8_t x0, uint8_t y0, uint8_t r, int16_t start_angle, int16_t end_angle, uint16_t color) {
    for (int16_t angle = start_angle; angle <= end_angle; angle++) {
        float rad = angle * 3.14159 / 180.0;
        int16_t x = x0 + r * cos(rad);
        int16_t y = y0 + r * sin(rad);
        display.drawPixel(x, y, color);
    }
}

void Display::drawIcon(uint8_t x, uint8_t y, const uint8_t* bitmap, uint8_t w, uint8_t h) {

    display.drawBitmap(x, y, bitmap, w, h, SSD1306_WHITE);

}