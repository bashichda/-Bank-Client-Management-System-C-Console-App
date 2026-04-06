# 🏦 Bank Client Management System v3 — C++ Console App

![C++](https://img.shields.io/badge/Language-C%2B%2B-blue?style=flat-square&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey?style=flat-square&logo=windows)
![File I/O](https://img.shields.io/badge/Storage-File%20I%2FO-orange?style=flat-square)
![Auth](https://img.shields.io/badge/Auth-Login%20%2B%20Permissions-red?style=flat-square)
![Version](https://img.shields.io/badge/Version-3.0-purple?style=flat-square)
![Status](https://img.shields.io/badge/Status-Complete-brightgreen?style=flat-square)
![License](https://img.shields.io/badge/License-MIT-yellow?style=flat-square)

A fully-featured console-based **Bank Management System** written in C++. This version introduces a **Login Screen**, a **Role-Based Permission System**, and a complete **User Management Module** — making it the most advanced version in the series.

---

## 📸 Preview

```
-------------------------------------
            Login Screen
-------------------------------------
Enter UserName : admin
Enter Password : 1234

================================================
                Main Menue Screen
================================================
        [1] Show Client List.
        [2] Add New Client.
        [3] Delete Client.
        [4] Update Client Info.
        [5] Find Client.
        [6] Transactions.
        [7] Manage Users.        ← NEW in v3
        [8] Logout.              ← NEW in v3
================================================

-----------------------------------------
Access Denied,
You don't have Permission to Do this,
Please Contact Your Admin.
-----------------------------------------
```

---

## ✨ What's New in v3

| Feature | v1 | v2 | v3 |
|---|---|---|---|
| Client CRUD (List/Add/Delete/Update/Find) | ✅ | ✅ | ✅ |
| Transactions (Deposit/Withdraw/Balances) | ❌ | ✅ | ✅ |
| Login Screen with authentication | ❌ | ❌ | ✅ |
| Role-based permission system | ❌ | ❌ | ✅ |
| User Management (CRUD) | ❌ | ❌ | ✅ |
| Bitwise permission flags | ❌ | ❌ | ✅ |
| Access Denied protection per screen | ❌ | ❌ | ✅ |
| Logout & session handling | ❌ | ❌ | ✅ |

---

## 🗂️ Project Structure

```
Bank-Client-Management-v3/
│
├── main.cpp         # Full application source code
├── Clients.txt      # Auto-generated clients data file
├── Users.txt        # Auto-generated users data file
└── README.md        # Project documentation
```

---

## 🧱 Code Architecture

### Data Structures

| Component | Type | Description |
|---|---|---|
| `sClient` | `struct` | Account number, pin, name, phone, balance, delete flag |
| `sUser` | `struct` | Username, password, permissions (int), delete flag |
| `CurrentUser` | `global sUser` | Stores the currently logged-in user's session |
| `enMainMenueOptions` | `enum` | Main menu choices (1–8) |
| `enTransactionsMenueOptions` | `enum` | Transaction menu choices (1–4) |
| `enManageUsersMenueOptions` | `enum` | User management menu choices (1–6) |
| `enMainMenuePermissions` | `enum` | Bitwise permission flags for each feature |

### 🔐 Permission System (Bitwise Flags)

Permissions are stored as a single `int` using bitwise OR — each feature maps to a unique power of 2:

| Permission | Value | Binary |
|---|---|---|
| `pListClient` | 1 | `0000001` |
| `pAddClient` | 2 | `0000010` |
| `pDeleteClient` | 4 | `0000100` |
| `pUpdateClient` | 8 | `0001000` |
| `pFindClient` | 16 | `0010000` |
| `pTransaction` | 32 | `0100000` |
| `pManageUsers` | 64 | `1000000` |
| `pAll` | -1 | Full access |

**Example:** A user with permissions `= 35` has access to: List (1) + Add (2) + Transaction (32) = `35`

```cpp
// How permission check works:
bool CheckPermission(enMainMenuePermissions Permission) {
    if (CurrentUser.Permissions == pAll) return true;
    return (Permission & CurrentUser.Permissions) == Permission;
}
```

### Menu Flow

```
Login Screen
    └── Authenticate from Users.txt
            └── Main Menu
                ├── [1] Show Client List      (requires pListClient)
                ├── [2] Add New Client         (requires pAddClient)
                ├── [3] Delete Client          (requires pDeleteClient)
                ├── [4] Update Client          (requires pUpdateClient)
                ├── [5] Find Client            (requires pFindClient)
                ├── [6] Transactions ────────► Transactions Menu
                │                               ├── [1] Deposit    (requires pTransaction)
                │                               ├── [2] Withdraw
                │                               ├── [3] Total Balances
                │                               └── [4] Back to Main Menu
                ├── [7] Manage Users ────────► Manage Users Menu  (requires pManageUsers)
                │                               ├── [1] List Users
                │                               ├── [2] Add User
                │                               ├── [3] Delete User
                │                               ├── [4] Update User
                │                               ├── [5] Find User
                │                               └── [6] Back to Main Menu
                └── [8] Logout ──────────────► Login Screen
```

### Key Functions

**Authentication:**

| Function | Description |
|---|---|
| `Login()` | Login loop — retries until valid credentials entered |
| `FindUserByUserNameAndPassword()` | Searches `Users.txt` for matching username + password |
| `LoadUserInfo()` | Sets `CurrentUser` global on successful login |
| `CheckPermission()` | Bitwise check of current user's permission against required flag |
| `ShowAccessDeniedMessage()` | Displays access denied message when permission check fails |

**User Management (new in v3):**

| Function | Description |
|---|---|
| `LoadUsersDataFromFile()` | Reads all user records into `vector<sUser>` |
| `SaveDataUsersInFile()` | Writes user vector back to file (skips deleted) |
| `ConvertUserRecordToLine()` | Serializes `sUser` to `username#//#password#//#permissions` |
| `ConvertUserLineToRecord()` | Parses a line from `Users.txt` into an `sUser` struct |
| `ReadNewUser()` | Reads username, password, and sets permissions interactively |
| `ChangeUserRecord()` | Reads updated password and permissions for an existing user |
| `FindUserByUserName()` | Searches user vector by username |
| `DeleteUserByUserName()` | Confirms then soft-deletes and saves |
| `UpdateUserByUserName()` | Confirms then updates user record and saves |
| `ShowManageUserMenue()` | Renders user management menu (requires `pManageUsers`) |

---

## 🚀 Getting Started

### Prerequisites

- A C++ compiler (e.g. **g++**, **MSVC**, **MinGW**)
- Windows OS *(uses `system("cls")` and `system("pause")` — Windows only)*

### Compile & Run

**Using g++ (MinGW / terminal):**
```bash
g++ main.cpp -o BankSystemV3
./BankSystemV3
```

**Using Visual Studio:**
1. Create a new **Empty C++ Project**
2. Add `main.cpp` to the project
3. Press `Ctrl + F5` to build and run

### First Run Setup

On the first run, you need a `Users.txt` file with at least one admin account. Create it manually in the same folder as the executable:

```
admin#//#1234#//#-1
```

> This creates user `admin` with password `1234` and full access (`-1 = pAll`).

---

## 💾 File Formats

**Clients.txt** — delimited by `#//#`:
```
A1001#//#1234#//#Mohammed El Amrani#//#0612345678#//#20000.000000
```

**Users.txt** — delimited by `#//#`:
```
admin#//#1234#//#-1
staff#//#5678#//#35
```

> User `staff` with permissions `35` = List (1) + Add (2) + Transactions (32)

---

## 🛠️ Technologies Used

- **Language:** C++
- **Libraries:** `<iostream>`, `<fstream>`, `<vector>`, `<string>`, `<iomanip>`
- **Concepts:** Structs, Enums, File I/O, Vectors, CRUD, Bitwise Operations, Role-Based Access Control (RBAC), Session Management, Soft Delete

---

## 🔮 Possible Improvements

- [ ] Hash passwords instead of storing them as plain text
- [ ] Add **last login timestamp** per user
- [ ] Implement **account lockout** after failed login attempts
- [ ] Add **transaction history log** with date and time
- [ ] Support **transfer between accounts**
- [ ] Port to **cross-platform** (remove `system()` calls)
- [ ] Migrate storage to **SQLite** for scalability

---

## 👨‍💻 Author

> Built with ❤️ as part of a C++ learning journey.

Feel free to fork, star ⭐, or contribute!

---

## 📄 License

This project is licensed under the **MIT License** — free to use and modify.
