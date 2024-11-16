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

std::map<char, std::string> devanagariNumbers = {
    {'0', "०"}, {'1', "१"}, {'2', "२"}, {'3', "३"}, {'4', "४"},
    {'5', "५"}, {'6', "६"}, {'7', "७"}, {'8', "८"}, {'9', "९"}
};

std::vector<std::string> englishMonths = {
    "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"
};

std::vector<std::string> englishMonthsDevnagari = {
    "जनवरी",   // January
    "फेब्रुअरी", // February
    "मार्च",    // March
    "अप्रिल",   // April
    "मे",       // May
    "जुन",      // June
    "जुलाई",    // July
    "अगस्ट",    // August
    "सेप्टेम्बर", // September
    "अक्टोबर",  // October
    "नोभेम्बर",  // November
    "डिसेम्बर"   // December
};

std::vector<std::string> romanizedNepaliMonths = {
    "Baisakh", "Jestha", "Ashadh", "Shrawan", "Bhadra", "Ashwin", "Kartik", "Mangsir", "Poush", "Magh", "Falgun", "Chaitra"
};

std::vector<std::string> nepaliMonths = {
    "बैशाख", "जेष्ठ", "आषाढ", "श्रावण", "भाद्रपद", "आश्विन", "कार्तिक", "मङ्सिर", "पौष", "माघ", "फाल्गुन", "चैत्र"
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

void getCurrentDate(int &year, int &month, int &day) {
    // Get the current time
    time_t t = time(0);  // Current time in seconds since the Unix epoch
    struct tm * now = localtime(&t);  // Get local time

    // Extract the year, month, and day from the tm struct
    year = now->tm_year + 1900;  // tm_year is years since 1900
    month = now->tm_mon + 1;     // tm_mon is 0-indexed (0 = January, 11 = December)
    day = now->tm_mday;          // tm_mday is the day of the month
}

// Convert numbers to Devanagari script
std::string convertToDevanagari(int num) {
    std::string result = "";
    std::string numStr = std::to_string(num);  // Convert the number to a string

    for (char c : numStr) {
        if (devanagariNumbers.find(c) != devanagariNumbers.end()) {
            result += devanagariNumbers[c];  // Append the Devanagari digit
        } else {
            result += c;  // In case it's not a digit, just append the character
        }
    }

    return result;
}

// Get month name based on --unicode and command context
std::string getMonthName(int month, bool unicode, bool isToad) {
    if (unicode && isToad) {
        return englishMonthsDevnagari[month - 1];  // Use Devanagari for English months if both flags are true
    } 
    if (isToad) {
        return englishMonths[month - 1];  // Use English months for --toad
    } 
    if (unicode) {
        return nepaliMonths[month - 1];  // Use Nepali months if unicode is true
    } 
    return romanizedNepaliMonths[month - 1];  // Use romanized Nepali months otherwise
}

// Get weekday name based on --unicode
std::string getWeekdayName(int dayOfWeek, bool unicode, bool isToad) {
    if (unicode && isToad) {
        return nepaliWeekdays[dayOfWeek];
    } if (isToad) {
        return englishWeekdays[dayOfWeek];  // Use English months for --toad
    }
     if (unicode) {
        return nepaliWeekdays[dayOfWeek];
    } else {
        return romanizedNepaliWeekdays[dayOfWeek];
    }
}

// Get English month name
std::string getEnglishMonthName(int month) {
    return englishMonths[month - 1];
}

// Get English weekday name
std::string getEnglishWeekdayName(int dayOfWeek) {
    return englishWeekdays[dayOfWeek];
}

void displayFormattedDate(int year, int month, int day, const std::string& format, bool unicode, bool isToad) {
    std::string result;
    result.reserve(format.length() * 2);  // Reserve space to avoid frequent reallocations

    // Helper lambda to conditionally convert numbers
    auto maybeConvertToDevanagari = [unicode](int num) {
        return unicode ? convertToDevanagari(num) : std::to_string(num);
    };

    for (size_t i = 0; i < format.length(); i++) {
        if (format[i] == 'y') {
            result += maybeConvertToDevanagari(year);
        } else if (format[i] == 'm') {
            result += maybeConvertToDevanagari(month);
        } else if (format[i] == 'd') {
            result += maybeConvertToDevanagari(day);
        } else if (format[i] == 'M') {
            result += getMonthName(month, unicode, isToad);  // Pass isToad here
        } else if (format[i] == 'w') {
            result += getWeekdayName((day + 6) % 7, unicode, isToad);  // Sunday is 0 in Gregorian
        } else {
            result += format[i];
        }
    }

    std::cout << result << std::endl;
}

void showTodaysDate(bool unicode, const std::string& format) {
    int year, month, day;
    getCurrentDate(year, month, day);  // Get today's date

    // Convert today's date to Bikram Sambat
    bikram bsdate;
    bsdate.fromGregorian(year, month, day);

    // After conversion, get the Bikram Sambat year, month, and day
    year = bsdate.getYear();
    month = bsdate.getMonth();
    day = bsdate.getDay();

    displayFormattedDate(year, month, day, format, unicode, false);  // Assume today is in AD (Gregorian)
}

int main(int argc, char *argv[]) {
    // Check for no arguments
    if (argc == 1) {
        int year, month, day;
        getCurrentDate(year, month, day);
        
        bikram bsdate;
        bsdate.fromGregorian(year, month, day);
        std::string bs_weekday_name = bsdate.getWeekdayName(year, month, day);

        std::cout << "\e[36m   Today's Date:\e[0m" << std::endl;
        std::cout << " \e[33m Gregorian: \e[0m"
                  << "\e[35m" << year << " " << month << " " << day << " " 
                  << bsdate.getWeekdayName(year, month, day) << " " << "\e[0m" << std::endl;
        std::cout << " \e[33m Bikram Sambat: \e[0m"
                  << "\e[35m" << bsdate.getYear() << " " << bsdate.getMonth() << " " 
                  << bsdate.getDay() << " " << bs_weekday_name << " " 
                  << " \e[33m days in bikram month: \e[0m" 
                  << bsdate.daysInMonth(bsdate.getYear(), bsdate.getMonth()) 
                  << "\e[0m" << std::endl;

        std::cerr << "Usage: \n"
                  << "  \e[31mShow today's date: ./nepdate-cli --today [--unicode] [--format format_string]\n\e[0m"
                  << "  \e[31mConvert to Bikram Sambat Date: ./nepdate-cli --tobs year month day [--unicode] [--format format_string]\n\e[0m"
                  << "  \e[31mConvert to Gregorian Date: ./nepdate-cli --toad year month day [--unicode] [--format format_string]\n\e[0m"
                  << "Options:\n"
                  << "  \e[31m--unicode : Display the date in Unicode format (Devanagari script).\e[0m\n"
                  << "  \e[31m--format format_string : Specify a custom format for the date (e.g., 'y-m-d', 'd-M-y'). \e[0mDefault: 'y-m-d'\n"
                  << "\nFormat Specifiers:\n"
                  << "  \e[31my : Year\n"
                  << "  \e[31mm : Month (numeric)\n"
                  << "  \e[31md : Day\n"
                  << "  \e[31mw : Weekday name\n"
                  << "  \e[31mM : Month name\n\e[0m"
                  << "\nExample commands:\n"
                  << "  \e[31m./nepdate-cli --today --unicode --format 'd-M-y'        : Show today's date in Unicode with custom format.\n"
                  << "  ./nepdate-cli --tobs 2024 11 15 --unicode --format 'y-m-d' : Convert a Gregorian date to Bikram Sambat date.\n"
                  << "  ./nepdate-cli --toad 2081 8 30 --unicode --format 'y/m/d'  : Convert a Nepali date to Gregorian date.\n\e[0m"
                  << "\e[35mFor more information, visit: https://github.com/opensource-nepal/nepdate-cli\n\e[0m";

        return 0;
    }

    bool unicode = false;
    std::string command = argv[1];
    std::string format = "y-m-d"; // Default format

    // Parse the arguments
    for (int i = 2; i < argc; ++i) {
        if (std::string(argv[i]) == "--unicode") {
            unicode = true;
        } else if (std::string(argv[i]) == "--format" && i + 1 < argc) {
            format = argv[i + 1];
            ++i; // Skip the next argument as it is the format string
        } else if (command == "--today" && std::string(argv[i]) != "--unicode") {
            format = argv[i];
        }
    }

    // Handle the --today command
    if (command == "--today") {
        showTodaysDate(unicode, format); // Pass the format argument here
        return 0;
    }

    // Handle the conversion commands (at least 5 arguments, up to 7 arguments)
    if ((command == "--toad" || command == "--tobs") && argc >= 5) {
        int year = std::stoi(argv[2]);
        int month = std::stoi(argv[3]);
        int day = std::stoi(argv[4]);

        // Optionally handle --unicode and --format in the command
        for (int i = 5; i < argc; ++i) {
            if (std::string(argv[i]) == "--unicode") {
                unicode = true;
            } else if (std::string(argv[i]) == "--format" && i + 1 < argc) {
                format = argv[i + 1];
                ++i; // Skip the next argument as it is the format string
            }
        }

        // Convert to Bikram Sambat Date
        bikram bsdate;

        if (command == "--tobs") {
            bsdate.fromGregorian(year, month, day);
            //displayFormattedDate(year, month, day, format, unicode, false);
        } else if (command == "--toad") {
            bsdate.fromNepali(year, month, day);
            //displayFormattedDate(year, month, day, format, unicode, true);
        } else {
            std::cerr << "Invalid command or insufficient arguments.\n";
            return 1; // Exit with an error code
        }

        // Get the converted date values
        year = bsdate.getYear();
        month = bsdate.getMonth();
        day = bsdate.getDay();

        // Display the converted date again based on the unicode flag
        displayFormattedDate(year, month, day, format, unicode, command == "--toad");

        return 0; 
    }

    return 1; // Default return if no valid command is found
}
