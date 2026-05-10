```markdown
# C Chat Server

A simple two-person chat application in C using TCP sockets. Built as a learning project for C programming and network sockets.

> **Note:** This is a learning project. Some parts were developed with AI assistance.

## Features

- Real-time chat between two users
- Custom usernames
- Messages prefixed with sender's name
- Dedicated client application (no telnet needed)

## Build & Run

```bash
git clone https://github.com/RedYukiRed/c-chat-server.git
cd c-chat-server
make
```

## Usage

**1. Start the server (Terminal 1):**
```bash
./build/server/chat_server
```

**2. Start clients (Terminals 2 & 3):**
```bash
# Default (localhost:9001)
./build/client/chat_client

# Custom IP and port
./build/client/chat_client 192.168.1.5 9001
```

**3. Chat!** Enter your name when prompted, then start messaging.

## Project Structure

```
├── src/
│   ├── common/    # Shared socket utilities
│   ├── server/    # Server implementation
│   └── client/    # Client application
├── include/       # Header files
└── build/         # Compiled binaries
```

## Requirements

- GCC
- Make
- Linux/macOS (uses POSIX sockets)

---

Enjoy chatting!
```