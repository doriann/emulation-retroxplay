#include <sys/time.h>
#include "ISystemDateTimeInterface.h"
#include "DateTime.h"

static class SystemDateTimeInterface : public ISystemDateTimeInterface
{
  private:
    static bool Initialize();

  public:
    static bool Initialized;

    char LoadTimeZone() override
    {
      time_t t = time(NULL);
      struct tm* lt = localtime(&t);
      return (char)(lt->tm_gmtoff / (15 * 60* 60));
    }

    void SaveTimeZone(char tz) override
    {
      (void)tz; // Ignore
    }

    bool LoadRTCValues(short &millis, short &year, char &month, char &day, char &hour, char &minute, char &second) override
    {
      time_t t = time(NULL);
      struct tm* lt = localtime(&t);
      second = lt->tm_sec;
      minute = lt->tm_min;
      hour   = lt->tm_hour;
      day    = lt->tm_mday;
      month  = lt->tm_mon + 1;
      year   = lt->tm_year + 1900;
      return true;
    }

    void SaveRTCValues(short millis, short year, char month, char day, char hour, char minute, char second) override
    {
      (void)millis;
      (void)year;
      (void)month;
      (void)day;
      (void)hour;
      (void)minute;
      (void)second;
    }
} SystemDateTime;

bool SystemDateTimeInterface::Initialize()
{
  DateTime::SetSystemInterface(&SystemDateTime);
  DateTime dt;
}

bool SystemDateTimeInterface::Initialized = SystemDateTimeInterface::Initialize();
