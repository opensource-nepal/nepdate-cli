/* 
 * Copyright (C) 2024 khumnath cg <mail@khumnath.com.np>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
 #include "bikram.h"
 #include <iostream>
 #include <string>
 #include <map>
 #include <ctime>
 #include <vector>
 
 // Devanagari digit mapping
 std::map<char, std::string> devanagariNumbers = {
     {'0', "०"}, {'1', "१"}, {'2', "२"}, {'3', "३"}, {'4', "४"},
     {'5', "५"}, {'6', "६"}, {'7', "७"}, {'8', "८"}, {'9', "९"}
 };
 
 // Month and weekday data
 std::vector<std::string> englishMonths = {
     "January", "February", "March", "April", "May", "June",
     "July", "August", "September", "October", "November", "December"
 };
 
 std::vector<std::string> englishMonthsAbbr = {
     "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
 };
 
 std::vector<std::string> englishMonthsDevnagari = {
     "जनवरी", "फेब्रुअरी", "मार्च", "अप्रिल", "मे", "जुन",
     "जुलाई", "अगस्ट", "सेप्टेम्बर", "अक्टोबर", "नोभेम्बर", "डिसेम्बर"
 };
 
 std::vector<std::string> romanizedNepaliMonths = {
     "Baisakh", "Jestha", "Ashadh", "Shrawan", "Bhadra", "Ashwin",
     "Kartik", "Mangsir", "Poush", "Magh", "Falgun", "Chaitra"
 };
 
 std::vector<std::string> romanizedNepaliMonthsAbbr = {
     "Bai", "Jes", "Asa", "Shr", "Bha", "Asw", "Kar", "Man", "Pou", "Mag", "Fal", "Cha"
 };
 
 std::vector<std::string> nepaliMonths = {
     "बैशाख", "जेष्ठ", "आषाढ", "श्रावण", "भाद्रपद", "आश्विन",
     "कार्तिक", "मङ्सिर", "पौष", "माघ", "फाल्गुन", "चैत्र"
 };
 
 std::vector<std::string> nepaliMonthsAbbr = {
     "बै.", "जे.", "आ.", "श्रा.", "भा.", "आ.", "का.", "मं.", "पौ.", "मा.", "फा.", "चै."
 };
 
 std::vector<std::string> englishWeekdays = {
     "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
 };
 
 std::vector<std::string> englishWeekdaysAbbr = {
     "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
 };
 
 std::vector<std::string> romanizedNepaliWeekdays = {
     "Ravivar", "Somvar", "Mangalvar", "Budhvar", "Brihaspativar", "Shukravar", "Shanivar"
 };
 
 std::vector<std::string> romanizedNepaliWeekdaysAbbr = {
     "Ravi", "Som", "Mangal", "Budh", "Brihas", "Shukra", "Shani"
 };
 
 std::vector<std::string> nepaliWeekdays = {
     "आइतबार", "सोमबार", "मङ्गलबार", "बुधबार", "बिहीबार", "शुक्रबार", "शनिबार"
 };
 
 std::vector<std::string> nepaliWeekdaysAbbr = {
     "आइत", "सोम", "मङ्गल", "बुध", "बिही", "शुक्र", "शनि"
 };
 
 // Get current date
 void getCurrentDate(int &year, int &month, int &day) {
     time_t t = time(0);
     struct tm * now = localtime(&t);
     year = now->tm_year + 1900;
     month = now->tm_mon + 1;
     day = now->tm_mday;
 }
 
 // Get current date and time
 void getCurrentDateTime(int &year, int &month, int &day, int &hour, int &minute, int &second) {
     time_t t = time(0);
     struct tm * now = localtime(&t);
     year = now->tm_year + 1900;
     month = now->tm_mon + 1;
     day = now->tm_mday;
     hour = now->tm_hour;
     minute = now->tm_min;
     second = now->tm_sec;
 }
 
 // Get weekday from Gregorian
 int getWeekday(int year, int month, int day) {
     std::tm t = {};
     t.tm_year = year - 1900;
     t.tm_mon = month - 1;
     t.tm_mday = day;
     std::mktime(&t);
     return t.tm_wday;
 }
 
 // Convert digits
 std::string convertToDevanagari(int num) {
     std::string result, s = std::to_string(num);
     for (char c : s) result += devanagariNumbers.count(c) ? devanagariNumbers[c] : std::string(1, c);
     return result;
 }
 
 // Get month name
 std::string getMonthName(int month, bool unicode, bool isToad) {
     if (isToad) {
         return unicode ? englishMonthsDevnagari[month - 1] : englishMonths[month - 1];
     }
     return unicode ? nepaliMonths[month - 1] : romanizedNepaliMonths[month - 1];
 }
 
 std::string getMonthNameAbbr(int month, bool unicode, bool isToad) {
     if (isToad) {
         return englishMonthsAbbr[month - 1];
     }
     return unicode ? nepaliMonthsAbbr[month - 1] : romanizedNepaliMonthsAbbr[month - 1];
 }
 
 // Get weekday name
 std::string getWeekdayName(int dow, bool unicode, bool isToad) {
     if (!unicode) {
        return isToad ? englishWeekdays[dow] : romanizedNepaliWeekdays[dow];
     }
     return nepaliWeekdays[dow];
 }
 
 std::string getWeekdayNameAbbr(int dow, bool unicode, bool isToad) {
     if (!unicode) {
        return isToad ? englishWeekdaysAbbr[dow] : romanizedNepaliWeekdaysAbbr[dow];
     }
     return nepaliWeekdaysAbbr[dow];
 }
 
 // Print formatted date using simple specifiers (y,m,d,M,w,W)
 void displayFormattedDate(int y, int m, int d, const std::string& format, bool unicode, bool isToad) {
     std::string out;
     auto num = [unicode](int x) { return unicode ? convertToDevanagari(x) : std::to_string(x); };
 
     int dow;
     if (isToad) {
         dow = getWeekday(y, m, d);
     } else {
         Bikram bs;
         int gy, gm, gd;
         bs.toGregorian(y, m, d, gy, gm, gd);
         dow = getWeekday(gy, gm, gd);
     }
 
     for (size_t i = 0; i < format.length(); ++i) {
         switch (format[i]) {
             case 'y': out += num(y); break;
             case 'm': out += num(m); break;
             case 'd': out += num(d); break;
             case 'M': out += getMonthName(m, unicode, isToad); break;
             case 'w': out += getWeekdayName(dow, unicode, false); break; // NP
             case 'W': out += getWeekdayName(dow, unicode, true); break; // EN
             default: out += format[i];
         }
     }
     std::cout << out << std::endl;
 }
 
 // Print formatted date/time using strftime-style specifiers
 void displayStrfFormattedDateTime(int y, int m, int d, int h, int min, int s, const std::string& format, bool unicode, bool isToad) {
     std::string out;
     auto num = [unicode](int x) { return unicode ? convertToDevanagari(x) : std::to_string(x); };
     auto paddedNum = [unicode](int num_to_pad) {
         std::string s = std::to_string(num_to_pad);
         if (num_to_pad < 10) {
             s = "0" + s;
         }
         if (unicode) {
             std::string result;
             for (char c : s) {
                 result += devanagariNumbers.at(c);
             }
             return result;
         }
         return s;
     };
 
     int dow;
     if (isToad) {
         dow = getWeekday(y, m, d);
     } else {
         Bikram bs;
         int gy, gm, gd;
         bs.toGregorian(y, m, d, gy, gm, gd);
         dow = getWeekday(gy, gm, gd);
     }
 
     for (size_t i = 0; i < format.length(); ++i) {
         if (format[i] == '%' && i + 1 < format.length()) {
            i++; // consume '%'
            switch (format[i]) {
                case 'Y': out += num(y); break;
                case 'y': out += paddedNum(y % 100); break;
                case 'm': out += paddedNum(m); break;
                case 'B': out += getMonthName(m, unicode, isToad); break;
                case 'b': out += getMonthNameAbbr(m, unicode, isToad); break;
                case 'd': out += paddedNum(d); break;
                case 'A': out += getWeekdayName(dow, unicode, isToad); break;
                case 'a': out += getWeekdayNameAbbr(dow, unicode, isToad); break;
                case 'H': out += paddedNum(h); break;
                case 'I': out += paddedNum((h == 0 || h == 12) ? 12 : h % 12); break;
                case 'M': out += paddedNum(min); break;
                case 'S': out += paddedNum(s); break;
                case 'p':
                    if (unicode) {
                        out += (h < 12) ? "पूर्वाह्न" : "अपराह्न";
                    } else {
                        out += (h < 12) ? "AM" : "PM";
                    }
                    break;
                case 'c':
                    out += getWeekdayNameAbbr(dow, unicode, isToad) + " ";
                    out += getMonthNameAbbr(m, unicode, isToad) + " ";
                    out += paddedNum(d) + " ";
                    out += paddedNum(h) + ":" + paddedNum(min) + ":" + paddedNum(s) + " ";
                    out += num(y);
                    break;
                case 'x':
                    out += paddedNum(m) + "/" + paddedNum(d) + "/" + paddedNum(y % 100);
                    break;
                case 'X':
                    out += paddedNum(h) + ":" + paddedNum(min) + ":" + paddedNum(s);
                    break;
                case '%': out += '%'; break;
                default: out += '%' + std::string(1, format[i]); break;
            }
         } else {
             out += format[i];
         }
     }
     std::cout << out << std::endl;
 }
 
 // Shows a detailed summary of today's date. Called when no arguments are given.
 void showDefaultDateSummary() {
     int gy, gm, gd;
     getCurrentDate(gy, gm, gd);
 
     Bikram bs;
     bs.fromGregorian(gy, gm, gd);
 
     int dow = getWeekday(gy, gm, gd);
 
     std::cout << "\e[36m   Today's Date:\e[0m\n";
     std::cout << " \e[33m Gregorian: \e[0m"
               << "\e[35m" << gy << " " << englishMonths[gm - 1] << " " << gd << ", "
               << englishWeekdays[dow] << "\e[0m\n";
 
     std::cout << " \e[33m Bikram Sambat: \e[0m"
               << "\e[35m" << bs.getYear() << " " << nepaliMonths[bs.getMonth() - 1] << " " << bs.getDay() << ", "
               << nepaliWeekdays[dow] << "\e[0m\n";
 
     std::cout << " \e[33m Days in this Bikram month: \e[0m"
               << bs.daysInMonth(bs.getYear(), bs.getMonth()) << "\n";
 }
 
 // Shows today's date using the simple format.
 void showFormattedToday(const std::string& format, bool unicode, bool showAd) {
     int gy, gm, gd;
     getCurrentDate(gy, gm, gd);
 
     if (showAd) {
         displayFormattedDate(gy, gm, gd, format, unicode, true);
     } else {
         Bikram bs;
         bs.fromGregorian(gy, gm, gd);
         displayFormattedDate(bs.getYear(), bs.getMonth(), bs.getDay(), format, unicode, false);
     }
 }
 
 // Shows current date and time using strftime format.
 void showFormattedNow(const std::string& format, bool unicode, bool showAd) {
     int gy, gm, gd, h, min, s;
     getCurrentDateTime(gy, gm, gd, h, min, s);
 
     if (showAd) {
         displayStrfFormattedDateTime(gy, gm, gd, h, min, s, format, unicode, true);
     } else {
         Bikram bs;
         bs.fromGregorian(gy, gm, gd);
         displayStrfFormattedDateTime(bs.getYear(), bs.getMonth(), bs.getDay(), h, min, s, format, unicode, false);
     }
 }
 
 // Help message
 void showHelp() {
     std::cerr << "Usage: \n"
               << "  \e[31mShow today's date summary:\e[0m ./nepdate-cli\n"
               << "  \e[31mShow today's date (simple format):\e[0m ./nepdate-cli --today [--ad] [--unicode] [--format y-m-d]\n"
               << "  \e[31mShow current date & time (strftime):\e[0m ./nepdate-cli --now [--ad] [--unicode] [--format '%Y-%m-%d']\n"
               << "  \e[31mConvert to Bikram Sambat:\e[0m ./nepdate-cli --tobs yyyy mm dd [--unicode] [--format y-m-d]\n"
               << "  \e[31mConvert to Gregorian:\e[0m ./nepdate-cli --toad yyyy mm dd [--unicode] [--format y-m-d]\n\n"
               << "Options:\n"
               << "  \e[31m--ad:\e[0m      Show date in AD when used with --today or --now\n"
               << "  \e[31m--unicode:\e[0m Display Unicode (Devanagari) output\n"
               << "  \e[31m--format:\e[0m  Format string (see specifiers for each command).\n\n"
               << "Simple Format Specifiers (\e[33mfor --today, --tobs, --toad\e[0m):\n"
               << "  \e[31my:\e[0m Year \e[31mm:\e[0m Month \e[31md:\e[0m Day \e[31mM:\e[0m Month name \e[31mw:\e[0m Weekday(NP) \e[31mW:\e[0m Weekday(EN)\n\n"
               << "strftime Format Specifiers (\e[33mfor --now\e[0m):\n"
               << "  \e[31m%Y\e[0m: Year \e[31m%y\e[0m: Year(2-digit) \e[31m%m\e[0m: Month(01-12) \e[31m%d\e[0m: Day(01-31)\n"
               << "  \e[31m%B\e[0m: Full month  \e[31m%b\e[0m: Abbr month  \e[31m%A\e[0m: Full weekday \e[31m%a\e[0m: Abbr weekday\n"
               << "  \e[31m%H\e[0m: Hour(24h) \e[31m%I\e[0m: Hour(12h) \e[31m%M\e[0m: Minute \e[31m%S\e[0m: Second \e[31m%p\e[0m: AM/PM\n"
               << "  \e[31m%c\e[0m: Locale date & time \e[31m%x\e[0m: Locale date \e[31m%X\e[0m: Locale time \e[31m%%\e[0m: Literal '%'\n\n"
               << "Examples:\n"
               << "  \e[32m# Show today's date in BS (simple format)\e[0m\n"
               << "  $ \e[31m./nepdate-cli --today --unicode --format 'd M, y, w'\e[0m\n"
               << "  \e[35m> १४ भाद्रपद, २०८२, शनिबार\e[0m\n\n"
               << "  \e[32m# Show current time in AD using strftime format (%c)\e[0m\n"
               << "  $ \e[31m./nepdate-cli --now --ad --format '%c'\e[0m\n"
               << "  \e[35m> Sat Aug 30 11:26:30 2025\e[0m\n\n"
               << "  \e[32m# Show current date/time in BS (Devanagari) with full details\e[0m\n"
               << "  $ \e[31m./nepdate-cli --now --unicode --format '%A, %d %B %Y, %I:%M:%S %p'\e[0m\n"
               << "  \e[35m> शनिबार, १४ भाद्रपद २०८२, ११:२६:३० पूर्वाह्न\e[0m\n\n"
               << "  \e[32m# Convert a specific AD date to BS (simple format)\e[0m\n"
               << "  $ \e[31m./nepdate-cli --tobs 2025 8 30 --format 'y-M-d, W'\e[0m\n"
               << "  \e[35m> 2082-Bhadra-14, Saturday\e[0m\n\n"
               << "\e[35mFor more info: https://github.com/opensource-nepal/nepdate-cli\e[0m\n";
 }
 
 int main(int argc, char *argv[]) {
     if (argc == 1) {
         showDefaultDateSummary();
         showHelp();
         return 0;
     }
 
     std::vector<std::string> args(argv + 1, argv + argc);
     std::string command;
     bool unicode = false;
     std::string format;
     int y = 0, m = 0, d = 0;
     bool showAdDate = false;
 
     // Find command first to set default format
     for(const auto& arg : args) {
         if(arg == "--today" || arg == "--now" || arg == "--tobs" || arg == "--toad") {
             command = arg;
             break;
         }
     }
 
     if (command == "--now") {
         format = "%Y-%m-%d %H:%M:%S";
     } else {
         format = "y-m-d";
     }
 
     for (size_t i = 0; i < args.size(); ++i) {
         if (args[i] == "--today" || args[i] == "--now") {
             // Already handled
         } else if ((args[i] == "--tobs" || args[i] == "--toad") && i + 3 < args.size()) {
             try {
                 y = std::stoi(args[i + 1]);
                 m = std::stoi(args[i + 2]);
                 d = std::stoi(args[i + 3]);
                 i += 3; // Skip date parts
             } catch (const std::invalid_argument& ia) {
                 std::cerr << "Error: Invalid date arguments." << std::endl;
                 showHelp();
                 return 1;
             }
         } else if (args[i] == "--unicode") {
             unicode = true;
         } else if (args[i] == "--format" && i + 1 < args.size()) {
             format = args[++i];
         } else if (args[i] == "--ad") {
             showAdDate = true;
         }
     }
 
     if (command == "--today") {
         showFormattedToday(format, unicode, showAdDate);
     } else if (command == "--now") {
         showFormattedNow(format, unicode, showAdDate);
     } else if (command == "--tobs" && y != 0) {
         Bikram bs;
         bs.fromGregorian(y, m, d);
         displayFormattedDate(bs.getYear(), bs.getMonth(), bs.getDay(), format, unicode, false);
     } else if (command == "--toad" && y != 0) {
         Bikram bs;
         int gy, gm, gd;
         bs.toGregorian(y, m, d, gy, gm, gd);
         displayFormattedDate(gy, gm, gd, format, unicode, true);
     } else {
         showHelp();
         return 1;
     }
 
     return 0;
 }

