# SecureX Tools

SecureX Tools is a collection of utilities designed to enhance digital security and data management. This suite includes a Base64 Encoder/Decoder, an Encryptor, an EXIF Data Extractor, and a URL Shortener. Each tool is crafted to provide essential functionalities in a user-friendly manner.

## Table of Contents

- [SecureX Tools](#securex-tools)
  - [Table of Contents](#table-of-contents)
  - [Overview](#overview)
  - [Prerequisites](#prerequisites)
  - [Projects](#projects)
    - [Encryptor](#encryptor)
    - [Base64 Generator](#base64-generator)
    - [EXIF Data Extractor](#exif-data-extractor)
  - [To Run](#to-run)
    - [URL Shortener](#url-shortener)
  - [Getting Started](#getting-started)
  - [Installation Process](#installation-process)
  - [Run](#run)
  - [Contributors](#contributors)

## Overview

SecureX Tools offers a comprehensive set of utilities for various digital security and data management tasks:

- **Base64Generator**: Encode or decode data in Base64 format.
- **Encryptor**: Securely encrypt and decrypt messages.
- **EXIFDataExtractor**: Extract metadata from digital photos.
- **URLShortener**: Create shorter aliases for long URLs.

## Prerequisites

Before installing SecureX Tools, ensure you have the following:

- A modern C++ compiler 
- libcurl,nlohmann(for URLShortener)
- libexif (for EXIFDataExtractor)
- OpenSSL (for Encryptor)

## Projects

### Encryptor

The Encryptor project is a simple encryption tool that allows users to encrypt and decrypt text using various algorithms. It's designed to demonstrate basic cryptography concepts in C++.

### Base64 Generator

This utility converts input data into its Base64 representation, a common encoding scheme used in data serialization and transmission. It showcases how to implement encoding algorithms in C++.


### EXIF Data Extractor

The EXIF Data Extractor is a tool for extracting metadata from digital photos, such as camera settings, GPS data, and timestamps. It demonstrates how to work with external libraries in C++.

## To Run
```bash
g++ -o read_exif main.cpp -lexif
./read_exif <image_file>
```

### URL Shortener

A simple URL shortening service implemented in C++, demonstrating web API interaction and basic data storage techniques.

```bash
g++ -o shorturl urlshortener.cpp main.cpp -lcurl
./shorturl
``` 

## Getting Started

To get started with these projects, you'll need a C++ compiler and any necessary development tools specific to your platform.

## Installation Process

1. Clone the SecureX Tools repository:
   ```
   git clone "https://github.com/AnuragDahal/SecureX-Tools.git"
    ``` 
2. Navigate to the cloned directory:
    ```
    cd SecureX-Tools
    ```
3. Compile each tool according to its specific instructions found in their respective directories.

## Run 

To run any of the SecureX Tools, navigate to the tool's directory and follow the run instructions provided in the tool's README.

## Contributors

1. [Anurag Dahal](https://github.com/AnuragDahal)
2. [Nabin Khair](https://github.com/nabinkhair42)
3. [Nitesh Pokhrel](https://github.com/nitesh171)
4. [Basanta Khatiwada](https://github.com/basanta-devs)
