# Numeric Vigenère Cipher (GTK Application)

A cross‑platform GTK-based desktop application implementing a **numeric Vigenère cipher**. This project provides an easy-to-use graphical interface for encrypting and decrypting text using a digit-based key.

This application is written in **pure C** and uses **GTK 4** for its interface. It is designed to be lightweight, educational, and portable across Linux, macOS, and Windows.

## Features

- GUI-based cipher tool using GTK 4
- Numeric Vigenère cipher (digits 0–9 determine character shifts)
- Real-time encryption and decryption
- Editable message and key input areas
- Read-only output area
- Fully cross-platform (Linux, macOS, Windows)
- Automated builds via GitHub Actions

## About the Cipher

This implementation uses digits (0–9) to define the shifts in the alphabet. For example, key **"1234"** applies shifts of +1, +2, +3, +4 repeatedly across the message.

### Encryption Logic

- Only letters A–Z and a–z are shifted
- Non-alphabetic characters remain unchanged
- Case is preserved

### Educational Disclaimer

**This is _not_ a secure encryption method and should not be used for protecting sensitive data.**
It is purely an educational demonstration.

## Building from Source

This project uses GTK 4 and standard CMake.

### Linux (Debian/Ubuntu)

```
sudo apt install build-essential cmake libgtk-4-dev
mkdir build && cd build
cmake ..
make
```

### Fedora / Red Hat

```
sudo dnf install gcc cmake gtk4-devel
mkdir build && cd build
cmake ..
make
```

### macOS (Homebrew)

```
brew install gtk4 cmake
mkdir build && cd build
cmake ..
make
```

### Windows (MSYS2)

Install MSYS2, then:

```
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-gtk4 cmake
cmake -G "MinGW Makefiles" -B build
cmake --build build
```

## Automated Cross‑Platform Builds

This repository includes a GitHub Actions workflow that compiles binaries for:

- Linux (x86_64 + ARM64)

Resulting artifacts are published automatically with each release.

## Running the Application

After building:

```
./cipher
```

(Or the platform-specific binary produced.)

When launched, the window will provide three text panes:

1. **Message Input**
2. **Numeric Key Input**
3. **Output** (read-only)

Two buttons perform encryption and decryption.

## License

Licensed under the **MIT License**. See `LICENSE` for details.

---
