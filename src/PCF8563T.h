#ifndef PCF8563T_H
#define PCF8563T_H

#include <Arduino.h>
#include <Wire.h>

class C_PCF8563T
{
  public:
    C_PCF8563T(){};

    byte decToBcd(byte val){return ( (val/10*16) + (val%10) );};
    byte bcdToDec(byte val){return ( (val/16*10) + (val%16) );};

    void SetWire(TwoWire *wire) {wire_ = wire;};

    //! 獲得時間
    int GetSecond();
    int GetMinute();
    int GetHour();
    int GetDay();
    int GetMonth();
    int GetYear();
    String GetTimeString(String interval=":");
    String GetDateString(String interval="-");
    String GetDatetimeString(String interval_date="-", String interval_middle=" ", String interval_time=":");
    
    //! 設定時間
    void SetSecond(int second);
    void SetMinute(int minute);
    void SetHour(int hour);
    void SetDay(int day);
    void SetMonth(int month);
    void SetYear(int year);
    void SetTime(time_t newTime);
    void SetTime(int Y, int M, int D, int h, int m, int s);

  private:
    TwoWire *wire_;
};

extern C_PCF8563T PCF8563;

#endif