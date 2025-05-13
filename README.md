# Text Document Analyzer

## File Structure
```
TextAnalyzer/
├── src/
│   ├── main.cpp
│   ├── file_loader.cpp
│   ├── text_analyzer.cpp
│   ├── csv_analyzer.cpp
│   ├── json_analyzer.cpp
│   └── utils.cpp
├── include/
│   ├── file_loader.h
│   ├── text_analyzer.h
│   ├── csv_analyzer.h
│   ├── json_analyzer.h
│   └── utils.h
├── Makefile
└── README.md
```

## Core Requirements

- Command-line interface with argument parsing
- Support for multiple file formats (txt, csv, json)
- Modular code with proper C++ file structure (headers, implementation files)
- Error handling for file operations and invalid inputs
- Efficient algorithms for text analysis

## Features to Implement
### Basic Features (Required)

- File loading and validation
- Word count and frequency analysis
- Line count, character count (with and without whitespace)
- Average word length
- Most common words (configurable top N)
- Basic search functionality (find occurrences of a term)

### Technical Requirements

- Use modern C++ features (C++11 or newer)
- Implement proper memory management
- Create a clear project structure with header files
- Include a Makefile or CMake build system
- Add comprehensive error handling
- Write a concise README with usage examples
