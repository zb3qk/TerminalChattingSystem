typedef struct profile_s {
    char *name;
    int socket;
} profile;

typedef struct chat_s {
    int id;
    profile first;
    profile second;
} chat;
