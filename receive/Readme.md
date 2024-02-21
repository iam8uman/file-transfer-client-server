# Terminal-Based File Transfer System

## Overview

This is a basic terminal-based client-server file transfer system written in C. The system allows clients to connect to a server, upload files, and download files from the server.

## Usage

### Client

1. Open a terminal and compile the client:

    ```bash
    gcc client.c -o client
    ```

2. Run the client:

    ```bash
    ./client
    ```

3. Choose the option to upload or download files and follow the prompts.

### Server

1. Open another terminal and compile the server:

    ```bash
    gcc server.c -o server
    ```

2. Run the server:

    ```bash
    ./server
    ```

3. The server listens on a specified port and manages file transfers.

## File Transfer Process

- **Uploading a File (Client to Server):**
  1. Select the option to upload a file.
  2. Enter the file path you want to upload.

- **Downloading a File (Client from Server):**
  1. Select the option to download a file.
  2. Enter the filename you want to download.

## Notes

- This is a basic example. In a production environment, consider implementing encryption, authentication, and error handling.
- Ensure that you have the necessary permissions to read and write files in the working directory.
- The server runs indefinitely; you may manually stop it with a keyboard interrupt (`Ctrl+C`).
