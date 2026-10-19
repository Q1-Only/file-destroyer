# destroyer

A lightweight Windows command-line tool that corrupts files by randomly flipping bits based on a specified probability.

## Usage

```cmd
destroyer.exe -i <input_file> -o <output_file> -s <strength>
```

- `-i`: Path to the input file (read-only).
- `-o`: Path to the output file (will be overwritten).
- `-s`: Flip probability per bit (range `[0, 1]`). For example, `0.0001` means 1 in 10,000 bits will be flipped on average.

**Example:**
```cmd
destroyer.exe -i original.zip -o corrupted.zip -s 0.0001
```

## Build

Requires C++11 or higher. Compile with GCC/MinGW on Windows:

```cmd
g++ -std=c++17 -O2 main.cpp -o destroyer.exe -municode
```

## Output

- Success: `Success`
- Failure: `Fail <ERROR_CODE>`

**Error Codes:**
- `BADARGS`: Missing/invalid arguments, or input and output paths are identical.
- `NOINPUT`: Cannot open the input file.
- `NOOUTPUT`: Cannot create the output file.
- `IOFAIL`: Read/write error during processing.

## Warning

This tool performs irreversible random bit flips. **Always operate on file copies**, as the output file will likely become unreadable or corrupted.