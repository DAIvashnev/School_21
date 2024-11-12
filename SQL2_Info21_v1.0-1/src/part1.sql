CREATE TABLE peers (
    nickname varchar primary key,
    birthday date not null
);

CREATE TABLE tasks (
    title       varchar primary key,
    parent_task varchar references tasks (title),
    max_xp      integer not null
);

ALTER TABLE tasks
    ADD CONSTRAINT ch_max_xp CHECK ( max_xp >= 0 );

CREATE TABLE checks (
    id   serial  primary key,
    peer varchar references peers (nickname),
    task varchar references tasks (title),
    date date
);

CREATE TYPE check_status AS ENUM ('start', 'success', 'failure');

CREATE TABLE p2p (
    id            serial       primary key,
    check_id      bigint       references checks (id),
    checking_peer varchar      references peers (nickname),
    status        check_status default 'start',
    time          time         without time zone
);

CREATE TABLE verter (
    id       serial    primary key,
    check_id bigint    references checks (id),
    status   check_status,
    time     time      without time zone
);

CREATE TABLE transferred_points (
    id            serial primary key,
    checking_peer varchar references peers (nickname),
    checked_peer  varchar references peers (nickname),
    points_amount integer
);

CREATE TABLE friends (
    id    serial  primary key,
    peer1 varchar references peers (nickname),
    peer2 varchar references peers (nickname)
);

CREATE TABLE recommendations (
    id               serial  primary key,
    peer             varchar references peers (nickname),
    recommended_peer varchar references peers (nickname)
);

CREATE TABLE xp (
    id        serial  primary key,
    check_id  bigint  references checks (id),
    xp_amount integer not null
);

ALTER TABLE xp
    ADD CONSTRAINT ch_xp_amount CHECK ( xp_amount >= 0 );

CREATE TYPE tracking_status AS ENUM ('login', 'logout');

CREATE TABLE time_tracking (
    id    serial          primary key,
    peer  varchar         references peers (nickname),
    date  date            not null,
    time  time            without time zone,
    state tracking_status default 'logout'
);


INSERT INTO peers (nickname, birthday)
VALUES ('warrynbo', '1994-04-20'),
       ('carrowsh', '1995-09-11'),
       ('malindac', '1996-04-21'),
       ('dashilow', '1997-11-13'),
       ('jeanicet', '2000-01-20'),
       ('fernando', '1999-01-15');

INSERT INTO tasks (title, parent_task, max_xp)
VALUES ('C1_SimpleBashUtils', null, 250),
       ('C2_s21_string+', 'C1_SimpleBashUtils', 500),
       ('C3_s21_decimal', 'C2_s21_string+', 350),
       ('C4_SmartCalc', 'C3_s21_decimal', 350),
       ('C5_3DViewer', 'C4_SmartCalc', 750),
       ('CPP1_matrixplus', 'C5_3DViewer', 250),
       ('CPP2_containers', 'CPP1_matrixplus', 300);

INSERT INTO checks (peer, task, date)
VALUES ('malindac', 'C1_SimpleBashUtils', '2023-04-20'),
       ('warrynbo', 'C1_SimpleBashUtils', '2023-04-21'),
       ('carrowsh', 'C1_SimpleBashUtils', '2023-04-22'),
       ('dashilow', 'C1_SimpleBashUtils', '2023-04-23'),
       ('warrynbo', 'C2_s21_string+', '2023-04-24'),
       ('malindac', 'C2_s21_string+', '2023-04-25'),
       ('dashilow', 'C2_s21_string+', '2023-04-26'),
       ('warrynbo', 'C3_s21_decimal', '2023-04-27'),
       ('dashilow', 'C3_s21_decimal', '2023-04-28'),
       ('carrowsh', 'C2_s21_string+', '2023-04-29'),
       ('jeanicet', 'C1_SimpleBashUtils', '2023-01-20'),
       ('jeanicet', 'C1_SimpleBashUtils', '2023-01-20');

INSERT INTO p2p (check_id, checking_peer, status, time)
VALUES (1, 'warrynbo', 'start', '13:00:00'),
       (1, 'warrynbo', 'success', '13:23:54'),
       (2, 'malindac', 'start', '14:45:00'),
       (2, 'malindac', 'success', '15:10:54'),
       (3, 'dashilow', 'start', '16:00:00'),
       (3, 'dashilow', 'success', '16:29:54'),
       (4, 'carrowsh', 'start', '11:30:00'),
       (4, 'carrowsh', 'success', '11:45:54'),
       (5, 'dashilow', 'start', '10:30:00'),
       (5, 'dashilow', 'success', '10:59:54'),
       (6, 'carrowsh', 'start', '11:32:00'),
       (6, 'carrowsh', 'success', '11:59:54'),
       (7, 'warrynbo', 'start', '07:10:00'),
       (7, 'warrynbo', 'success', '09:23:54'),
       (8, 'malindac', 'start', '16:21:00'),
       (8, 'malindac', 'success', '17:23:54'),
       (9, 'carrowsh', 'start', '12:51:00'),
       (9, 'carrowsh', 'success', '13:33:54'),
       (10, 'dashilow', 'start', '13:11:00'),
       (10, 'dashilow', 'success', '14:09:54'),
       (11, 'jeanicet', 'start', '13:11:00'),
       (11, 'jeanicet', 'failure', '14:09:54'),
       (12, 'jeanicet', 'start', '13:11:00'),
       (12, 'jeanicet', 'success', '14:09:54');

INSERT INTO verter (check_id, status, time)
VALUES (1, 'start', '13:24:00'),
       (1, 'success', '13:25:00'),
       (2, 'start', '15:11:00'),
       (2, 'success', '15:12:00'),
       (3, 'start', '16:30:00'),
       (3, 'success', '16:31:00'),
       (4, 'start', '11:46:00'),
       (4, 'success', '11:47:00'),
       (5, 'start', '11:00:00'),
       (5, 'success', '11:01:00'),
       (6, 'start', '12:00:00'),
       (6, 'success', '12:01:00'),
       (7, 'start', '09:24:00'),
       (7, 'success', '09:25:00'),
       (8, 'start', '17:24:00'),
       (8, 'success', '17:25:00'),
       (9, 'start', '13:34:00'),
       (9, 'failure', '13:35:00'),
       (10, 'start', '14:10:00'),
       (10, 'success', '14:11:00'),
       (12, 'start', '15:11:00'),
       (12, 'success', '16:09:54');

INSERT INTO transferred_points (checking_peer, checked_peer, points_amount)
VALUES ('malindac','warrynbo', 1),
       ('warrynbo', 'malindac', 1),
       ('carrowsh', 'dashilow', 1),
       ('dashilow', 'carrowsh', 1),
       ('warrynbo', 'dashilow', 1),
       ('malindac', 'carrowsh', 1),
       ('dashilow', 'warrynbo', 1),
       ('warrynbo', 'malindac', 1),
       ('dashilow', 'carrowsh', 1),
       ('carrowsh', 'dashilow', 1);

INSERT INTO friends (peer1, peer2)
VALUES ('warrynbo', 'malindac'),
       ('malindac', 'carrowsh'),
       ('carrowsh', 'dashilow'),
       ('fernando', 'malindac'),
       ('jeanicet', 'fernando');

INSERT INTO recommendations (peer, recommended_peer)
VALUES ('warrynbo', 'carrowsh'),
       ('malindac', 'dashilow'),
       ('dashilow', 'carrowsh'),
       ('fernando', 'malindac'),
       ('jeanicet', 'fernando'),
       ('warrynbo', 'jeanicet');

INSERT INTO xp (check_id, xp_amount)
VALUES (1, 231),
       (2, 245),
       (3, 225),
       (4, 245),
       (5, 485),
       (6, 500),
       (7, 495),
       (8, 350),
       (10, 500),
       (12, 247);
--        (12, 248);


INSERT INTO time_tracking (peer, date, time, state)
VALUES ('warrynbo', '2023-04-20', '12:05', 'login'),
       ('warrynbo', '2023-04-20', '16:23', 'logout'),
       ('warrynbo', '2023-04-20', '16:35', 'login'),
       ('warrynbo', '2023-04-20', '21:00', 'logout'),
       ('malindac', '2023-04-20', '16:35', 'login'),
       ('malindac', '2023-04-20', '21:00', 'logout'),
       ('malindac', '2023-04-21', '14:31', 'login'),
       ('malindac', '2023-04-21', '18:14', 'logout'),
       ('dashilow', '2023-04-22', '15:47', 'login'),
       ('dashilow', '2023-04-22', '21:02', 'logout'),
       ('jeanicet', '2023-05-20', '10:05', 'login'),
       ('jeanicet', '2023-05-20', '16:03', 'logout'),
       ('jeanicet', '2023-05-21', '15:05', 'login'),
       ('jeanicet', '2023-05-21', '19:02', 'logout');


CREATE OR REPLACE PROCEDURE export_to_csv(table_name TEXT, file_path TEXT, delimiter TEXT)
LANGUAGE plpgsql AS $$
BEGIN
    EXECUTE format('COPY %I TO %L WITH DELIMITER %L HEADER CSV;', table_name, file_path, delimiter);
END;
$$;

-- CALL export_to_csv('peers', '/tmp/peers.csv', ',');

CREATE OR REPLACE PROCEDURE import_from_csv(table_name TEXT, file_path TEXT, delimiter TEXT)
LANGUAGE plpgsql AS $$
BEGIN
    EXECUTE format('COPY %I FROM %L WITH DELIMITER %L HEADER CSV;', table_name, file_path, delimiter);
END;
$$;

-- TRUNCATE peers;
-- CALL import_from_csv('peers', '/tmp/peers.csv', ',');
-- SELECT * FROM peers;
