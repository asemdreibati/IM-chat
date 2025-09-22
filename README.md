# 💬 IM-Chat

IM-Chat is a lightweight, cross-platform instant messaging application built with **C++** and **Qt**, featuring a clean client-server architecture. It supports **private chats**, **group chats**, and **broadcast messaging** — making it a great learning tool for socket programming and GUI development.

---

## ✨ Features

- **Unicast Chatting (Private)** – Send direct messages to a specific user.
- **Multicast Chatting (Groups)** – Create chat groups, add online users, and exchange messages within the group.
- **Broadcast Chatting** – Send a message to all connected users at once.
- **Real-Time Communication** – Low-latency messaging over TCP sockets.
- **Cross-Platform** – Works on Windows, macOS, and Linux.
- **Qt GUI** – Clean, responsive interface.

---

## 📸 Screenshots

Below are examples of IM‑Chat in action, demonstrating its three core messaging modes.

| One‑to‑One Chat (Unicast)                                                                    | Group Chat (Multicast)                                                                           | Broadcast to All                                                                                               |
| -------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------ | -------------------------------------------------------------------------------------------------------------- |
| ![One-to-One Chat](assets/screenshots/unicast.png?raw=true 'Private chat between two users') | ![Group Chat](assets/screenshots/groupchat.png?raw=true 'Group chat with multiple participants') | ![Broadcast Chat](assets/screenshots/broadcast.png?raw=true 'Broadcast message sent to all connected clients') |

---

## 🏗️ How It Works

1. **Run the Server Instance**  
   Start the server application first — it will listen for incoming client connections.

2. **Launch the Client(s)**  
   For each client:

   - Enter the **server IP** (e.g., `127.0.0.1` for local testing).
   - Enter your **display name**.
   - Click **Join**.

3. **Start Chatting**
   - The joiner will be visible to all connected users.
   - Choose between **private**, **group**, or **broadcast** messaging.

---

## 📦 Installation

### Prerequisites

- Qt 6.9+ (Qt Widgets module)
- CMake 3.31+
- C++17-compatible compiler (GCC, Clang, or MSVC)

### Build Steps

```bash
git clone https://github.com/asemdreibati/IM-chat.git
cd IM-chat
mkdir build && cd build
cmake ..
cmake --build .
```

---

## ▶️ Running the Application from the Build Directory

After building, you can run the applications directly from the `build` folder.

### Start the Server

```bash
./Server-Side/IMChatServer
```

(On Windows, use Server-Side\Debug\IMChatServer.exe or Server-Side\Release\IMChatServer.exe depending on your build type.)

### Start a Client

```bash
./Client-Side/IMChatClient
```

(On Windows, use Client-Side\Debug\IMChatClient.exe or Client-Side\Release\IMChatClient.exe.)

---

## ▶️ Generating & Viewing Documentation(Doxygen)

This project includes a Doxygen configuration for generating HTML documentation.

### Generate Docs

```bash
# From the project root
run_doxy_file.bat
```

This will create a docs/html/ folder containing the generated documentation.

### View Docs

Open:

```bash
docs/html/index.html
```

in your web browser to explore class hierarchies, public interfaces.
