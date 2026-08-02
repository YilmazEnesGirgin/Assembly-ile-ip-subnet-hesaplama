# Subnet Engine x64

This project is a hybrid **C** and **x64 Assembly** networking calculator designed to simulate a router's **Control Plane** and **Data Plane** architecture. It calculates IPv4 subnet details (Subnet Mask, Network ID, Broadcast ID) using high-performance assembly bitwise operations while managing user interaction and data formatting via C.

## 🧠 Architecture Overview

- **Control Plane (`ControlPlane.c`)**: Acts as the management layer. It handles user input (IP address and CIDR prefix), parses strings into 32-bit integers, formats output into Decimal and Binary representations, and manages terminal buffers.
- **Data Plane (`DataPlane.asm`)**: Acts as the forwarding/calculation engine. Written in **x86-64 Assembly** using Windows ABI calling conventions (`RCX`, `RDX`, `R8`), it performs low-level bitwise operations (`SHL`, `NOT`, `AND`, `OR`) to compute subnet boundaries at maximum execution speed.

## 📁 Project Structure

```text
├── ControlPlane.c   # Main C program (CLI, I/O, formatting)
├── DataPlane.asm    # x64 Assembly module (Bitwise subnet math)
└── README.md        # Project documentation
