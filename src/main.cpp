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
 
 std::vector<std::string> englishMonthsDevnagari = {
     "जनवरी", "फेब्रुअरी", "मार्च", "अप्रिल", "मे", "जुन",
     "जुलाई", "अगस्ट", "सेप्टेम्बर", "अक्टोबर", "नोभेम्बर", "डिसेम्बर"
 };
 
 std::vector<std::string> romanizedNepaliMonths = {
     "Baisakh", "Jestha", "Ashadh", "Shrawan", "Bhadra", "Ashwin",
     "Kartik", "Mangsir", "Poush", "Magh", "Falgun", "Chaitra"
 };
 
 std::vector<std::string> nepaliMonths = {
     "बैशाख", "जेष्ठ", "आषाढ", "श्रावण", "भाद्रपद", "आश्विन",
     "कार्तिक", "मङ्सिर", "पौष", "माघ", "फाल्गुन", "चैत्र"
 };
 
 std::vector<std::string> englishWeekdays = {
     "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
 };
 
 std::vector<std::string> romanizedNepaliWeekdays = {
     "Ravivar", "Somvar", "Mangalvar", "Budhvar", "Brihaspativar", "Shukravar", "Shanivar"
 };
 
 std::vector<std::string> nepaliWeekdays = {
     "आइतबार", "सोमबार", "मङ्गलबार", "बुधबार", "बिहीबार", "शुक्रबार", "शनिबार"
 };
 
 // Get current date
 void getCurrentDate(int &year, int &month, int &day) {
     time_t t = time(0);
     struct tm * now = localtime(&t);
     year = now->tm_year + 1900;
     month = now->tm_mon + 1;
     day = now->tm_mday;
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
     if (unicode && isToad) return englishMonthsDevnagari[month - 1];
     if (isToad) return englishMonths[month - 1];
     if (unicode) return nepaliMonths[month - 1];
     return romanizedNepaliMonths[month - 1];
 }
 
 // Get weekday name
 std::string getWeekdayName(int dow, bool unicode, bool isToad) {
     if (unicode && isToad) return nepaliWeekdays[dow];
     if (isToad) return englishWeekdays[dow];
     if (unicode) return nepaliWeekdays[dow];
     return romanizedNepaliWeekdays[dow];
 }
 
 // Print formatted
 void displayFormattedDate(int y, int m, int d, const std::string& format, bool unicode, bool isToad) {
     std::string out;
     auto num = [unicode](int x) { return unicode ? convertToDevanagari(x) : std::to_string(x); };
 
     for (size_t i = 0; i < format.length(); ++i) {
         switch (format[i]) {
             case 'y': out += num(y); break;
             case 'm': out += num(m); break;
             case 'd': out += num(d); break;
             case 'M': out += getMonthName(m, unicode, isToad); break;
             case 'w': out += getWeekdayName(getWeekday(y, m, d), unicode, isToad); break;
             default: out += format[i];
         }
     }
 
     std::cout << out << std::endl;
 }
 
 // Show today's date
 void showTodaysDate(bool unicode, const std::string& format) {
     int gy, gm, gd;
     getCurrentDate(gy, gm, gd);
 
     Bikram bs;
     bs.fromGregorian(gy, gm, gd);
 
     std::cout << "\e[36m   Today's Date:\e[0m\n";
     std::cout << " \e[33m Gregorian: \e[0m"
               << "\e[35m" << gy << " " << gm << " " << gd << " "
               << getWeekdayName(getWeekday(gy, gm, gd), unicode, true) << "\e[0m\n";
 
     std::cout << " \e[33m Bikram Sambat: \e[0m"
               << "\e[35m" << bs.getYear() << " " << bs.getMonth() << " " << bs.getDay() << " "
               << getWeekdayName(getWeekday(gy, gm, gd), unicode, false) << "\e[0m\n";
 
     std::cout << " \e[33m days in bikram month: \e[0m"
               << bs.daysInMonth(bs.getYear(), bs.getMonth()) << "\n";
 }
 
 // Help message
 void showHelp() {
     std::cerr << "Usage: \n"
               << "  \e[31mShow today's date:\e[0m ./nepdate-cli --today [--unicode] [--format format_string]\n"
               << "  \e[31mConvert to Bikram Sambat:\e[0m ./nepdate-cli --tobs yyyy mm dd [--unicode] [--format format_string]\n"
               << "  \e[31mConvert to Gregorian:\e[0m ./nepdate-cli --toad yyyy mm dd [--unicode] [--format format_string]\n\n"
               << "Options:\n"
               << "  \e[31m--unicode:\e[0m Display Unicode (Devanagari) output\n"
               << "  \e[31m--format:\e[0m  Format string like 'y-m-d', 'd-M-y', etc. Default: y-m-d\n\n"
               << "Format Specifiers:\n"
               << "  \e[31my:\e[0m Year  \e[31mm:\e[0m Month number  \e[31md:\e[0m Day  \e[31mM:\e[0m Month name  \e[31mw:\e[0m Weekday\n\n"
               << "Examples:\n"
               << "  \e[31m./nepdate-cli --today --unicode --format 'd-M-y'\n"
               << "  ./nepdate-cli --tobs 2024 11 15 --unicode --format 'y-m-d'\n"
               << "  ./nepdate-cli --toad 2081 8 30 --unicode --format 'y/m/d'\e[0m\n\n"
               << "\e[35mFor more info: https://github.com/opensource-nepal/nepdate-cli\e[0m\n";
 }
 
 int main(int argc, char *argv[]) {
     if (argc == 1) {
         showTodaysDate(false, "y-m-d");
         showHelp();
         return 0;
     }
 
     std::string command = argv[1];
     bool unicode = false;
     std::string format = "y-m-d";
 
     // Parse flags
     for (int i = 2; i < argc; ++i) {
         std::string arg = argv[i];
         if (arg == "--unicode") unicode = true;
         else if (arg == "--format" && i + 1 < argc) {
             format = argv[++i];
         }
     }
 
     if (command == "--today") {
         showTodaysDate(unicode, format);
         return 0;
     }
 
     if ((command == "--tobs" || command == "--toad") && argc >= 5) {
         int y = std::stoi(argv[2]);
         int m = std::stoi(argv[3]);
         int d = std::stoi(argv[4]);
         Bikram bs;
 
         if (command == "--tobs") {
             bs.fromGregorian(y, m, d);
             displayFormattedDate(bs.getYear(), bs.getMonth(), bs.getDay(), format, unicode, false);
         } else {
             int gy, gm, gd;
             bs.toGregorian(y, m, d, gy, gm, gd);
             displayFormattedDate(gy, gm, gd, format, unicode, true);
         }
         return 0;
     }
 
     showHelp();
     return 1;
 }
 