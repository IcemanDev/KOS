#pragma once

//////////////////////////////////////////////////////////////////////////
// Keyboard
void KKeyboardInit();
int  KKeyboardReadChar();
char KKeyTranslate(int keycode);
bool KKeyboardHasInput();

