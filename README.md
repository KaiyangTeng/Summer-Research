# DFA Separation Research Project

## Project Overview

This is a research project on **Deterministic Finite Automaton (DFA) separation problems**. The project investigates how to find the minimum-state DFA that can separate three binary strings, belonging to the field of computational complexity theory and automata theory.
[Click here for the reserach paper](Separating Three Words by Finite Automata.pdf)






## Research Problem

**DFA Three-String Separation Problem:**
- Given three binary strings x, y, z of equal length
- Find a DFA M with the minimum number of states
- Such that there exists a starting state where the three strings reach different final states after processing through the DFA

## Project Structure

```
DFA/
├── main.cpp              # Main program - complete research implementation
├── test.cpp              # Test program - testing for 6-bit strings
├── DFA.h                 # DFA class definition - three-string separation version
├── DFA (1).h            # DFA class definition - two-string separation version
├── DFA (2).h            # DFA class definition - three-string separation version (backup)
├── command.txt          # Deployment commands
├── main                 # Compiled executable
└── N*_Result.txt        # Experimental result files for various lengths
```

## Core Algorithms

### 1. DFA Class Design

```cpp
struct state {
    size_t t_0 = 0;  // Transition state on input '0'
    size_t t_1 = 0;  // Transition state on input '1'
};
```

**Main Methods:**
- `seperation(x, y, z)`: Check if three strings can end in different states from a specified starting state
- `E_seperation(x, y, z)`: Check if there exists a starting state where three strings can be separated
- `operator++()`: Increment operation for DFA configuration, used to enumerate all possible DFAs

### 2. Separation Algorithm

```cpp
DFA find_result(const std::string& str1, const std::string& str2, const std::string& str3, size_t& val)
```

**Algorithm Flow:**
1. Start with 3 states
2. Enumerate all possible DFA configurations (n^(2n) possibilities)
3. Test each configuration to see if it can separate the three strings
4. If no solution found with current state count, increase state count and repeat
5. Return the first solution found

### 3. String Generation

Supports multiple string generation strategies:
- `str_generator_exactly_N_one()`: Generate strings containing exactly N '1's
- `str_generator_2_one()`: Generate strings containing at most 2 '1's
- `str_generator()`: Generate all possible binary strings

## Compilation and Execution

### Compilation
```bash
g++ -o main main.cpp
g++ -o test test.cpp
```

### Run Main Program
```bash
./main
```
The program will prompt for string length input, then perform complete separation experiments.

### Run Test Program
```bash
./test
```
Quick testing for 6-bit strings.

## Experimental Results

### Output Format

Result files contain the following information:
- `str1, str2, str3`: Three input strings
- `val1, val2, val3`: Indices of strings in the list
- `dist`: Minimum number of states required for separation
- `result`: String representation of DFA (encoding of state transitions)
- `val`: Index value of DFA configuration

### Sample Output
```
str1            str2            str3            val1    val2    val3    dist    result          val
000010000       00010000        010000000       1       2       4       4       00010302        306
```

## Research Features

### 1. Theoretical Background
- Computational complexity research on DFA separation problems
- Exploration of minimum-state DFA construction methods
- Analysis of separation difficulty for different string lengths

### 2. Experimental Methods
- Brute force search through all possible DFA configurations
- State count increment optimization strategy
- Large-scale experimental data collection and analysis

### 3. Algorithm Complexity
- Time Complexity: O(n^(2n) × string length)
- Space Complexity: O(n)
- Where n is the number of DFA states

## File Descriptions

### Core Files
- `main.cpp`: Complete research implementation supporting arbitrary length strings
- `test.cpp`: Quick testing for 6-bit strings
- `DFA.h`: Three-string separation DFA class implementation

### Variant Files
- `DFA (1).h`: Two-string separation version with more separation types (E-separation, A-separation, etc.)
- `DFA (2).h`: Backup implementation for three-string separation

### Result Files
- `N*_Result.txt`: Experimental results for different string lengths
- `N* *state Mod_Result.txt`: State estimation results based on modular arithmetic theory

## Usage Examples

### Basic Usage
```cpp
#include "DFA.h"

// Create 3-state DFA
DFA m(3);

// Test separation
if (m.E_seperation("000", "001", "010")) {
    std::cout << "Strings can be separated" << std::endl;
}
```

### Complete Experiment
```cpp
// Generate string list
std::vector<std::string> strings;
std::string path = "";
str_generator_exactly_N_one(0, 1, 6, path, strings);

// Test all triplets
for (int i = 0; i < strings.size(); i++) {
    for (int j = i + 1; j < strings.size(); j++) {
        for (int k = j + 1; k < strings.size(); k++) {
            DFA result = find_result(strings[i], strings[j], strings[k], val);
            // Process results...
        }
    }
}
```

## Research Significance

1. **Theoretical Contribution**: Provides experimental data and algorithm implementation for DFA separation problems
2. **Computational Complexity**: Studies the computational complexity and optimization methods of this problem
3. **Automata Theory**: Explores DFA minimization construction techniques
4. **Experimental Verification**: Validates theoretical conjectures through large-scale experiments

## Future Directions

1. **Algorithm Optimization**: Improve search strategies to reduce computation time
2. **Theoretical Analysis**: Deep analysis of mathematical properties of separation problems
3. **Application Extension**: Apply separation techniques to other automata problems
4. **Parallel Computing**: Utilize multi-core processors to accelerate large-scale experiments

## Author Information

This is a 2024 Summer Research project focusing on computational complexity of DFA separation problems.

## License

This project is for academic research purposes only.
