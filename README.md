
## nepdate-cli: Bikram Sambat Date Converter

`nepdate-cli` is a command-line tool for displaying and converting dates between the Bikram Sambat (Vikram Samvat) and Gregorian calendars. It's a simple utility designed for easy interaction with these two calendar systems, featuring extensive formatting options.

> [!NOTE]
> 
> A Rust port is available on the `rust` branch of this repository. If you prefer to install a binary using Cargo, you can run:
> 
> ```
> cargo install nepdate-cli
> 
> ```
> 
> Or, add it as a dependency in your `Cargo.toml` file: `nepdate-cli = "0.1.3"`. For more details, see the [Rust README](https://github.com/opensource-nepal/nepdate-cli/blob/rust/README.md "null").

### Features

-   Display a summary of the current date in both Bikram Sambat and Gregorian calendars.
    
-   Convert dates between Bikram Sambat and Gregorian.
    
-   Display the current date or date/time with custom formatting.
    
-   Supports both simple format specifiers and a wide range of `strftime`-style specifiers.
    
-   Output in Unicode (Devanagari script) or Romanized text.
    
-   Supports a very long date range using astronomical calculation.(there is precomputed data for 2000-2099)
    

### Installation

There are two installation methods available: using a Debian package or compiling from source.

#### From Debian Package

1.  **Download the latest `.deb` file** from the [releases](https://github.com/opensource-nepal/nepdate-cli/releases "null") page.
    
2.  **Install the package** using `dpkg`:
    
    ```
    sudo dpkg -i nepdate-cli_1.0.0_amd64.deb
    
    ```
    
    Replace `nepdate-cli_1.0.0_amd64.deb` with the filename of the downloaded package.
    

#### From Source

1.  Clone the repository:
    
    ```
    git clone [https://github.com/opensource-nepal/nepdate-cli.git](https://github.com/opensource-nepal/nepdate-cli.git)
    cd nepdate-cli
    
    ```
    
2.  Install dependencies:
    
    ```
    sudo apt-get update
    sudo apt-get install -y cmake build-essential debhelper devscripts
    
    ```
    
    _The `debhelper` and `devscripts` packages are for building the Debian installer package._
    
3.  Build and install:
    
    ```
    mkdir build
    cd build
    cmake ..
    make
    sudo make install
    
    ```
    
    _To build a Debian package, run `dpkg-buildpackage -b -us -uc` from the project root directory. This command builds the package without signing._
    

### Usage

Once installed, use `nepdate-cli` from the command line.

Running the command with no arguments displays a detailed summary of the current date:

```
nepdate-cli

```

Output:

```
   Today's Date:
    Gregorian: 2025 August 30, Saturday
    Bikram Sambat: 2082 Bhadra 14, शनिबार
    Days in this Bikram month: 31

```

For specific conversions and formatted outputs, use the following commands and options:

```
Usage: 
  Show today's date summary: ./nepdate-cli
  Show today's date (simple format): ./nepdate-cli --today [--ad] [--unicode] [--format y-m-d]
  Show current date & time (strftime): ./nepdate-cli --now [--ad] [--unicode] [--format '%Y-%m-%d']
  Convert to Bikram Sambat: ./nepdate-cli --tobs yyyy mm dd [--unicode] [--format y-m-d]
  Convert to Gregorian: ./nepdate-cli --toad yyyy mm dd [--unicode] [--format y-m-d]

Options:
  --ad:      Show date in AD when used with --today or --now
  --unicode: Display Unicode (Devanagari) output
  --format:  Format string (see specifiers for each command).


```

### Format Specifiers

#### Simple Format Specifiers (`--today`, `--tobs`, `--toad`)

Specifier

Description

`y`

Year

`m`

Month (numeric)

`d`

Day

`M`

Full month name

`w`

Weekday name (Nepali)

`W`

Weekday name (English)

#### `strftime` Format Specifiers (`--now`)

Specifier

Description

Specifier

Description

`%Y`

Year (e.g., 2082)

`%H`

Hour, 24-hour (00-23)

`%y`

Year, 2-digit (e.g., 82)

`%I`

Hour, 12-hour (01-12)

`%m`

Month as a number (01-12)

`%M`

Minute (00-59)

`%d`

Day of the month (01-31)

`%S`

Second (00-59)

`%B`

Full month name

`%p`

AM or PM

`%b`

Abbreviated month name

`%c`

Locale’s appropriate date and time

`%A`

Full weekday name

`%x`

Locale’s appropriate date

`%a`

Abbreviated weekday name

`%X`

Locale’s appropriate time

`%%`

A literal `%` character

  

  

### Examples

_(Note: Terminal output colors are represented here by formatting.)_

1.  **Show today's date in BS using simple format**
    
    ```
    # Show today's date in BS (simple format)
    $ ./nepdate-cli --today --unicode --format 'd M, y, w'
    > १४ भाद्रपद, २०८२, शनिबार
    
    ```
    
2.  **Show current date and time in AD using `strftime`**
    
    ```
    # Show current time in AD using strftime format (%c)
    $ ./nepdate-cli --now --ad --format '%c'
    > Sat Aug 30 11:34:15 2025
    
    ```
    
3.  **Show current date and time in BS (Devanagari) with full details**
    
    ```
    # Show current date/time in BS (Devanagari) with full details
    $ ./nepdate-cli --now --unicode --format '%A, %d %B %Y, %I:%M:%S %p'
    > शनिबार, १४ भाद्रपद २०८२, ११:३४:१५ पूर्वाह्न
    
    ```
    
4.  **Convert a specific AD date to BS**
    
    ```
    # Convert a specific AD date to BS (simple format)
    $ ./nepdate-cli --tobs 2025 8 30 --format 'y-M-d, W'
    > 2082-Bhadra-14, Saturday
    
    ```
    

### Contributing

Contributions are welcome! If you have any bug reports or feature requests, please open an issue on the GitHub [repository](https://github.com/opensource-nepal/nepdate-cli "null").

To contribute code:

1.  Fork the repository.
    
2.  Create a new branch for your changes.
    
3.  Commit your changes and push them to your fork.
    
4.  Open a pull request against the `main` branch of the original repository.
    

### License

nepdate-cli is released under the [GNU General Public License v3.0](https://www.gnu.org/licenses/gpl-3.0.en.html "null"). See the `LICENSE` file for more details.

### Contact

For any inquiries, you can reach out to [khumnath cg](https://khumnath.com.np "null").