# 🏦 Bank Client Management System v2 — C++ Console App

![C++](https://img.shields.io/badge/Language-C%2B%2B-blue?style=flat-square&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey?style=flat-square&logo=windows)
![File I/O](https://img.shields.io/badge/Storage-File%20I%2FO-orange?style=flat-square)
![Version](https://img.shields.io/badge/Version-2.0-purple?style=flat-square)
![Status](https://img.shields.io/badge/Status-Complete-brightgreen?style=flat-square)
![License](https://img.shields.io/badge/License-MIT-yellow?style=flat-square)

An extended console-based **Bank Client Management System** written in C++. This version builds on v1 by adding a full **Transactions Menu** with Deposit, Withdraw, and Total Balances features — all persisted to a text file.

> 🔗 **v1 (Client Management only):** [Bank-Client-Management-v1](https://github.com/YourUsername/Bank-Client-Management-v1)

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
        [6] Transactions.         ← NEW in v2
        [7] Exit.
================================================

================================================
            Transactions Menue Screen
================================================
        [1] Deposit.
        [2] Withdraw.
        [3] Total Balances.
        [4] Main Menue.
================================================

----------------------------------------------------------------------------------------------
| Account Number  | Client Name                              | Balance
----------------------------------------------------------------------------------------------
| A1001           | Mohammed El Amrani                       | 20000.00
| A1002           | Sara Benali                              | 8500.50
----------------------------------------------------------------------------------------------
                                        Total Balances = 28500.50
```

---

## ✨ What's New in v2

| Feature | v1 | v2 |
|---|---|---|
| List / Add / Delete / Update / Find clients | ✅ | ✅ |
| Transactions Menu | ❌ | ✅ |
| Deposit to account | ❌ | ✅ |
| Withdraw from account | ❌ | ✅ |
| Overdraft protection | ❌ | ✅ |
| Total balances screen | ❌ | ✅ |
| Dual menu navigation | ❌ | ✅ |

---

## 🗂️ Project Structure

```
Bank-Client-Management-v2/
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
| `sClient` | `struct` | Holds account number, pin, name, phone, balance, delete flag |
| `enMainMenueOptions` | `enum` | Maps main menu choices (1–7) to operations |
| `enTransactionsMenueOptions` | `enum` | Maps transaction menu choices (1–4) to operations |

### Menu Flow

```
Main Menu
├── [1] Show Client List
├── [2] Add New Client
├── [3] Delete Client
├── [4] Update Client Info
├── [5] Find Client
├── [6] Transactions ──────► Transactions Menu
│                               ├── [1] Deposit
│                               ├── [2] Withdraw
│                               ├── [3] Total Balances
│                               └── [4] Back to Main Menu
└── [7] Exit
```

### Key Functions

**Client Management (inherited from v1):**

| Function | Description |
|---|---|
| `LoadClientsDataFromFile()` | Reads all records from file into `vector<sClient>` |
| `SaveDataClientsInFile()` | Writes the full vector back to file (skips deleted) |
| `ConvertLineToRecord()` | Parses a delimited line into an `sClient` struct |
| `ConvertRecordToLine()` | Serializes an `sClient` struct into a delimited string |
| `FindClientByAccountNumber()` | Searches vector for a client by account number |
| `DeleteClientByAccountNumber()` | Confirms then soft-deletes and saves |
| `UpdateClientByAccontNumber()` | Confirms then updates client in vector and saves |

**Transactions (new in v2):**

| Function | Description |
|---|---|
| `DepositBalanceToClientByAccountNumber()` | Adds amount to client balance and saves to file |
| `ShowDepositScreen()` | Finds client, reads amount, calls deposit function |
| `ShowWithdrawScreen()` | Finds client, validates amount vs balance, calls deposit with negative value |
| `ShowTotalBalancesScreen()` | Lists all clients with balances and prints the sum |
| `ShowTransactionsMenue()` | Renders the transactions menu and routes choices |
| `PerformTransactionsMenueOptions()` | Switch-case dispatcher for all transaction actions |
| `GoBackToTransactionMenue()` | Returns to the transactions menu after any operation |

---

## 🚀 Getting Started

### Prerequisites

- A C++ compiler (e.g. **g++**, **MSVC**, **MinGW**)
- Windows OS *(uses `system("cls")` and `system("pause")` — Windows only)*

### Compile & Run

**Using g++ (MinGW / terminal):**
```bash
g++ main.cpp -o BankSystemV2
./BankSystemV2
```

**Using Visual Studio:**
1. Create a new **Empty C++ Project**
2. Add `main.cpp` to the project
3. Press `Ctrl + F5` to build and run

> ⚠️ `Clients.txt` will be created automatically in the same directory as the executable when you first add a client.

---

## 🎮 How to Use

### Main Menu

| Option | Action |
|---|---|
| `1` | Show formatted list of all clients |
| `2` | Add one or more new clients |
| `3` | Delete a client by account number |
| `4` | Update a client's info |
| `5` | Find and display a client's details |
| `6` | Open the Transactions menu |
| `7` | Exit the program |

### Transactions Menu

| Option | Action |
|---|---|
| `1` | Deposit an amount into a client's account |
| `2` | Withdraw an amount (with overdraft protection) |
| `3` | View all balances and the total sum |
| `4` | Return to the Main Menu |

---

## 🧠 How Transactions Work

**Deposit:**
```
Find client by account number
→ Show client card
→ Enter amount
→ Confirm (y/n)
→ balance += amount → Save to file
```

**Withdraw:**
```
Find client by account number
→ Show client card
→ Enter amount
→ Validate: amount must not exceed current balance
→ Confirm (y/n)
→ balance += (amount * -1) → Save to file
```

**Total Balances:**
```
Load all clients
→ Print each client's account + name + balance
→ Sum all balances → Display total
```

---

## 💾 File Format

Client records are stored in `Clients.txt` using a custom `#//#` delimiter:

```
A1001#//#1234#//#Mohammed El Amrani#//#0612345678#//#20000.000000
A1002#//#5678#//#Sara Benali#//#0698765432#//#8500.500000
```

---

## 🛠️ Technologies Used

- **Language:** C++
- **Libraries:** `<iostream>`, `<fstream>`, `<vector>`, `<string>`, `<iomanip>`
- **Concepts:** Structs, Enums, File I/O, Vectors, CRUD, Soft Delete, Dual Menu Navigation, Overdraft Validation

---

## 🔮 Possible Improvements

- [ ] Add **transaction history log** per client
- [ ] Add **password hashing** for PinCode security
- [ ] Support **transfer between accounts**
- [ ] Add **date/time stamping** for each transaction
- [ ] Port to **cross-platform** (remove `system()` calls)
- [ ] Migrate storage to **SQLite** or a proper database

---

## 👨‍💻 Author

> Built with ❤️ as part of a C++ learning journey.

Feel free to fork, star ⭐, or contribute!

---

## 📄 License

This project is licensed under the **MIT License** — free to use and modify.
