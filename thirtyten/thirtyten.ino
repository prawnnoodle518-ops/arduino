// 引脚定义
const int BUTTON_PIN = 2;  // 按键模块 IN 接 D2
const int RED_PIN    = 9;  // RGB R 接 D9
const int GREEN_PIN  = 10; // RGB G 接 D10
const int BLUE_PIN   = 11; // RGB B 接 D11

int colorState = 0;
int lastButtonState = LOW;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

void setColor(int red, int green, int blue) {
  analogWrite(RED_PIN, red);
  analogWrite(GREEN_PIN, green);
  analogWrite(BLUE_PIN, blue);
}

void updateColor(int state) {
  switch (state) {
    case 0: setColor(0, 0, 0);       break; // 关
    case 1: setColor(255, 0, 0);     break; // 红
    case 2: setColor(0, 255, 0);     break; // 绿
    case 3: setColor(0, 0, 255);     break; // 蓝
    case 4: setColor(255, 255, 0);   break; // 黄
    case 5: setColor(255, 0, 255);   break; // 紫
    case 6: setColor(0, 255, 255);   break; // 青
    case 7: setColor(255, 255, 255); break; // 白
  }
}

void setup() {
  pinMode(BUTTON_PIN, INPUT); // 模块本身已有电路，使用标准 INPUT 即可
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  updateColor(colorState);
}

void loop() {
  int reading = digitalRead(BUTTON_PIN);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    static int currentButtonState = LOW;
    if (reading != currentButtonState) {
      currentButtonState = reading;

      // 按键按下的瞬间（高电平）切换颜色
      if (currentButtonState == HIGH) {
        colorState = (colorState + 1) % 8;
        updateColor(colorState);
      }
    }
  }

  lastButtonState = reading;
}
