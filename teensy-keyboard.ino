/**
 * Script to create a USB keyboard out of two parts:
 * - Teensy LC - https://www.pjrc.com/teensy/
 * - Game Boy Zero Button PCB Board - https://handheldlegend.com/products/game-boy-zero-button-pcb-board
 */
#include <Bounce.h>

#define NUM_KEYS 12

struct Key
{
  char keycode;
  Bounce *bounce;
};

Key keys[NUM_KEYS];

Key key(char keycode, int pin)
{
  Key *ret = new Key;
  ret->keycode = keycode;
  ret->bounce = new Bounce(pin, 10);
  pinMode(pin, INPUT_PULLUP);
  return *ret;
}

// original configuration
void setupKeysOld()
{
  keys[0] = key('w', 0);
  keys[1] = key('s', 1);
  keys[2] = key('a', 2);
  keys[3] = key('d', 3);
  keys[4] = key('p', 4);
  keys[5] = key('l', 5);
  keys[6] = key('o', 6);
  keys[7] = key('k', 7);
  keys[8] = key('x', 8);
  keys[9] = key('z', 9);
  keys[10] = key('q', 10);
  keys[11] = key('e', 11);
}

/**
 * Configure keys that are in the same order as pins on the key board
 */
void setupKeys()
{
  // KEY BOARD
  keys[0] = key('w', 0);   // up
  keys[1] = key('s', 1);   // down
  keys[2] = key('a', 2);   // left
  keys[3] = key('d', 3);   // right
  keys[4] = key('p', 4);   // start
  keys[5] = key('o', 5);   // select
  keys[6] = key('f', 6);   // A
  keys[7] = key('g', 7);   // B
  keys[8] = key('r', 8);   // X
  keys[9] = key('t', 9);   // Y
  keys[10] = key('q', 10); // L
  keys[11] = key('e', 11); // R
  //keys[0] = key('', 0); // GND

  // ADDITIONAL KEY
}

void setup()
{
  setupKeys();
  Keyboard.begin();
}

void loop()
{
  for (int i = 0; i < NUM_KEYS; i++)
  {
    keys[i].bounce->update();

    if (keys[i].bounce->fallingEdge())
    {
      Keyboard.press(keys[i].keycode);
    }
    else if (keys[i].bounce->risingEdge())
    {
      Keyboard.release(keys[i].keycode);
    }
  }
}
