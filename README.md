Terminal Chatter
=======

## About

This project is designed to be a means for personal improvement in learning about different aspects of C programming and sockets. The Chatter  currently has the ability to chat over the web with access to profiles, usernames, passwords, and chat history. To use this project effectively, the server must be run on a computer accessible via a public IP address. This ip address should be written in the define statement in Client.c

### Server
When running the server code, the folder in which it is being run should be considered as the server database. Files such as the list of profiles, chat histories, etc. will be added to that folder.

### Client
The Client is a means to communicate with the server. The /profile command creates/deletes/selects a profile and shares it with the server, and the /message command connects a profile or instance of a profile to a chat.

#### Profiles
When a profile is created, a message indicating this will be sent to the server. The information being send is as follows: `create (profile name) (password)`. With this information, a profile will be made on the server.  

When a regular message is being sent, the initial information being sent is `(user id) (password)`. This is so that a socket can be paired to the id value in a *profile object*. Each sequential message sent afterwords will come in the form of `(user id - destination) (message)`. The message includes the text indicating the user writing the message, ie. `(user): message`.

### Future Steps
This is a slow growing project (developed in my free time) but has a few short term goals to build in subjects which I find interesting into the program
    1. Groups Chats
    2. Hashing Profiles on Server
    3. GUI
    4. Server Security
    5. Encrypted Messaging
    6. Direct Socket connection  
    7. Concurrency

### Security Issues
    1. Overloading call stack with /message command
    2. Making a large number of profiles
    3. Sending bandwidth breaking number of messages
    4. Invalid input arguments
    5. Limitation breaks in Client.c not reciprocated in Server.c (better Sync between the Client and the Server)




> Markdown uses email-style > characters for blockquoting.
