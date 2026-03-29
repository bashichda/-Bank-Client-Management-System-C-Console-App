# 🏦 Bank Client Management System — C++ Console App

![C++](https://img.shields.io/badge/Language-C%2B%2B-blue?style=flat-square&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey?style=flat-square&logo=windows)
![File I/O](https://img.shields.io/badge/Storage-File%20I%2FO-orange?style=flat-square)
![Status](https://img.shields.io/badge/Status-Complete-brightgreen?style=flat-square)
![License](https://img.shields.io/badge/License-MIT-yellow?style=flat-square)

A console-based **Bank Client Management System** written in C++ that allows full CRUD operations on bank clients. All data is **persisted to a text file**, making it a real-world data management application with a clean menu-driven interface.

---

## 📸 Preview

```
================================================
                Main Menue Screen
================================================
        [1] Show Client List.
        [2] Add New Client.
        [3] Delete Client.
        [4] Update Client Info.
        [5] Find Client.
        [6] Exit.
================================================

----------------------------------------------------------------------------------------------
| AccountNumber  | PinCode    | Client Name                              | Phone        | Balance
----------------------------------------------------------------------------------------------
| A1001          | 1234       | Mohammed El Amrani                       | 0612345678   | 15000.00
| A1002          | 5678       | Sara Benali                              | 0698765432   | 8500.50
----------------------------------------------------------------------------------------------
```

---

## ✨ Features

- 📋 **List all clients** — formatted table with account number, pin, name, phone, and balance
- ➕ **Add new clients** — with duplicate account number detection
- ❌ **Delete clients** — with confirmation prompt before deletion
- ✏️ **Update client info** — modify any field by account number
- 🔍 **Find a client** — instant lookup by account number with full details card
- 💾 **File persistence** — all data saved to `Clients.txt` and reloaded on every run
- ✅ **Input validation** — duplicate check, range validation, and safe string reading

---

## 🗂️ Project Structure

```
Bank-Client-Management/
│
├── main.cpp         # Full application source code
├── Clients.txt      # Auto-generated data file (created on first add)
└── README.md        # Project documentation
```

---

## 🧱 Code Architecture

### Data Structures

| Component | Type | Description |
|---|---|---|
| `sClient` | `struct` | Holds account number, pin, name, phone, balance, and delete flag |
| `enMainMenueOptions` | `enum` | Maps menu choices to operations (List, Add, Delete, Update, Find, Exit) |

### File Format

Client records are stored in `Clients.txt` using a custom delimiter `#//#`:

```
A1001#//#1234#//#Mohammed El Amrani#//#0612345678#//#15000.000000
A1002#//#5678#//#Sara Benali#//#0698765432#//#8500.500000
```

### Key Functions

| Function | Description |
|---|---|
| `LoadClientsDataFromFile()` | Reads all records from file into a `vector<sClient>` |
| `SaveDataClientsInFile()` | Writes the full client vector back to file (skips deleted) |
| `ConvertLineToRecord()` | Parses a delimited line into an `sClient` struct |
| `ConvertRecordToLine()` | Serializes an `sClient` struct into a delimited string |
| `SplitString()` | Custom string splitter using a delimiter |
| `ClientExistsByAccountNumber()` | Checks file for duplicate account numbers before adding |
| `FindClientByAccountNumber()` | Searches vector for a client by account number |
| `MarkClientForDelete()` | Sets `MarkForDelete = true` on matching client |
| `DeleteClientByAccountNumber()` | Confirms then marks + saves to remove a client |
| `UpdateClientByAccontNumber()` | Confirms then replaces client fields in vector and saves |
| `ReadNewClient()` | Reads all fields for a new client with validation |
| `PrintClientCard()` | Displays full client details in a formatted card |
| `PrintClientRecord()` | Prints a single row in the client list table |
| `ShowMainMenue()` | Renders the main menu and routes to operations |
| `PerformMainMenueOptions()` | Switch-case dispatcher for all menu actions |

---

## 🚀 Getting Started

### Prerequisites

- A C++ compiler (e.g. **g++**, **MSVC**, **MinGW**)
- Windows OS *(uses `system("cls")` and `system("pause")` — Windows only)*

### Compile & Run

**Using g++ (MinGW / terminal):**
```bash
g++ main.cpp -o BankSystem
./BankSystem
```

**Using Visual Studio:**
1. Create a new **Empty C++ Project**
2. Add `main.cpp` to the project
3. Press `Ctrl + F5` to build and run

> ⚠️ `Clients.txt` will be created automatically in the same directory as the executable when you first add a client.

---

## 🎮 How to Use

| Option | Action |
|---|---|
| `1` | Show a formatted list of all clients |
| `2` | Add one or more new clients (with duplicate guard) |
| `3` | Delete a client by account number (with confirmation) |
| `4` | Update a client's info by account number (with confirmation) |
| `5` | Search for a client by account number and view their card |
| `6` | Exit the program |

---

## 🧠 How Data Persistence Works

```
Run program
    └── Load Clients.txt → vector<sClient>
            ├── Add    → Append directly to file
            ├── Delete → Mark flag → Re-save vector (skip flagged)
            └── Update → Modify in vector → Re-save entire vector
```

The **soft delete** pattern (`MarkForDelete`) ensures no accidental data loss — records are only removed from disk when the file is re-written.

---

## 🛠️ Technologies Used

- **Language:** C++
- **Libraries:** `<iostream>`, `<fstream>`, `<vector>`, `<string>`, `<iomanip>`
- **Concepts:** Structs, Enums, File I/O, Vectors, String Parsing, CRUD Operations, Soft Delete Pattern

---

## 🔮 Possible Improvements

- [ ] Add **password hashing** for PinCode security
- [ ] Implement **deposit / withdraw** transactions
- [ ] Add a **transaction history** log per client
- [ ] Support **sorting** the client list by name or balance
- [ ] Port to **cross-platform** (remove `system()` calls)
- [ ] Migrate storage to **SQLite** or a proper database

---

## 👨‍💻 Author

> Built with ❤️ as part of a C++ learning journey.

Feel free to fork, star ⭐, or contribute!

---

## 📄 License

This project is licensed under the **MIT License** — free to use and modify.
