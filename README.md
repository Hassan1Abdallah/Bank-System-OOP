# BankSystemOOP

A console-based **Object-Oriented Bank Management System** built in **C++**, offering core functionalities for managing clients, users, currency exchange, and transactions. The system emphasizes **clean architecture**, **access control**, and **modular design**.

---

## 🖥️ How to Run

> ✅ Tested on **Windows** environment (Visual Studio / MinGW).

1. Clone the repo.
2. Open the project in your preferred IDE (e.g., Visual Studio).
3. Make sure all `.txt` data files exist in the `Data/` folder.
4. Build and run `main.cpp`.
5. Login using a valid user.

---

## 📷 Screenshots

1. **Login Screen**

  ![image](https://github.com/user-attachments/assets/0dd80142-3065-489c-b37a-a7af1d720fdb)

2. **Main Menu**

  ![image](https://github.com/user-attachments/assets/8469ca73-a295-4e67-a5a7-9a8c6a990612)

3. **Transactions Menu**

  ![image](https://github.com/user-attachments/assets/c2328820-ee46-47c1-a4f0-10fbdfc2b001)

4. **Manage Users Menu**

  ![image](https://github.com/user-attachments/assets/ea6811a6-0b42-4d63-8314-c6456fa180c3)

5. **Currency Exchange Menu**

  ![image](https://github.com/user-attachments/assets/34f0b8eb-d250-4472-ada7-1c26d2c99480)


---

## 📁 Project Structure

```
BankSystemOOP/
├── Core/                  # Main entities and business models
├── Lib/                   # Utility/helper classes
├── Screens/               # UI components split by module
│   ├── Clients/           # All client-related screens
│   ├── Users/             # All user-related screens
│   ├── Currencies/        # All currency-related screens
│   ├── MainScreen.h       # Main navigation menu
│   ├── Screen.h           # Base screen class with shared logic
├── Data/                  # Data persistence (TXT files)
├── Global.h               # Shared global state (e.g., current user)
├── main.cpp               # Entry point
```

---

## 🔐 User Permissions Explained

| **Permission Name** | **Description**                    | **Enum Value**         |
| ------------------- | ---------------------------------- | ---------------------- |
| List Clients        | View all clients in the system     | `pListClients = 1`     |
| Add New Client      | Add a new client                   | `pAddNewClient = 2`    |
| Delete Client       | Delete an existing client          | `pDeleteClient = 4`    |
| Update Client       | Modify client details              | `pUpdateClients = 8`   |
| Find Client         | Search for a client by account     | `pFindClient = 16`     |
| Transactions        | Access deposit, withdraw, transfer | `pTranactions = 32`    |
| Manage Users        | Add, Delete, Update, List users    | `pManageUsers = 64`    |
| Login Register      | View login history of users        | `pLoginRegister = 128` |
| Full Access         | All above permissions combined     | `-1`                   |

Permissions are managed using a bitwise flag system per user.

---

## 🌟 Features

* ✅ Fully Object-Oriented Design (OOP Principles)
* ✅ Clean separation of responsibilities
* ✅ Robust Input Validation (via `InputValidate.h`)
* ✅ Centralized Permission System per User
* ✅ Login & Login History Tracking
* ✅ Transaction Features: Deposit, Withdraw, Transfer, Logs
* ✅ Currency Exchange + Calculator Tool
* ✅ Admin Panel for User Management
* ✅ Uses flat file `.txt` storage
* ✅ Highly extensible & modular file structure
* ✅ Role-Based Access with Permission Flags
* ✅ Organized folder structure for Clients / Users / Currencies
* ✅ Easy-to-read Menus with Clear Navigation

---

## 📄 Data Files

Located inside the `/Data/` folder:

* `Clients.txt`
* `Users.txt`
* `Currencies.txt`
* `TransferLog.txt`
* `LoginRegister.txt`

> ⚠️ Make sure these files are present and writable.

---

## 🙋 Author

Originally created by [Dr. Mohammed Abu-Hdhoud].

Refactored, extended, and maintained by [Hassan Abdallah], with a focus on code structure, user interface, and feature optimization.

For questions or suggestions, feel free to contact: hassan20230123@gmail.com

---
