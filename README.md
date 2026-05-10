# C Chat Server

A simple two-person chat server implemented in C using TCP sockets and the `select()` system call.

## Features

- Real-time chat between two users.
- Users choose their names upon connecting.
- Messages are displayed with sender's name (e.g., `User: Message`).
- Graceful handling of client disconnections.

## Setup & Build

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/RedYukiRed/c-chat-server.git
    cd c-chat-server
    ```

2.  **Build the server:**
    Ensure you have GCC and Make installed.
    ```bash
    make
    ```
    This command will create a `build/` directory and compile the project into an executable file named `Chat` inside it.

## Usage

1.  **Start the server:**
    Run the executable from the `build` directory:
    ```bash
    ./build/Chat
    ```
    The server will start listening on port `9001` by default.

2.  **Connect two clients:**
    Open two separate terminals. You will need one terminal for the server and two for the clients.

    *   **Terminal 1 (Server):** Run the compiled server.
        ```bash
        ./build/Chat
        ```
    *   **Terminal 2 (Client 1):** Connect to the server using `telnet` or `nc`.
        ```bash
        telnet 127.0.0.1 9001
        # or
        nc 127.0.0.1 9001
        ```
    *   **Terminal 3 (Client 2):** Connect to the server using `telnet` or `nc`.
        ```bash
        telnet 127.0.0.1 9001
        # or
        nc 127.0.0.1 9001
        ```

3.  **Enter your name:**
    When prompted by the server after connecting, each client should enter a unique username.

4.  **Chat:**
    Once both clients are connected and have provided their names, messages sent by one client will be delivered to the other, prefixed with the sender's username.

## How it Works

The server utilizes TCP sockets and the `select()` system call to efficiently manage real-time communication between two connected clients. After clients identify themselves with usernames, the server relays messages between them.
