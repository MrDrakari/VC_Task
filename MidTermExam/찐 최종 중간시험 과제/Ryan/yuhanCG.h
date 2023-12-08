#pragma once
#include <Windows.h>

void DrawBox(HDC hdc, int isMouseRButtonPressed, POINT startPoint, POINT endPoint, POINT newstartPoint, POINT newendPoint);

void DrawCircle(HDC hdc, int isMouseLButtonPressed, int isMouseRButtonPressed, POINT startPoint, POINT endPoint, POINT newendPoint, POINT newstartPoint);

void DrawBonobono(HDC hdc, int blink);

void DrawRyan(HDC hdc, POINT startPoint, POINT endPoint);

void DrawCube(HDC hdc, POINT startPoint, POINT endPoint);