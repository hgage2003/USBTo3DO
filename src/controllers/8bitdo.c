#include "bsp/board.h"

#include <stdlib.h>

#include "8bitdo.h"
#include "hid_parser.h"

//#define _DEBUG_MAPPER_

bool map_8bitDo_M30(uint8_t instance, uint8_t *id, controler_type *type, void **res, void *ctrl_v)
 {
  hid_controller *ctrl =(hid_controller*)ctrl_v;
  _3do_joypad_report *result = malloc(sizeof(_3do_joypad_report));
  *result = new3doPadReport();
  *type = JOYPAD;
  *id = ctrl->index + instance;
  hid_buttons *btn = & ctrl->buttons[ctrl->index];

  result->up = btn->ABS_Y <= 64;
  result->down = btn->ABS_Y >= 196;
  result->left = btn->ABS_X <= 64;
  result->right = btn->ABS_X >= 196;
  result->X = btn->BASE5;
  result->P = btn->BASE6 || btn->TOP2;
  result->A = btn->TRIGGER;
  result->B = btn->THUMB;
  result->C = btn->BASE2;
  result->L = btn->BASE3 || btn->TOP;
  result->R = btn->BASE || btn->BASE4;

  if (ctrl->hasHat[ctrl->index]) {
    result->up |= btn->HAT_UP;
    result->down |= btn->HAT_DOWN;
    result->left |= btn->HAT_LEFT;
    result->right |= btn->HAT_RIGHT;
  }

  #ifdef _DEBUG_MAPPER_
  //used for mapping debug
  printf("(up, down, left, right) (%d %d %d %d) (X,P,A,B,C,L,R)(%d %d %d %d %d %d %d)\n",
  result->up, result->down, result->left, result->right, result->X, result->P, result->A, result->B, result->C, result->L, result->R);
  #endif
  *res = (void *)(result);
  return true;
}