## nepdate-cli: Bikram Sambat Date Converter

nepdate-cli is a command-line tool for displaying and converting dates between the Bikram Sambat (Vikram Samvat) and Gregorian calendars. It's a simple utility designed for easy interaction with these two calendar systems.

> [!NOTE]  
> Rust port is available at rust branch of this repository. if you want to install just binary using cargo use
> ``` cargo install nepdate-cli ```   or use as dependency on Cargo.toml file.  ``` nepdate-cli = "0.1.3" ```
> check https://github.com/opensource-nepal/nepdate-cli/blob/rust/src/bikram.rs for available functions or https://github.com/opensource-nepal/nepdate-cli/blob/rust/src/main.rs for example uses.
> read readme file for rust https://github.com/opensource-nepal/nepdate-cli/blob/rust/README.md

### Features

-   Display the current Bikram Sambat date.
-   Convert dates between Bikram Sambat and Gregorian calendars.
-   Supports date formatting with devnagari script and date format  specifiers.
-   Supports very long date range.

### Installation

There are two installation methods available: using a Debian package or compiling from source.

#### From Debian Package

1.  **Download the latest `.deb` file** from the [releases](https://github.com/opensource-nepal/nepdate-cli/releases) page.
2.  **Install the package** using `dpkg`:

    ```bash
    sudo dpkg -i nepdate-cli_1.0.0_amd64.deb
    ```

    Replace `nepdate-cli_1.0.0_amd64.deb` with the filename of the downloaded package.


#### From Source

1.  Clone the repository:

    ```bash
    git clone https://github.com/opensource-nepal/nepdate-cli.git
    cd nepdate-cli
    ```

2.  Install dependencies:

    ```bash
    sudo apt-get update
    sudo apt-get install -y cmake build-essential debhelper devscripts
    ```

    *packages debhelper and devscripts are for building debian installer package.*

3.  Build and install:

    ```bash
    mkdir build
    cd build
    cmake ..
    make
    sudo make install
    ```

    *if need to build deb package with signing, run `dpkg-buildpackage -b` from project root directory. (you have to edit email address to yours in files in /debian folder.)*
    *`dpkg-buildpackage -b -us -uc` command builds debian package without signing.*

### Usage

Once installed, you can use nepdate-cli from the command line. Here are some basic commands:

```bash
nepdate-cli
```

Output:
```
   Today's Date:
    Gregorian: 2024 11 15 Friday
    Bikram Sambat: 2081 8 30 शुक्रवार  days in bikram month: 30
```

```
Usage:
  Show today's date: ./ndate --today [--unicode] [--format format_string]
  Convert to Bikram Sambat Date: ./ndate --tobs year month day [--unicode] [--format format_string]
  Convert to Gregorian Date: ./ndate --toad year month day [--unicode] [--format format_string]
Options:
  --unicode : Display the date in Unicode format (Devanagari script).
  --format format_string : Specify a custom format for the date (e.g., 'y-m-d', 'd-M-y'). Default: 'y-m-d'

Format Specifiers:
  y : Year
  m : Month (numeric)
  d : Day
  w : Weekday name
  M : Month name

Example commands:
  ./ndate --today --unicode --format 'd-M-y'        : Show today's date in Unicode with custom format.
  ./ndate --tobs 2024 11 15 --unicode --format 'y-m-d' : Convert a Gregorian date to Bikram Sambat date.
  ./ndate --toad 2081 8 30 --unicode --format 'y/m/d'  : Convert a Nepali date to Gregorian date.
```

### Examples:

1. Show today's date in Devanagari script with default format:
    ```bash
    ./ndate --today --unicode
    ```
    Output: २०८१-८-३०

2. Convert a Gregorian date to Bikram Sambat date in Devanagari script:
    ```bash
    ./ndate --tobs 2024 11 15 --unicode
    ```
    Output: २०८१-८-३०

3. Show today's date with custom format 'd-M-y':
    ```bash
    ./ndate --today --format 'd-M-y'
    ```
    Output: ३०-श्रावण-२०८१

4. Convert a Bikram Sambat date to Gregorian date with weekday name:
    ```bash
    ./ndate --toad 2081 8 30 --format 'w, y-m-d' --unicode
    ```
    Output: शुक्रवार, २०८१-८-३०


### Contributing

Contributions are welcome! If you have any bug reports or feature requests, please open an issue on the GitHub [repository](https://github.com/opensource-nepal/nepdate-cli).

Here's a quick guide to contributing code:

1.  Fork the repository.
2.  Create a new branch for your changes.
3.  Commit your changes and push them to your fork.
4.  Open a pull request against the main branch of the original repository.

### License

nepdate-cli is released under the [GNU General Public License v3.0](https://www.gnu.org/licenses/gpl-3.0.en.html). See the LICENSE file for more details.

### Contact

For any inquiries, you can reach out to [khumnath cg](https://khumnath.com.np) .
