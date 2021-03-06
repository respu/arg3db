#ifndef ARG3_TEST_DB_H
#define ARG3_TEST_DB_H

#include "sqldb.h"
#include "base_record.h"
#include <unistd.h>
#include "sqlite3_db.h"
#include "mysql_db.h"

#define TESTDB "test.db"

class testsqlite3db : public arg3::db::sqlite3_db
{
public:
    testsqlite3db() : sqlite3_db(TESTDB)
    {
    }

    void setup()
    {
        open();
        execute("create table if not exists users(id integer primary key autoincrement, first_name varchar(45), last_name varchar(45))");
    }

    void teardown()
    {
        close();
        unlink(connection_string().c_str());
        schemas()->clear("users");
    }

    sqlite3 *rawDb()
    {
        return db_;
    }
};

class testmysqldb : public arg3::db::mysql_db
{
public:
    testmysqldb() : mysql_db("test")
    {
    }

    void setup()
    {
        open();
        execute("create table if not exists users(id integer primary key auto_increment, first_name varchar(45), last_name varchar(45))");
    }

    void teardown()
    {
        execute("delete from users");
        close();
        schemas()->clear("users");
    }

    MYSQL *rawDb()
    {
        return db_;
    }
};

extern void setup_testdb();
extern void teardown_testdb();

extern testsqlite3db testdb1;
extern testmysqldb testdb2;

extern arg3::db::sqldb *testdb;

class user : public arg3::db::base_record<user>
{
public:
    user(arg3::db::sqldb *db = testdb) : base_record(db, "users", "id") {}

    user(const arg3::db::row &values, arg3::db::sqldb *db = testdb) : base_record(db, "users", "id", values) {}

    user(long long id,  arg3::db::sqldb *db = testdb) : base_record(db, "users", "id", id) {}

    user(const user &other) : base_record(other) {}

    user(user &&other) : base_record(other) {}

    user &operator=(const user &other)
    {
        base_record<user>::operator=(other);
        return *this;
    }

    user &operator=(user && other)
    {
        base_record<user>::operator=(other);
        return *this;
    }
    string to_string()
    {
        ostringstream buf;

        buf << id() << ": " << get("first_name") << " " << get("last_name");

        return buf.str();
    }
};


#endif
