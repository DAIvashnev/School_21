INSERT INTO users (user_id, login, password) VALUES (DEFAULT, 'enedinae', '123456');
INSERT INTO users (user_id, login, password) VALUES (DEFAULT, 'iivdmal', '123456');
INSERT INTO users (user_id, login, password) VALUES (DEFAULT, 'login', '123456');
INSERT INTO users (user_id, login, password) VALUES (DEFAULT, 'kek', '123456');
INSERT INTO users (user_id, login, password) VALUES (DEFAULT, 'five', '123456');

INSERT INTO chat_room (chat_room_id, name, owner) VALUES (DEFAULT, 'job', 1);
INSERT INTO chat_room (chat_room_id, name, owner) VALUES (DEFAULT, 'sport', 2);
INSERT INTO chat_room (chat_room_id, name, owner) VALUES (DEFAULT, 'school', 3);
INSERT INTO chat_room (chat_room_id, name, owner) VALUES (DEFAULT, 'ufc', 3);
INSERT INTO chat_room (chat_room_id, name, owner) VALUES (DEFAULT, 'flud', 4);

INSERT INTO message (message_id, author_message, name_room, text_message, date_time) VALUES (DEFAULT, 1, 2, 'Hard Work nigga', '2023-09-01 08:30');
INSERT INTO message (message_id, author_message, name_room, text_message, date_time) VALUES (DEFAULT, 2, 3, 'Im winner', '2023-07-17 09:30');
INSERT INTO message (message_id, author_message, name_room, text_message, date_time) VALUES (DEFAULT, 3, 4, 'SUCCESS', '2023-07-24 12:00');
INSERT INTO message (message_id, author_message, name_room, text_message, date_time) VALUES (DEFAULT, 4, 5, 'AAAAAND STEEEEL', '2023-10-23 23:10');
INSERT INTO message (message_id, author_message, name_room, text_message, date_time) VALUES (DEFAULT, 5, 6, 'eshkere', '2023-01-01 06:00');

INSERT INTO users_chat_room (user_id, chat_room_id) VALUES (1, 2);
INSERT INTO users_chat_room (user_id, chat_room_id) VALUES (2, 3);
INSERT INTO users_chat_room (user_id, chat_room_id) VALUES (3, 4);
INSERT INTO users_chat_room (user_id, chat_room_id) VALUES (4, 5);
INSERT INTO users_chat_room (user_id, chat_room_id) VALUES (5, 6);
