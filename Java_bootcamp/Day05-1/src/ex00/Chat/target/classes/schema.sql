CREATE TABLE IF NOT EXISTS users(
user_id INT PRIMARY KEY,
login VARCHAR(20) NOT NULL,
password VARCHAR(15) NOT NULL,
);

CREATE TABLE IF NOT EXISTS chat_room(
chat_room_id INT PRIMARY KEY,
name VARCHAR(20) NOT NULL,
owner REFERENCES user (user_id),
);

CREATE TABLE IF NOT EXISTS message (
message_id INT PRIMARY KEY,
author_message REFERENCES user (user_id) NOT NULL,
name_room REFERENCES chat_room (chat_room_id) NOT NULL,
text_message VARCHAR(1000),
date_time TIMESTAMP WITH TIME ZONE
);

CREATE TABLE IF NOT EXISTS users_chat_room(
user_id PRIMARY KEY REFERENCES chat_room (chat_room_id) NOT NULL,
chat_room_id PRIMARY KEY REFERENCES users (user_id) NOT NULL
)
