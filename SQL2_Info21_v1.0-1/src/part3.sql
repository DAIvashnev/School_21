
-- Вопрос об использовании функций вместо процедур когда нужно вернуть значения в pedago:
-- (https://rocketchat-student.21-school.ru/channel/pedago_21?msg=aAj6ATa7RQZgatdZh)
--
-- В нем оставлена реакция p2p. Поэтому для возвращаемых значений мы не передаем дополнительный
-- курсор в процедуру, а вместо этого используем функции.

-- 1) Написать функцию, возвращающую таблицу TransferredPoints в более человекочитаемом виде
-- Ник пира 1, ник пира 2, количество переданных пир поинтов.
-- Количество отрицательное, если пир 2 получил от пира 1 больше поинтов.

-- Data for checking the result of the task
-- INSERT INTO transferred_points (checking_peer, checked_peer, points_amount)
-- VALUES (1, 'warrynbo', 'malindac', 5),
--         (2, 'malindac', 'carrowsh', 2),
--         (3, 'carrowsh', 'malindac', 4),
--         (4, 'chubumba', 'warrynbo', 1),
--         (5, 'warrynbo', 'chubumba', 1),
--         (6, 'dashilow', 'chubumba', 1);

DROP FUNCTION IF EXISTS transferred_points_human_readable();

CREATE OR REPLACE FUNCTION transferred_points_human_readable()
RETURNS TABLE (
        peer1         VARCHAR,
        peer2         VARCHAR,
        points_amount INTEGER
) AS $$
BEGIN
RETURN QUERY
SELECT checking_peer AS peer1,
        checked_peer AS peer2,
        CASE
            WHEN
                (
                SELECT DISTINCT tp2.points_amount
                FROM transferred_points AS tp2
                WHERE checking_peer = tp1.checked_peer
                AND checked_peer = tp1.checking_peer
                ) > tp1.points_amount
            THEN
                tp1.points_amount * -1
            ELSE
                tp1.points_amount
            END
FROM transferred_points AS tp1;
END;
$$ LANGUAGE plpgsql;

-- Тестовый запрос.
SELECT *
FROM transferred_points_human_readable();

-- 2) Написать функцию, которая возвращает таблицу вида: ник пользователя,
-- название проверенного задания, кол-во полученного XP
--
-- В таблицу включать только задания, успешно прошедшие проверку (определять по таблице Checks).
-- Одна задача может быть успешно выполнена несколько раз. В таком случае в
-- таблицу включать все успешные проверки.

-- Data for checking the result of the task
-- INSERT INTO checks (id, peer, task, date)
-- VALUES (1, 'malindac', 'C2_s21_stringplus-0', '2023-04-20 13:00:00'),
--        (2, 'malindac', 'CPP2_containers', '2023-04-22 16:00:00'),
--        (3, 'warrynbo', 'C3_SimpleBashUtils-0', '2023-04-21 14:45:00'),
--        (4, 'chubumba', 'CPP1_s21_matrixplus-1', '2023-04-24 10:30:00'),
--        (5, 'dashilow', 'D01_Linux-0', '2023-04-24 10:30:00'),
--        (6, 'carrowsh', 'DO5_SimpleDocker-0', '2023-04-24 10:30:00'),
--        (7, 'derevyanka', 'DO3_LinuxMonitoring_v1.0-0', '2023-04-24 10:30:00');

DROP FUNCTION IF EXISTS successfully_checked_tasks();

CREATE OR REPLACE FUNCTION successfully_checked_tasks()
	RETURNS TABLE (
	    Peer VARCHAR,
	    Task VARCHAR,
	    XP   INTEGER)
    AS $$
BEGIN
	RETURN QUERY (
    SELECT checks.peer   AS nickname,
            checks.task  AS checked_task,
            xp.xp_amount AS got_xp
    FROM xp
    JOIN checks ON xp.check_id = checks.id
    ORDER BY checked_task
	);
END;
$$ LANGUAGE plpgsql;

-- Тестовый запрос.
SELECT *
FROM successfully_checked_tasks();

-- 3) Написать функцию, определяющую пиров, которые не выходили из кампуса в течение всего дня
-- Параметры функции: день, например 12.05.2022.
-- Функция возвращает только список пиров.

DROP FUNCTION IF EXISTS check_date(peer_date date);

CREATE OR REPLACE FUNCTION check_date(peer_date date)
    RETURNS TABLE
            (
                login varchar
            )
AS
$$
BEGIN
    RETURN QUERY
    SELECT peer AS login
    FROM time_tracking
    WHERE date = peer_date
    GROUP BY peer
    HAVING COUNT(
                   CASE
                       WHEN state = 'logout'
                           THEN 1
                       END) = 0;
END;
$$ LANGUAGE plpgsql;

-- Тестовый запрос.
SELECT *
FROM check_date('2023-04-22');

-- 4) Посчитать изменение в количестве пир поинтов каждого пира по таблице TransferredPoints
-- Результат вывести отсортированным по изменению числа поинтов.
-- Формат вывода: ник пира, изменение в количество пир поинтов

DROP FUNCTION IF EXISTS peer_points_change();

CREATE OR REPLACE FUNCTION peer_points_change()
RETURNS TABLE (
    peer VARCHAR,
    points_change BIGINT)
AS
$$
BEGIN
    RETURN QUERY
WITH checking AS (
    SELECT checking_peer AS peer, SUM(points_amount) AS points_change
    FROM transferred_points
    GROUP BY checking_peer
), checked AS (
    SELECT checked_peer AS peer, SUM(points_amount) AS points_change
    FROM transferred_points
    GROUP BY checked_peer
)
SELECT checking.peer, checking.points_change - COALESCE(checked.points_change, 0) AS points_change
FROM checking
LEFT JOIN checked ON checking.peer = checked.peer
WHERE checked.peer IS NULL
   OR (checking.peer IS NOT NULL AND checked.peer IS NOT NULL)
ORDER BY points_change DESC;
END;
$$ LANGUAGE plpgsql;

-- Тестовая транзакция.
SELECT *
FROM peer_points_change();

-- 5) Посчитать изменение в количестве пир поинтов каждого пира по таблице,
-- возвращаемой первой функцией из Part 3
--
-- Результат вывести отсортированным по изменению числа поинтов.
-- Формат вывода: ник пира, изменение в количество пир поинтов

DROP FUNCTION IF EXISTS result_prp_with_human_readable_func();

CREATE OR REPLACE FUNCTION result_prp_with_human_readable_func()
RETURNS TABLE (
    peer VARCHAR,
    points_change bigint) AS
$$
    BEGIN
    RETURN QUERY
    WITH normalize AS (
        SELECT *, CASE
                    WHEN points_amount < 0
                    THEN
                        points_amount * (-1)
                    ELSE
                        points_amount
                    END AS renew_points_amount
        FROM transferred_points_human_readable()
    ),
    checking_peer AS (
        SELECT peer1, SUM(renew_points_amount) AS peer1_points
        FROM normalize
        GROUP BY peer1
    ),
    checked_peer AS (
        SELECT peer2, SUM(renew_points_amount) AS peer2_points
        FROM normalize
        GROUP BY peer2)
    SELECT COALESCE (peer1, peer2) AS peer, ((COALESCE(peer1_points, 0)) - (COALESCE(peer2_points, 0))) AS points_change
    FROM (SELECT *
          FROM checking_peer FULL JOIN checked_peer
                             ON peer1 = peer2) AS full_tab
    ORDER BY points_change;
    END;
$$ LANGUAGE plpgsql;

SELECT *
FROM result_prp_with_human_readable_func();

-- Task 6. Определить самое часто проверяемое задание за каждый день
-- При одинаковом количестве проверок каких-то заданий в определенный день, вывести их все.
-- Формат вывода: день, название задания

-- INSERT INTO checks (id, peer, task, date)
-- VALUES (7, 'warrynbo', 'CPP1_matrixplus', '2023-04-20 13:00:00'),
--        (8, 'malindac', 'CPP1_matrixplus', '2023-04-20 14:45:00');
-- INSERT INTO checks (id, peer, task, date)
-- VALUES (9, 'warrynbo', 'CPP2_containers', '2023-04-20 23:00:00'),
--        (10, 'malindac', 'CPP2_containers', '2023-04-20 23:45:00');

DROP FUNCTION IF EXISTS get_most_checked_task_per_day();

CREATE OR REPLACE FUNCTION get_most_checked_task_per_day()
    RETURNS TABLE
            (
                day  date,
                task varchar
            )
AS
$$
WITH count_checks AS (SELECT date(date)                        AS day,
                             split_part(task, '_', 1)::varchar AS task,
                             count(*)                          AS cou
                      FROM checks
                      GROUP BY task, day),
     max_day AS (SELECT day,
                        max(cou) AS max_on_day
                 FROM count_checks
                 GROUP BY day)
SELECT count_checks.day as day,
       count_checks.task
FROM max_day
         INNER JOIN count_checks ON max_day.day = count_checks.day AND
                                    count_checks.cou = max_day.max_on_day
ORDER BY count_checks.day DESC;
$$ LANGUAGE sql;

SELECT *
FROM get_most_checked_task_per_day();

-- 7) Найти всех пиров, выполнивших весь заданный блок задач и дату завершения последнего задания
-- Параметры: название блока, например "CPP".
-- Результат вывести отсортированным по дате завершения.
-- Формат вывода: ник пира, дата завершения блока (т.е. последнего
-- выполненного задания из этого блока)

-- INSERT INTO checks (peer, task, date)
-- VALUES ('jeanicet', 'C1_SimpleBashUtils', '2023-04-20'),
--        ('jeanicet', 'C2_s21_string+', '2023-04-21'),
--        ('jeanicet', 'C3_s21_decimal', '2023-04-22'),
--        ('jeanicet', 'C4_SmartCalc', '2023-04-23'),
--        ('jeanicet', 'C5_3DViewer+', '2023-04-25'),
--        ('jeanicet', 'C5_3DViewer+', '2023-04-26 ');
--
-- INSERT INTO p2p (check_id, checking_peer, status, time)
-- VALUES (11, 'jeanicet', 'start', '13:00:00'),
--        (11, 'jeanicet', 'success', '13:23:54'),
--        (12, 'jeanicet', 'start', '14:45:00'),
--        (12, 'jeanicet', 'success', '15:10:54'),
--        (13, 'jeanicet', 'start', '16:00:00'),
--        (13, 'jeanicet', 'success', '16:29:54'),
--        (14, 'jeanicet', 'start', '11:30:00'),
--        (14, 'jeanicet', 'success', '11:45:54'),
--        (15, 'jeanicet', 'start', '11:30:00'),
--        (15, 'jeanicet', 'success', '11:45:54'),
--        (16, 'jeanicet', 'start', '10:30:00'),
--        (16, 'jeanicet', 'success', '10:59:54');

DROP FUNCTION IF EXISTS get_completed_peers(block_title VARCHAR);

CREATE OR REPLACE FUNCTION get_completed_peers(block_title VARCHAR)
    RETURNS TABLE
            (
                peer varchar,
                day  date
            )
AS
$$
WITH peer_tasks AS (SELECT peer, task, date(MAX(c.date)) AS max_date
                    FROM p2p p
                             INNER JOIN checks c ON p.check_id = c.id
                             LEFT JOIN verter v on c.id = v.check_id
                    WHERE p.status = 'success' AND (v.status IS NULL OR v.status = 'success')
                      AND split_part(task, '_', 1) LIKE (block_title || '_')
                    GROUP BY peer, task)
SELECT peer, max(max_date) AS day
FROM peer_tasks
GROUP BY peer
HAVING count(task) = (SELECT count(title)
                      FROM tasks
                      WHERE split_part(title, '_', 1) LIKE (block_title || '_'))
ORDER BY day DESC;
$$ LANGUAGE sql;

SELECT *
FROM get_completed_peers('C');

-- 8) Определить, к какому пиру стоит идти на проверку каждому обучающемуся
-- Определять нужно исходя из рекомендаций друзей пира, т.е. нужно найти пира,
-- проверяться у которого рекомендует наибольшее число друзей.
-- Формат вывода: ник пира, ник найденного проверяющего
-- вводим на вход имя пира и оставляем только реки друзей и выводим наиболее частое

-- INSERT INTO recommendations (id, peer, recommended_peer)
-- VALUES (1, 'warrynbo', 'carrowsh'),
--        (2, 'malindac', 'dashilow'),
--        (3, 'dashilow', 'chubumba'),
--        (4, 'derevyanka', 'carrowsh'),
--        (5, 'chubumba', 'warrynbo'),
-- (6, 'malindac', 'chubumba'),
-- (7, 'warrynbo', 'chubumba'),
-- (8, 'derevyanka', 'chubumba');
--
-- INSERT INTO friends (id, peer1, peer2)
-- VALUES (1, 'warrynbo', 'malindac'),
--        (2, 'dashilow', 'carrowsh'),
--        (3, 'malindac', 'chubumba'),
--        (4, 'carrowsh', 'derevyanko'),
--        (5, 'chubumba', 'warrynbo'),
--        (6, 'carrowsh', 'warrynbo'),
--        (7, 'carrowsh', 'malindac');

DROP FUNCTION IF EXISTS get_most_recommended_peer(IN peer VARCHAR, OUT recommended_peer VARCHAR);

CREATE OR REPLACE FUNCTION get_most_recommended_peer(IN checking_peer VARCHAR)
    RETURNS TABLE (
        peer VARCHAR,
        recommended_peer VARCHAR )
AS
$$
BEGIN
    RETURN QUERY
        WITH all_friends AS (
            SELECT peer1, peer2
            FROM friends
            UNION
            SELECT peer2, peer1
            FROM friends
--             ORDER BY peer1, peer2  -- выведем все пары друзей с 2-х сторон
        ),
        choose_friend AS (
            SELECT all_friends.peer2
            FROM all_friends
            WHERE all_friends.peer1 = checking_peer -- выведи всех друзей чела из инпута
        ),
        choose_rec AS (
        SELECT ar.peer AS peer, ar.recommended_peer
        FROM recommendations AS ar
        WHERE ar.peer IN (SELECT cf.peer2 FROM choose_friend AS cf)
          AND (ar.recommended_peer NOT LIKE checking_peer)
        )
        SELECT t.peer, t.recommended_peer
        FROM (
            SELECT cr.peer, cr.recommended_peer, COUNT(*) OVER (PARTITION BY cr.recommended_peer) AS frequency
            FROM choose_rec AS cr
             ) t
        ORDER BY t.frequency DESC;
END;
$$ LANGUAGE plpgsql;

SELECT *
FROM get_most_recommended_peer('carrowsh');

-- 9) Определить процент пиров, которые:
-- Приступили только к блоку 1
-- Приступили только к блоку 2
-- Приступили к обоим
-- Не приступили ни к одному
--
-- Пир считается приступившим к блоку, если он проходил хоть одну проверку любого
-- задания из этого блока (по таблице Checks)
-- Параметры: название блока 1, например SQL, название блока 2, например A.
-- Формат вывода: процент приступивших только к первому блоку, процент приступивших только
-- ко второму блоку, процент приступивших к обоим, процент не приступивших ни к одному
-- StartedBlock1
-- StartedBlock2
-- StartedBothBlocks
-- DidntStartAnyBlock

-- INSERT INTO checks (id, peer, task, date)
-- VALUES (1, 'malindac', 'C2_s21_stringplus-0', '2023-04-20 13:00:00'),
--        (2, 'malindac', 'CPP2_containers', '2023-04-22 16:00:00'),
--        (3, 'warrynbo', 'C3_SimpleBashUtils-0', '2023-04-21 14:45:00'),
--        (4, 'chubumba', 'CPP1_s21_matrixplus-1', '2023-04-24 10:30:00'),
--        (5, 'dashilow', 'D01_Linux-0', '2023-04-24 10:30:00'),
--        (6, 'carrowsh', 'DO5_SimpleDocker-0', '2023-04-24 10:30:00'),
--        (7, 'derevyanka', 'DO3_LinuxMonitoring_v1.0-0', '2023-04-24 10:30:00');

DROP FUNCTION IF EXISTS check_blocks(starting_letter_1 VARCHAR, starting_letter_2 VARCHAR);

CREATE OR REPLACE FUNCTION check_blocks(starting_letter_1 VARCHAR, starting_letter_2 VARCHAR)
    RETURNS TABLE
            (
                StartedBlock1      BIGINT,
                StartedBlock2      BIGINT,
                StartedBothBlocks  BIGINT,
                DidntStartAnyBlock BIGINT
            )
AS
$$
DECLARE
-- отдельно посчитала сумму всех строк данных для 100 процентов
    common_number BIGINT := (SELECT COUNT(*)
                             FROM (SELECT DISTINCT ch.peer FROM checks AS ch) AS t);
BEGIN
    RETURN QUERY
        WITH started_block1 AS (SELECT DISTINCT peer
                                FROM checks
                                WHERE checks.task SIMILAR TO CONCAT(starting_letter_1, '[0-9]_%')),
             started_block2 AS (SELECT DISTINCT peer
                                FROM checks
                                WHERE checks.task SIMILAR TO CONCAT(starting_letter_2, '[0-9]_%')),
             started_both AS (SELECT DISTINCT started_block1.peer
                              FROM started_block1
                                       JOIN started_block2 ON started_block1.peer = started_block2.peer),
             didnt_start_any AS (SELECT DISTINCT checks.peer
                                 FROM checks
                                 EXCEPT
                                 SELECT DISTINCT sbb.peer
                                 FROM (SELECT peer
                                       FROM started_block1
                                       UNION
                                       SELECT peer
                                       FROM started_block2) AS sbb),
--     отдельно посчитала сумму для каждой из таблиц, выведенных ниже
             count_started_block1 AS (SELECT COUNT(*) AS count_started_block1
                                      FROM started_block1),
             count_started_block2 AS (SELECT COUNT(*) AS count_started_block2
                                      FROM started_block2),
             count_started_both AS (SELECT COUNT(*) AS count_started_both
                                    FROM started_both),
             count_didnt_start_any AS (SELECT COUNT(*) AS count_didnt_start_any
                                       FROM didnt_start_any)
--     -- отдельно селектом нашла проценты для каждого столбца
        SELECT ((SELECT count_started_block1::BIGINT
                 FROM count_started_block1) * 100 / common_number)  AS StartedBlock1,
               ((SELECT count_started_block2::BIGINT
                 FROM count_started_block2) * 100 / common_number)  AS StartedBlock2,
               ((SELECT count_started_both::BIGINT
                 FROM count_started_both) * 100 / common_number)    AS StartedBothBlocks,
               ((SELECT count_didnt_start_any::BIGINT
                 FROM count_didnt_start_any) * 100 / common_number) AS DidntStartAnyBlock;
END
$$ LANGUAGE plpgsql;

SELECT *
FROM check_blocks('C', 'CPP');


-- 10) Определить процент пиров, которые когда-либо успешно проходили проверку в свой день рождения
-- Также определите процент пиров, которые хоть раз проваливали проверку в свой день рождения.
-- Формат вывода: процент пиров, успешно прошедших проверку в день рождения, процент пиров,
-- проваливших проверку в день рождения

DROP FUNCTION IF EXISTS calculate_birthday_check_percentages();

CREATE OR REPLACE FUNCTION calculate_birthday_check_percentages()
    RETURNS TABLE (
        "SuccessfulChecks"   numeric,
        "UnsuccessfulChecks" numeric
    )
AS $$
DECLARE
    count_peers integer := (SELECT count(*) FROM peers);
BEGIN
    RETURN QUERY
        WITH p2p_checks AS (
            SELECT check_id, status
            FROM p2p
            WHERE status IN ('failure', 'success')
        ),
        verter_checks AS (
            SELECT check_id, status
            FROM verter
            WHERE status IN ('failure', 'success')
        ),
        all_checks AS (
            SELECT pe.nickname,
                CASE
                    WHEN p.status = 'success' AND (v.status IS NULL OR v.status = 'success')
                        THEN 'success'
                    WHEN p.status = 'failure' OR (p.status = 'success' AND v.status = 'failure')
                        THEN 'failure'
                END AS status
            FROM peers pe
            JOIN checks c ON pe.nickname = c.peer
            JOIN p2p_checks p ON c.id = p.check_id
            LEFT JOIN verter_checks v ON c.id = v.check_id
            WHERE extract(MONTH FROM pe.birthday) = extract(MONTH FROM c.date)
                AND extract(DAY FROM pe.birthday) = extract(DAY FROM c.date)
        ),
        checks_data AS (
            SELECT nickname, status
            FROM all_checks
            GROUP BY nickname, status
        )
        SELECT
            ROUND(COUNT(CASE WHEN status = 'success' THEN 1 END) * 100.0 /
                  count_peers, 2) AS "SuccessfulChecks",
            ROUND(COUNT(CASE WHEN status = 'failure' THEN 1 END) * 100.0 /
                  count_peers, 2) AS "UnsuccessfulChecks"
        FROM checks_data;
END
$$ LANGUAGE plpgsql;

--  test for 10
SELECT * FROM calculate_birthday_check_percentages();

-- 11) Определить всех пиров, которые сдали заданные задания 1 и 2, но не сдали задание 3
-- Параметры: названия заданий 1, 2 и 3.
-- Формат вывода: список пиров

DROP FUNCTION IF EXISTS find_peers_on_tasks(task1 VARCHAR, task2 VARCHAR, task3 VARCHAR);

CREATE OR REPLACE FUNCTION find_peers_on_tasks(task1 VARCHAR, task2 VARCHAR, task3 VARCHAR)
RETURNS SETOF VARCHAR
AS
$$
BEGIN
    RETURN QUERY
    SELECT t.nickname AS peer
    FROM (SELECT nickname,
                 count(DISTINCT CASE WHEN c.task = task1 THEN 1 END) AS first_task,
                 count(DISTINCT CASE WHEN c.task = task2 THEN 1 END) AS second_task,
                 count(DISTINCT CASE WHEN c.task = task3 THEN 1 END) AS third_task
          FROM peers pe
                  JOIN checks c on pe.nickname = c.peer
                  JOIN p2p p on c.id = p.check_id
                  LEFT JOIN verter v on c.id = v.check_id
          WHERE p.status = 'success' AND (v.status IS NULL OR v.status = 'success')
          GROUP BY nickname) t
    WHERE first_task = 1
      AND second_task = 1
      AND third_task != 1;
END
$$ LANGUAGE plpgsql;

-- tests for 11
SELECT find_peers_on_tasks('C1_SimpleBashUtils', 'C2_s21_string+', 'C4_SmartCalc');

SELECT find_peers_on_tasks('C1_SimpleBashUtils', 'C3_s21_decimal', 'C5_3DViewer');

-- 12) Используя рекурсивное обобщенное табличное выражение, для каждой
-- задачи вывести кол-во предшествующих ей задач
--
-- То есть сколько задач нужно выполнить, исходя из условий входа,
-- чтобы получить доступ к текущей.
-- Формат вывода: название задачи, количество предшествующих
DROP FUNCTION IF EXISTS get_prev_count();

CREATE OR REPLACE FUNCTION get_prev_count()
RETURNS TABLE(task varchar, prev_count int)
AS
$$
DECLARE
    _task varchar;
    _prev_count int;
BEGIN
    FOR _task, _prev_count IN
        WITH RECURSIVE prev_tasks AS (
            SELECT t.title AS t_title, 0 AS p_prev_count
            FROM tasks t
            WHERE t.parent_task IS NULL
            UNION
            SELECT t.title AS t_title, prev_tasks.p_prev_count + 1 AS p_prev_count
            FROM tasks t
            JOIN prev_tasks ON t.parent_task = prev_tasks.t_title
        )
        SELECT t_title, p_prev_count
        FROM prev_tasks
        ORDER BY p_prev_count DESC
    LOOP
    RETURN QUERY
		SELECT _task, _prev_count;
    END LOOP;
END;
$$ LANGUAGE plpgsql;

-- test for 12
SELECT * FROM get_prev_count();

-- 13) Найти "удачные" для проверок дни. День считается "удачным",
-- если в нем есть хотя бы N идущих подряд успешных проверки
--
-- Параметры: количество идущих подряд успешных проверок N.
-- Временем проверки считать время начала P2P этапа.
-- Под идущими подряд успешными проверками подразумеваются успешные проверки,
-- между которыми нет неуспешных.
-- При этом кол-во опыта за каждую из этих проверок должно быть не меньше 80% от максимального.
-- Формат вывода: список дней

CREATE OR REPLACE FUNCTION lucky_day(N int)
    RETURNS TABLE (
        date_check         date
) AS
$$
BEGIN
    RETURN QUERY
        WITH t1 AS (SELECT c.date      AS date_ch,
                           t.max_xp    AS max_xp,
                           x.xp_amount AS peer_get_xp
                    FROM checks c
                             INNER JOIN p2p on c.id = p2p.check_id AND (p2p.status = 'success')
                             INNER JOIN verter v on c.id = v.check_id AND (v.status = 'success')
                             INNER JOIN xp x on c.id = x.check_id
                             INNER JOIN tasks t on c.task = t.title
                    ORDER BY date)
        SELECT date_ch AS date_check
        FROM t1
        WHERE t1.peer_get_xp > t1.max_xp * 0.8
        GROUP BY date_ch
        HAVING count(date_ch) >= N;
END;
$$ LANGUAGE plpgsql;

-- test for 13
SELECT * FROM lucky_day(2);

-- 14) Определить пира с наибольшим количеством XP
-- Формат вывода: ник пира, количество XP
CREATE OR REPLACE FUNCTION max_done_task()
    RETURNS TABLE
            (
                peer varchar,
                xp   bigint
            )
AS
$$
BEGIN
    return query
        SELECT c.peer as peer,
               sum(xp_amount) xp
        FROM xp
                 INNER JOIN checks c on c.id = xp.check_id
        GROUP BY c.peer
        ORDER BY xp DESC
        LIMIT 1;
END;
$$ LANGUAGE plpgsql;

SELECT * FROM max_done_task();

-- 15) Определить пиров, приходивших раньше заданного времени не менее N раз за всё время
-- Параметры: время, количество раз N.
-- Формат вывода: список пиров

-- INSERT INTO time_tracking (id, peer, date, time, state)
-- VALUES (1, 'warrynbo', '2023-04-20', '12:05', 1),
--        (2, 'warrynbo', '2023-04-20', '16:23', 2),
--        (3, 'warrynbo', '2023-04-20', '17:05', 1),
--        (4, 'warrynbo', '2023-04-20', '18:05', 2),
--        (5, 'chubumba', '2023-04-21', '14:31', 1),
--        (6, 'dashilow', '2023-04-22', '15:47', 1),
--        (7, 'chubumba', '2023-04-22', '15:40', 1),
--        (8, 'chubumba', '2023-05-12', '12:05', 1),
--        (9, 'fernando', '2023-06-12', '18:05', 1),
--        (10, 'malindac', '2023-07-01', '18:05', 2),
--        (11, 'warbirdo', '2023-06-30', '18:05', 2),
--        (12, 'neelyrha', '2023-06-29', '18:05', 2),
--        (13, 'enedinae', '2023-06-28', '18:05', 2),
--        (14, 'malindac', '2023-07-01', '19:05', 2),
--        (15, 'malindac', '2023-07-01', '20:05', 2),
--        (16, 'fernando', '2023-07-01', '20:05', 2);

DROP FUNCTION IF EXISTS check_time_coming(time_come TIME, N INT);

CREATE OR REPLACE FUNCTION check_time_coming(time_come TIME, N INT)
    RETURNS TABLE (
        peer varchar
                  )
AS $$
BEGIN
    RETURN QUERY
    SELECT tt.peer
    FROM time_tracking tt
    WHERE tt.time < time_come AND tt.state = 'login'
    GROUP BY tt.peer
    HAVING COUNT(*) >= N;
END;
$$ LANGUAGE plpgsql;

SELECT *
FROM check_time_coming('19:47:00', 2);

-- 16) Определить пиров, выходивших за последние N дней из кампуса больше M раз
-- Параметры: количество дней N, количество раз M.
-- Формат вывода: список пиров

CREATE OR REPLACE FUNCTION check_come_out(N INT, M INT)
    RETURNS TABLE (
        peer varchar
                  )
AS $$
BEGIN
    RETURN QUERY
    SELECT peer_table.peer
    FROM (
        SELECT tt.peer, tt.date, count(*) AS counts
        FROM time_tracking tt
        WHERE tt.state = 'logout' AND tt.date > (current_date - N) -- искать за последние N дней
        GROUP BY tt.peer, tt.date
        ORDER BY tt.date
         ) AS peer_table
    GROUP BY peer_table.peer
    HAVING SUM(peer_table.counts) > M;
END;
$$ LANGUAGE plpgsql;

SELECT *
FROM check_come_out(100, 1);

-- 17) Определить для каждого месяца процент ранних входов
-- Формат вывода: Таблица статистики для месяцев в которые были посещения

CREATE OR REPLACE FUNCTION calculate_early_entries_percentage()
    RETURNS TABLE
            (
                "Month"        VARCHAR,
                "EarlyEntries" NUMERIC
            )
AS
$$
WITH peers_data AS (SELECT nickname,
                           birthday
                    FROM peers
                    ORDER BY EXTRACT(MONTH FROM birthday)),
     peers_enter_time AS (SELECT peer,
                                 EXTRACT(HOUR FROM time) < 12 AS is_early_enter
                          FROM time_tracking
                          WHERE state = 'login')
SELECT to_char(to_date(CAST(EXTRACT(MONTH FROM birthday) AS VARCHAR), 'MM'), 'Month') AS "Month",
       COUNT(CASE WHEN is_early_enter THEN 1 END) * 100.0 / COUNT(*)                  AS "EarlyEntries"
FROM peers_data AS pd
         INNER JOIN peers_enter_time AS pe ON pd.nickname = pe.peer
GROUP BY EXTRACT(MONTH FROM birthday);
$$ LANGUAGE sql;

--  test for 17
SELECT *
FROM calculate_early_entries_percentage();
