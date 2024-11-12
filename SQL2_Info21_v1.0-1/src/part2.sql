-- 1
CREATE OR REPLACE PROCEDURE add_p2p_record(
    p_checker_name varchar,
    p_checked_name varchar,
    p_task_name varchar,
    p_check_status check_status,
    p_time timestamp DEFAULT current_timestamp
)
    LANGUAGE plpgsql
AS
$$
DECLARE
    l_check_id bigint;
BEGIN
    IF p_check_status = 'start' THEN
        INSERT INTO checks (id, peer, task, date)
        VALUES ((SELECT max(id) + 1
                            AS id
                 FROM checks), p_checker_name, p_task_name, p_time::date)
        RETURNING id INTO l_check_id;
    ELSE
        SELECT max(id)
        INTO l_check_id
        FROM checks;
    END IF;

    INSERT INTO p2p (id, check_id, checking_peer, status, time)
    VALUES ((SELECT max(id) + 1
                        AS id
             FROM p2p), l_check_id, p_checked_name, p_check_status, p_time::time);
END;
$$;

-- 2
CREATE OR REPLACE PROCEDURE add_verter_check(
    p_nickname varchar,
    p_name_task varchar,
    p_check_status check_status,
    p_time timestamp default current_timestamp
)
LANGUAGE plpgsql
AS $$
DECLARE
    l_check_id bigint := (SELECT checks.id
                         FROM p2p
                         JOIN checks ON checks.id = p2p.check_id
                         AND p2p.status = 'success'
                         WHERE checks.task = p_name_task
                         AND checks.peer = p_nickname
                         ORDER BY checks.task DESC, p2p.time DESC
                                  LIMIT 1);
BEGIN
    IF (l_check_id IS NOT NULL) THEN
        INSERT INTO verter (id, check_id, status, time)
        VALUES ((SELECT max(id) + 1
            AS id FROM verter), l_check_id, p_check_status, p_time::time);
    END IF;
END;
$$;

-- tests cases for 1 & 2 parts
CALL add_p2p_record('fernando', 'jeanicet', 'C1_SimpleBashUtils', 'start');
CALL add_p2p_record('fernando', 'jeanicet', 'C1_SimpleBashUtils', 'success');
CALL add_p2p_record('jeanicet', 'fernando', 'C1_SimpleBashUtils', 'start');
CALL add_p2p_record('jeanicet', 'fernando', 'C1_SimpleBashUtils', 'success');

CALL add_verter_check('fernando', 'C1_SimpleBashUtils', 'start');
CALL add_verter_check('fernando', 'C1_SimpleBashUtils', 'success');
CALL add_verter_check('jeanicet', 'C1_SimpleBashUtils', 'start');
CALL add_verter_check('jeanicet', 'C1_SimpleBashUtils', 'success');

SELECT p.checking_peer, c.peer,
		p.check_id, p.status AS p2p_time, p.time,
		v.status AS v_status, v.time AS v_time
FROM p2p p
JOIN verter v ON p.check_id = v.check_id
JOIN checks c ON p.check_id = c.id
WHERE p.status = 'success'
	AND v.status IN ('success', 'failure')
ORDER BY c.date DESC;

-- Функция обновялющая количество очков у пиров в таблице transferred_points,
-- после добавления записи в таблицу p2p.
CREATE OR REPLACE FUNCTION fnc_trg_change_transferred_points() RETURNS trigger AS
$$
DECLARE
    checked_peer_nickname varchar;
BEGIN
    SELECT peer INTO checked_peer_nickname FROM checks WHERE id = NEW.check_id;
    IF NEW.status = 'start' THEN
        IF exists(SELECT *
                  FROM transferred_points
                  WHERE (checking_peer = (SELECT peer FROM checks WHERE id = 15))
                    AND (checked_peer = checked_peer_nickname)) THEN
            UPDATE transferred_points
            SET points_amount = points_amount + 1
            WHERE (checking_peer = NEW.checking_peer)
              AND (checked_peer = checked_peer_nickname);

            UPDATE transferred_points
            SET points_amount = points_amount - 1
            WHERE (checking_peer = checked_peer_nickname )
              AND (checked_peer = NEW.checking_peer);
        ELSE
            INSERT INTO transferred_points (checking_peer, checked_peer, points_amount)
            VALUES (NEW.checking_peer, checked_peer_nickname, 1),
                   (checked_peer_nickname, NEW.checking_peer, -1);
        END IF;
    END IF;

    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

-- Триггер изменяющий количество очков у проверяющего и проверяемого
-- во время старта проверки.
CREATE OR REPLACE TRIGGER trg_p2p_transfer
    AFTER INSERT
    ON p2p
    FOR EACH ROW
    WHEN ( NEW.status = 'start' )
EXECUTE FUNCTION fnc_trg_change_transferred_points();

CALL add_p2p_record('fernando', 'jeanicet', 'C2_s21_string+', 'start');
CALL add_p2p_record('fernando', 'jeanicet', 'C2_s21_string+', 'success');

-- Запись считается корректной, если:
--
-- Количество XP не превышает максимальное доступное для проверяемой задачи
-- Поле Check ссылается на успешную проверку
-- Если запись не прошла проверку, не добавлять её в таблицу.
CREATE OR REPLACE FUNCTION fnc_trg_xp_checking_added_experience() RETURNS trigger AS
$$
DECLARE
    xp_for_task bigint;
BEGIN
    SELECT DISTINCT t.max_xp
    INTO xp_for_task
    FROM checks c
             INNER JOIN tasks t on t.title = c.task
             INNER JOIN p2p p on c.id = p.check_id
             LEFT JOIN verter v on c.id = v.check_id
    WHERE p.status = 'success' AND (v.status IS NULL OR v.status = 'success')
      AND (c.id = NEW.check_id)
      AND (NEW.xp_amount <= t.max_xp);

    IF xp_for_task IS NOT null THEN
        RETURN NEW;
    ELSE
        RAISE NOTICE 'Некорректная вставка';
        RETURN NULL;
    end if;
END;
$$ LANGUAGE plpgsql;

-- Триггер проверяющий корректность при добавления данных в таблицу xp
CREATE OR REPLACE TRIGGER trg_xp_checking_add
    BEFORE INSERT
    ON xp
    FOR EACH ROW
EXECUTE FUNCTION fnc_trg_xp_checking_added_experience();

-- Опыт превышает максимальный для задачи
INSERT INTO xp (check_id, xp_amount)
VALUES (5, 2121);
-- Проваленная проверка (p2p)
INSERT INTO xp (check_id, xp_amount)
VALUES (11, 210);
-- Проваленная проверка (verter)
INSERT INTO xp (check_id, xp_amount)
VALUES (9, 210);
-- Корректная проверка
INSERT INTO xp (check_id, xp_amount)
VALUES (5, 210);
