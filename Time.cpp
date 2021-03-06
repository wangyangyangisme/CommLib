/*
 * File:   CTime.cpp
 * Author: Administrator
 *
 * Created on 2014年1月26日, 下午4:49
 */

#include <bits/time.h>
#include <sys/time.h>

#include "Time.h"
namespace CommLib {

    Time::Time(time_t tt) : tt_(tt) {
        localtime_r(&tt, &tm_);
    }

    Time::Time() : tt_(0) {
    }

    unsigned long mktime(unsigned int year, unsigned int mon,
            unsigned int day, unsigned int hour,
            unsigned int min, unsigned int sec) {
        if (0 >= (int) (mon -= 2)) { /* 1..12 -> 11,12,1..10 */
            mon += 12; /* Puts Feb last since it has leap day */
            year -= 1;
        }

        return (((
                (unsigned long) (year / 4 - year / 100 + year / 400 + 367 * mon / 12 + day) +
                year * 365 - 719499
                )*24 + hour /* now have hours */
                )*60 + min /* now have minutes */
                )*60 + sec; /* finally seconds */
    }

    Time::Time(int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec) {
        tt_ = mktime(nYear, nMonth, nDay, nHour, nMin, nSec) + __timezone;
        localtime_r(&tt_, &tm_);

    }

    Time::Time(const Time& orig) : tm_(orig.tm_), tt_(orig.tt_) {
    }

    Time::~Time() {
    }

    Time Time::GetCurrentTime() {
        time_t _tt = time(NULL);
        return Time(_tt);
    }

    long Time::GetCurrTick() {
        timeval tm;
        gettimeofday(&tm, NULL);
        return ( tm.tv_sec * 1000000 + tm.tv_usec);
    }

    int Time::GetDay() {
        return tm_.tm_yday + 1;
    }

    int Time::GetDayOfWeek() {
        return tm_.tm_wday;
    }

    int Time::GetHour() {
        return tm_.tm_hour;
    }

    int Time::GetMinute() {
        return tm_.tm_min;
    }

    int Time::GetMonth() {
        return tm_.tm_mon + 1;
    }

    int Time::GetSecond() {
        return tm_.tm_sec;
    }

    time_t Time::GetTime() {
        return tt_;
    }

    int Time::GetYear() {
        return tm_.tm_year + 1900;
    }

    Time Time::operator +(TimeSpan &span) {
        return Time(tt_ + span.GetTimeSpan());
    }

    Time Time::operator -(TimeSpan &span) {
        return Time(tt_ - span.GetTimeSpan());
    }

    TimeSpan Time::operator -(Time &tm) {
        return TimeSpan(tt_ - tm.tt_);
    }

    Time Time::operator +(time_t tt) {
        return Time(tt_ + tt);
    }

    Time Time::operator -(time_t tt) {
        return Time(tt_ - tt);
    }
}
