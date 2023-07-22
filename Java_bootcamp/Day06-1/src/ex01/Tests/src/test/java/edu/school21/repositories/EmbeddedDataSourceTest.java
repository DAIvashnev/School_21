package edu.school21.repositories;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.springframework.jdbc.datasource.embedded.EmbeddedDatabase;
import org.springframework.jdbc.datasource.embedded.EmbeddedDatabaseBuilder;

import java.sql.Connection;
import java.sql.SQLException;

import static org.springframework.jdbc.datasource.embedded.EmbeddedDatabaseType.HSQL;

public class EmbeddedDataSourceTest {

    EmbeddedDatabase db;

    @BeforeEach
    void init() {
        db = new EmbeddedDatabaseBuilder()
                .generateUniqueName(true)
                .setType(HSQL)
                .setScriptEncoding("UTF-8")
                .ignoreFailedDrops(true)
                .addScript("schema.sql")
                .addScript("data.sql")
                .build();
    }

    @Test
    void testConnection() {
        try {
            Connection c = db.getConnection();
            Assertions.assertNotNull(c);
            c.close();
        }
        catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
