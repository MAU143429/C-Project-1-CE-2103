# 🖥️ Project 1 — C! Language Client Interface CE-2103

## 📘 Overview

This repository contains the client-side graphical interface for the pseudo-language **C!**, developed as part of Project 1 in the course CE2103 — Algoritmos y Estructuras de Datos II at Instituto Tecnológico de Costa Rica.

The client communicates with a backend server responsible for parsing and executing C! code. This application allows users to write, load, and submit C! programs through a modern interface, view results, and receive syntax/semantic feedback in real-time.

---

## 🧩 Features

- 📝 **C! Code Editor** with syntax-aware input
- 📂 File handling for loading and saving C! source files
- 🔄 **Communication with server** via TCP sockets
- 📡 Sends user code to be interpreted and visualizes the output
- 🛠️ Interactive UI elements for better user experience

---

## 🛠️ Technologies Used

- **Language**: C++14
- **Framework**: Qt 5.15
- **Communication**: TCP sockets
- **IDE**: Qt Creator or Visual Studio with Qt integration

---

## 🔧 How to Use

1. Launch the server before starting the client.
2. Open the client application.
3. Write or load a C! program.
4. Submit the code — feedback and execution results are displayed in the interface.

---

## 🧪 Notes

- This client was designed and tested on **Windows 10** using **Qt 5.15**.
- For full backend logic and interpreter engine, refer to:  
  🔗 [C! Language Server Repo](https://github.com/MAU143429/Proyecto1-Server-C-CE-2103)

- The C! language includes features like:
  - Variable declarations
  - Conditional execution
  - Loops and arithmetic operations
  - Basic procedures

This project demonstrates socket-based communication and UI integration in the context of a compiler-interpreter system.
