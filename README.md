Terminal Chatter
=======

## About

This project is designed to be a means for personal improvement
in learning about different aspects of C programming and sockets. The Chatter  currently has the ability to chat over the web with access to profiles, usernames, passwords, and chat history.

In the Draft Folder:  

### Server
When running the server code, the folder in which it is being run should be considered as the server database. Files such as the list of profiles, chat histories, etc. will be added to that folder.

### Client


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
