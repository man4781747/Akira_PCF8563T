#include "PCF8563T.h"
#include <Arduino.h>
#include <esp_log.h>
#include <Wire.h>
#include <TimeLib.h>

int C_PCF8563T::GetSecond() {
  (*wire_).beginTransmission(0x51);
  (*wire_).write(0x02);
  (*wire_).endTransmission();
  (*wire_).requestFrom(0x51, 1);
  return bcdToDec((*wire_).read() & 0b01111111);
}

void C_PCF8563T::SetSecond(int second) {
  (*wire_).beginTransmission(0x51);
  (*wire_).write(0x02);
  (*wire_).write(decToBcd(second) & 0b01111111);
  (*wire_).endTransmission();
}

int C_PCF8563T::GetMinute() {
  (*wire_).beginTransmission(0x51);
  (*wire_).write(0x03);
  (*wire_).endTransmission();
  (*wire_).requestFrom(0x51, 1);
  return bcdToDec((*wire_).read() & 0b01111111);
}

void C_PCF8563T::SetMinute(int minute) {
  (*wire_).beginTransmission(0x51);
  (*wire_).write(0x03);
  (*wire_).write(decToBcd(minute) & 0b01111111);
  (*wire_).endTransmission();
}

int C_PCF8563T::GetHour() {
  (*wire_).beginTransmission(0x51);
  (*wire_).write(0x04);
  (*wire_).endTransmission();
  (*wire_).requestFrom(0x51, 1);
  return bcdToDec((*wire_).read() & 0b00111111);
}

void C_PCF8563T::SetHour(int hour) {
  (*wire_).beginTransmission(0x51);
  (*wire_).write(0x04);
  (*wire_).write(decToBcd(hour) & 0b00111111);
  (*wire_).endTransmission();
}

int C_PCF8563T::GetDay() {
  (*wire_).beginTransmission(0x51);
  (*wire_).write(0x05);
  (*wire_).endTransmission();
  (*wire_).requestFrom(0x51, 1);
  return bcdToDec((*wire_).read() & 0b00111111);
}

void C_PCF8563T::SetDay(int day) {
  (*wire_).beginTransmission(0x51);
  (*wire_).write(0x05);
  (*wire_).write(decToBcd(day) & 0b00111111);
  (*wire_).endTransmission();
}

int C_PCF8563T::GetMonth() {
  (*wire_).beginTransmission(0x51);
  (*wire_).write(0x07);
  (*wire_).endTransmission();
  (*wire_).requestFrom(0x51, 1);
  return bcdToDec((*wire_).read() & 0b00011111);
}

void C_PCF8563T::SetMonth(int month) {
  (*wire_).beginTransmission(0x51);
  (*wire_).write(0x07);
  (*wire_).write(decToBcd(month) & 0b00011111);
  (*wire_).endTransmission();
}

int C_PCF8563T::GetYear() {
  (*wire_).beginTransmission(0x51);
  (*wire_).write(0x08);
  (*wire_).endTransmission();
  (*wire_).requestFrom(0x51, 1);
  return bcdToDec((*wire_).read())+ 2000;
}

void C_PCF8563T::SetYear(int year) {
  (*wire_).beginTransmission(0x51);
  (*wire_).write(0x08);
  (*wire_).write(decToBcd(year%100) & 0b11111111);
  (*wire_).endTransmission();
}

String C_PCF8563T::GetDateString(String interval)
{
  char date[11];
  sprintf(date, "%04d%s%02d%s%02d",
    GetYear(), interval.c_str(), GetMonth(), interval.c_str(), GetDay()
  );
  return String(date);
}

String C_PCF8563T::GetTimeString(String interval)
{
  char time_[11];
  sprintf(time_, "%02d%s%02d%s%02d",
    GetHour(), interval.c_str(), GetMinute(), interval.c_str(), GetSecond()
  );
  return String(time_);
}

String C_PCF8563T::GetDatetimeString(String interval_date, String interval_middle, String interval_time)
{
  return GetDateString(interval_date)+interval_middle+GetTimeString(interval_time);
}

void C_PCF8563T::SetTime(time_t newTime)
{
  SetYear(year(newTime));
  SetMonth(month(newTime));
  SetDay(day(newTime));
  SetHour(hour(newTime));
  SetMinute(minute(newTime));
  SetSecond(second(newTime));
}

void C_PCF8563T::SetTime(int Y, int M, int D, int h, int m, int s)
{
  SetYear(Y);
  SetMonth(M);
  SetDay(D);
  SetHour(h);
  SetMinute(m);
  SetSecond(s);
}

C_PCF8563T PCF8563;