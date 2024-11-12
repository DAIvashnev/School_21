-- 1 task
CREATE OR REPLACE PROCEDURE p4_drop_tables() 
LANGUAGE plpgsql 
AS $$
DECLARE
    table_name text;
BEGIN
    FOR table_name IN 
		SELECT t.table_name 
		FROM information_schema.tables AS t 
		WHERE t.table_schema = current_schema()
		AND t.table_name LIKE 'tablename%'
	LOOP
        EXECUTE 'DROP TABLE IF EXISTS ' || quote_ident(table_name) || ' CASCADE';
    END LOOP;
END;
$$;

-- test for 1
CREATE TABLE TableName1 (id serial primary key, name text);
CREATE TABLE TableName2 (id serial primary key, name text);

SELECT table_name FROM information_schema.tables WHERE table_schema = current_schema();

CALL p4_drop_tables();

SELECT table_name FROM information_schema.tables WHERE table_schema = current_schema();


-- 2 task
CREATE OR REPLACE PROCEDURE p4_count_table(OUT n int)
AS
$$
BEGIN
    n = (SELECT count(*)
         FROM (SELECT routines.routine_name, parameters.data_type
               FROM information_schema.routines
                        LEFT JOIN information_schema.parameters ON routines.specific_name = parameters.specific_name
               WHERE routines.specific_schema = 'public'
                 AND parameters.data_type IS NOT NULL
               ORDER BY routines.routine_name, parameters.ordinal_position) as foo);
END
$$ LANGUAGE plpgsql;

-- test for 2
DO
$$
    DECLARE
        res integer;
    BEGIN
        CALL p4_count_table(res);
        RAISE NOTICE 'Num %', res;
    END
$$;


-- 3 task
CREATE OR REPLACE PROCEDURE p4_delete_dml_triggers(IN ref refcursor, INOUT result int)
AS
$$
BEGIN
    FOR ref IN
        SELECT trigger_name || ' ON ' || event_object_table
        FROM information_schema.triggers
        WHERE trigger_schema = 'public'
        LOOP
            EXECUTE 'DROP TRIGGER ' || ref;
            result := result + 1;
        END LOOP;
END
$$ LANGUAGE plpgsql;

-- test for 3
CALL p4_delete_dml_triggers('cursor_name', 0);

SELECT trigger_name
FROM information_schema.triggers;


--4 task
CREATE OR REPLACE PROCEDURE p4_show_info(IN ref refcursor, IN name text)
AS
$$
BEGIN
    OPEN ref FOR
        SELECT routine_name,
               routine_type,
               routine_definition
        FROM information_schema.routines
        WHERE specific_schema = 'public'
          AND routine_definition LIKE '%' || name || '%';
END
$$ LANGUAGE plpgsql;

-- test for 4
CALL p4_show_info('cursor_name', 'date');
FETCH ALL IN "cursor_name";
