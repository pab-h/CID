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

    const uint8_t centerX = 8;
    const uint8_t centerY = 12;

    // Clean previous data
    display.fillRect(0, 0, 28, 18, SSD1306_BLACK);

    // 1. Prints a full size arc
    drawArc(centerX, centerY, 1, 12, 225, 315, SSD1306_WHITE);

    // 2. Erase arcs above the current level
    if (level < 4)
        drawArc(centerX, centerY, 10, 11, 232, 310, SSD1306_BLACK);
    if (level < 3)
        drawArc(centerX, centerY, 8, 9, 230, 310, SSD1306_BLACK);
    if (level < 2)
        drawArc(centerX, centerY, 5, 7, 235, 305, SSD1306_BLACK);
    if (level < 1)
        drawArc(centerX, centerY, 3, 4, 235, 305, SSD1306_BLACK);

    // 3. Cuts the wifi icon if level = 0
    if (level == 0) {
        for (int i = 0; i <= 13; i++) {
            int x = i;
            int y = x - 3;
            display.drawPixel(x, y, SSD1306_WHITE);
            display.drawPixel(x, y - 1, SSD1306_BLACK);
            display.drawPixel(x, y + 1, SSD1306_BLACK);
        }
    }

    // 4. Print Wi-Fi
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(26, 5);
    display.print("Wi-Fi");

}


void Display::showBatteryIcon(uint8_t percentage) {

    const uint8_t x = SCREEN_WIDTH - 32;  
    const uint8_t y = 0;                  
    const uint8_t width = 28;
    const uint8_t height = 14;

    // Clear area
    display.fillRect(x - 30, y, width + 30, height, SSD1306_BLACK);

    // Batery contour
    display.drawRect(x, y + 2, width - 4, height - 4, SSD1306_WHITE);

    // Batery detail
    uint8_t tipHeight = 4;
    uint8_t tipY = y + 2 + ((height - 4 - tipHeight) / 2);
    display.drawRect(x + width - 4, tipY, 3, tipHeight, SSD1306_WHITE);

    // Fills the batery
    uint8_t fillWidth = map(percentage, 0, 100, 0, width - 6);

    if (fillWidth > 0) {
        display.fillRect(x + 2, y + 4, fillWidth, height - 8, SSD1306_WHITE);
    }

    // Print percentage text
    uint8_t textY = y + (height / 2) - 3;

    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
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

    //42

    display.fillRect(0, 42, SCREEN_WIDTH, 10, SSD1306_BLACK);
    
    drawIcon(0, 42, locationIconBitmap, 16, 16);

    display.setCursor(20, 46);
    display.print(location.c_str());

}

void Display::updateFromSystemStatus(const application::SystemStatus& status) {
    display.clearDisplay();

    // 1. Shows Wi-fi icon
    int wifiLevel = status.getConnectionLevel();
    showWiFiSignal(wifiLevel);

    // 2. Shows batery icon and percentage
    int battery = static_cast<int>(status.getBatteryLevel());
    showBatteryIcon(battery);

    // 3. Draw dotted line below the status bar
    for (uint8_t x = 0; x < SCREEN_WIDTH; x += 1) {
        if(x % 5 < 3) display.drawPixel(x, 17, SSD1306_WHITE);
    }

    // 4. Shows current activity
    std::string activity = status.activityToString();
    showActivity(" Act - " + activity);

    // 5. Shows CID current location
    std::string location = status.getCurrentSector();
    showLocation(" Loc - " + location);

    display.display();
}

/* Private functions */

void Display::drawArc(uint8_t x0, uint8_t y0, uint8_t rStart, uint8_t rEnd, int16_t start_angle, int16_t end_angle, uint16_t color) {

    for (uint8_t r = rStart; r <= rEnd; r++) {
        for (int16_t angle = start_angle; angle <= end_angle; angle++) {
            float rad = angle * 3.14159 / 180.0;
            int16_t x = x0 + r * cos(rad);
            int16_t y = y0 + r * sin(rad);
            display.drawPixel(x, y, color);
        }
    }

}

void Display::drawIcon(uint8_t x, uint8_t y, const uint8_t* bitmap, uint8_t w, uint8_t h) {

    display.drawBitmap(x, y, bitmap, w, h, SSD1306_WHITE);

}