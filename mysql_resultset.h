#ifndef ARG3_DB_MYSQL_RESULTSET_H_
#define ARG3_DB_MYSQL_RESULTSET_H_

#include <mysql/mysql.h>
#include "resultset.h"

namespace arg3
{
    namespace db
    {

        class mysql_db;

        /*!
         * a sqlite specific implmentation of a result set
         */
        class mysql_resultset : public resultset_impl
        {
            friend class select_query;
            friend class row;
            friend class sqldb;
            friend class resultset_iterator;
        private:
            MYSQL_RES *res_;
            MYSQL_ROW row_;
            mysql_db *db_;
            unsigned *refcount_;
        public:
            mysql_resultset(mysql_db *db, MYSQL_RES *res);

            mysql_resultset(const mysql_resultset &other);
            mysql_resultset(mysql_resultset &&other);
            virtual ~mysql_resultset();

            mysql_resultset &operator=(const mysql_resultset &other);
            mysql_resultset &operator=(mysql_resultset && other);

            bool is_valid() const;

            row current_row();

            void reset();

            bool next();

            size_t column_count() const;
        };

        class mysql_stmt_resultset : public resultset_impl
        {
            friend class select_query;
            friend class row;
            friend class sqldb;
            friend class resultset_iterator;
        private:
            MYSQL_STMT *stmt_;
            MYSQL_RES *metadata_;
            mysql_db *db_;
            MYSQL_BIND *bindings_;
            size_t columnCount_;
            unsigned *refcount_;
            int status_;
            void get_results();
        public:
            mysql_stmt_resultset(mysql_db *db, MYSQL_STMT *stmt);

            mysql_stmt_resultset(const mysql_stmt_resultset &other);
            mysql_stmt_resultset(mysql_stmt_resultset &&other);
            virtual ~mysql_stmt_resultset();

            mysql_stmt_resultset &operator=(const mysql_stmt_resultset &other);
            mysql_stmt_resultset &operator=(mysql_stmt_resultset && other);

            bool is_valid() const;

            row current_row();

            void reset();

            bool next();

            size_t column_count() const;
        };
    }
}

#endif
