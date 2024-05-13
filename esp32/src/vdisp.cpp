/*
  This piece of software acts as like a HD44780 LCD on the I2C bus. 
  
  The Nano receives the HD44780 instructions as an I2C slave using the default pins A4 (SDA) and A5 (SCL).
  It applies the instructions to a local representation of the display content. On each change
  of the display content it sends the whole display content (80 characters) out via the serial interface (TX pin).

  More details about the HD44780 LCD instruction set: 
  * https://mil.ufl.edu/3744/docs/lcdmanual/commands.html
  * https://www.sparkfun.com/datasheets/LCD/HD44780.pdf

  Only instructions that affect the display content are implemented (no read, no character generation).
*/

#include <Arduino.h>
#include <Wire.h>
#include <vdisp.h>

void onReceive(int count) {
    //Serial.println("onReceive");
    //digitalWrite(LED_BUILTIN, LOW);
    while(Wire.available()) {
        uint8_t in = Wire.read();
        bool enable = in & 0x04;
        if (!enable) {
            continue;
        }

        if (nibbleIndex) {
            loNibble = in;

            bool rs = loNibble & 0x01;
            bool rw = loNibble & 0x02;
            uint8_t cmd = (hiNibble & 0xF0) | ((loNibble & 0xF0) >> 4);

            handleCommand(rs, rw, cmd);
        } else {
            loNibble = 0;
            hiNibble = in;
        }
        nibbleIndex = !nibbleIndex;
    }
    //digitalWrite(LED_BUILTIN, HIGH);
}

void handleCommand(bool rs, bool rw, uint8_t cmd) {
    //Serial.printf("handleCommand %d %d 0x%.2x\n",rs,rw,cmd);
    if (rw) {
        //Serial.println("read not implemented");
        return;
    }

    if (rs) {
        writeData(cmd);
        return;
    }

    if (cmd == 0x01) {
        clearDisplay();
    } else if ((cmd & 0xFE) == 0x02) {
        cursorHome();
    } else if ((cmd & 0xFC) == 0x04) {
        bool increment = (cmd & 0x02);
        bool shift = (cmd & 0x01);
        setEntryMode(increment, shift);
    } else if ((cmd & 0xF8) == 0x08) {
        bool display = (cmd & 0x04);
        bool cursor = (cmd & 0x02);
        bool blink = (cmd & 0x01);
        setOnOff(display, cursor, blink);
    } else if ((cmd & 0xF0) == 0x10) {
        bool display = (cmd & 0x08);
        bool right = (cmd & 0x04);
        setShift(display, right);
    } else if ((cmd & 0xE0) == 0x20) {
        bool full = (cmd & 0x10);
        bool twoLines = (cmd & 0x08);
        bool bigFont = (cmd & 0x04);
        setFunction(full, twoLines, bigFont);
    } else if ((cmd & 0xC0) == 0x40) {
        uint8_t address = (cmd & 0x3F);
        setCGAddress(address);
    } else if ((cmd & 0x80) == 0x80) {
        uint8_t address = (cmd & 0x7F);
        setDDAddress(address);
    } 
}

void clearDisplay() {
  // https://mil.ufl.edu/3744/docs/lcdmanual/commands.html#ClearDisplay
  for (int i = 0; i < LCD_LENGTH; i+=1) {
    ddram[i] = 0x20;
  }
  dirty = true;
  currentAddress = 0;
  entryModeIncrement = true;

}

void cursorHome() {
  // https://mil.ufl.edu/3744/docs/lcdmanual/commands.html#CursorHome
  currentAddress = 0;
}

void setEntryMode(bool increment, bool shift) {
  // https://mil.ufl.edu/3744/docs/lcdmanual/commands.html#EntryMode
  entryModeIncrement = increment;
  entryModeShift = shift;
}

void setOnOff(bool display, bool cursor, bool blink) {
  // https://mil.ufl.edu/3744/docs/lcdmanual/commands.html#Doo
  // not relevant for the display content
}

void setShift(bool display, bool right) {
  // https://mil.ufl.edu/3744/docs/lcdmanual/commands.html#Cds
  if (right) {
    currentAddress = (currentAddress + 1) % LCD_LENGTH;
  } else if (currentAddress > 0) {
    currentAddress -= 1;
  } else {
    currentAddress = LCD_LENGTH - 1;
  }
}

void setFunction(bool full, bool twoLines, bool bigFont) {
  // https://mil.ufl.edu/3744/docs/lcdmanual/commands.html#Fs
  // not relevant for the display content
}

void setCGAddress(uint8_t address) {
  // https://mil.ufl.edu/3744/docs/lcdmanual/commands.html#Sca
  ramIndex = CGRAM;
}

void setDDAddress(uint8_t address) {
  // https://mil.ufl.edu/3744/docs/lcdmanual/commands.html#Sda
  ramIndex = DDRAM;
  currentAddress = address % LCD_LENGTH;
}

void writeData(char data) {
  // https://mil.ufl.edu/3744/docs/lcdmanual/commands.html#Wr
  if (ramIndex == CGRAM) {
    return;
  }

  ddram[currentAddress] = data;
  dirty = true;

  if (entryModeIncrement) {
    currentAddress = (currentAddress + 1) % LCD_LENGTH;
  }
}
