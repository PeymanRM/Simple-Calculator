<h1 align="center">
  Simple Calculator
  <br>
</h1>

<h4 align="center">A 2-operand standard calculator built with C for ATmega16.</h4>



<p align="center">
  <a href="#key-features">Key Features</a> •
  <a href="#flowchart">Flowchart</a> •
  <a href="#how-to-use">How To Use</a> •
  <a href="#notes">Notes</a> •
  <a href="#Prerequisites">Prerequisites</a> •
  <a href="#license">License</a>
</p>

![screenshot](https://raw.githubusercontent.com/PeymanRM/Simple-Calculator/main/img/calculator_gif.gif)

## Key Features

* Basic Arithmetic Operations
  - Addition (+), Subtraction (-), Multiplication (×), and Division (÷).
  - Percentage (%)
  - Square Root (√)
  - Power (^)
* Chained Calculations
  - No need for pressing "=" to do another calculation with the result of last one.
* Floating Point Support
  - Handles both integer and floating-point numbers for more precise calculations.
  - Supports up to 3 decimals.
* Automatic Refill
  - If not taken an operand, suggests operands from previous calculations instead.
* Proteus Simulation

## Flowchart

![flowchart](https://raw.githubusercontent.com/PeymanRM/Simple-Calculator/main/img/nonDigitKeyPress%20Flowchart.jpg)

## How To Use

1. **Clone the Repository:** To clone and run this application, you'll need [Git](https://git-scm.com) installed on your computer. From your command line:
```bash
# Clone this repository
$ git clone https://github.com/PeymanRM/Simple-Calculator.git
```
2. **Open the Proteus Simulation:**
Navigate to the circuit folder and open the provided Proteus simulation file (calculator.pdsprj).
4. **Chose program file:** Double-click on U1 and choose the program file: ```./Code/Debug/Exe/ATmega16_Calculator.hex```
5. **Start the simulation**

## Notes

> **Note 1:**
> Power operation (^) is actually (+/-) button.

> **Note 2:**
> Memory operations on keypad are not implemented.

## Prerequisites

- CodeVisionAVR 3.14
- Proteus 8

## License

MIT

---

> LinkedIn [@PeymanRM](https://www.linkedin.com/in/peymanrm) &nbsp;&middot;&nbsp;
> GitHub [@PeymanRM](https://github.com/PeymanRM) &nbsp;&middot;&nbsp;
> X [@Peyman_RM](https://x.com/Peyman_RM)