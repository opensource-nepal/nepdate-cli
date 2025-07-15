use std::env;
use std::process;
use chrono::{Datelike, Local, NaiveDate};

mod bikram;
use bikram::Bikram;

fn main() {
    let args: Vec<String> = env::args().collect();

    // Check for correct number of arguments and command flags
    if args.len() != 6 || args[1] != "--conv" || (args[2] != "--tobs" && args[2] != "--toad") {
        // Print usage instructions
        eprintln!(
            "Usage: {}\n\x1b[31m Convert to Nepali Date: --conv --tobs year month day\n Convert to Gregorian Date: --conv --toad year month day\x1b[0m",
            args[0]
        );

        // Display today's date as an example
        let now_date = Local::now();
        let g_year_today = now_date.year();
        let g_month_today = now_date.month();
        let g_day_today = now_date.day();
        // Get Gregorian weekday directly from chrono for today's date
        let g_weekday_name_today = now_date.format("%A").to_string();

        let mut bsdate_today = Bikram::new();
        // Convert today's Gregorian date to Bikram Sambat
        bsdate_today.from_gregorian(g_year_today, g_month_today as i32, g_day_today as i32);

        // For today's date, use the Gregorian weekday for both outputs
        let bs_weekday_name_today = g_weekday_name_today.clone();

        println!("\x1b[36m   Today's Date:\x1b[0m");
        println!(
            " \x1b[33m Gregorian: \x1b[0m \x1b[35m{} {} {} {} \x1b[0m",
            g_year_today, g_month_today, g_day_today, g_weekday_name_today
        );
        println!(
            " \x1b[33m Bikram Sambat: \x1b[0m \x1b[35m{} {} {} {} \x1b[33m days in bikram month: \x1b[0m{} \x1b[0m",
            bsdate_today.get_year(),
            bsdate_today.get_month(),
            bsdate_today.get_day(),
            bs_weekday_name_today,
            bsdate_today.days_in_month(bsdate_today.get_year(), bsdate_today.get_month())
        );
        process::exit(1);
    }

    let conv_type = &args[2];
    // Parse input date components
    let year = args[3].parse::<i32>().expect("Year must be an integer.");
    let month = args[4].parse::<i32>().expect("Month must be an integer.");
    let day = args[5].parse::<i32>().expect("Day must be an integer.");

    let mut bsdate = Bikram::new(); // Create a new Bikram instance for the conversion

    if conv_type == "--tobs" {
        // Get weekday of the *input Gregorian date*
        let input_gregorian_weekday = if let Some(date) = NaiveDate::from_ymd_opt(year, month as u32, day as u32) {
            date.format("%A").to_string()
        } else {
            "Invalid Gregorian input date".to_string()
        };

        // Convert Gregorian to Bikram Sambat
        bsdate.from_gregorian(year, month, day);

        // Use the Gregorian input weekday for the Bikram Sambat output
        let bs_weekday_name = input_gregorian_weekday.clone();

        println!(
            " \x1b[33m Gregorian Input: \x1b[0m \x1b[35m{} {} {} {} \x1b[0m",
            year, month, day, input_gregorian_weekday
        );
        println!(
            " \x1b[33m Bikram Sambat Date: \x1b[0m \x1b[35m{} {} {} {} \x1b[0m \x1b[33m days in bikram month: \x1b[0m{} \x1b[0m",
            bsdate.get_year(),
            bsdate.get_month(),
            bsdate.get_day(),
            bs_weekday_name,
            bsdate.days_in_month(bsdate.get_year(), bsdate.get_month())
        );
    } else if conv_type == "--toad" {
        // Convert Bikram Sambat to Gregorian
        // The to_gregorian method returns the Gregorian date components
        let (converted_g_year, converted_g_month, converted_g_day) =
            bsdate.to_gregorian(year, month, day);

        // Get the weekday name for the *converted Gregorian date* using chrono
        let gregorian_weekday_name = if let Some(date) = NaiveDate::from_ymd_opt(
            converted_g_year,
            converted_g_month as u32,
            converted_g_day as u32,
        ) {
            date.format("%A").to_string()
        } else {
            "Invalid Gregorian date".to_string()
        };

        println!(
            "\x1b[33m Gregorian Date: \x1b[0m \x1b[35m{} {} {} {} \x1b[0m",
            converted_g_year, converted_g_month, converted_g_day, gregorian_weekday_name
        );
    }
}
