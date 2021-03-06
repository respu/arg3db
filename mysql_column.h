#ifndef ARG3_DB_MYSQL_COLUMN_H_
#define ARG3_DB_MYSQL_COLUMN_H_

#include <mysql/mysql.h>
#include "column.h"

namespace arg3
{
    namespace db
    {

        /*!
         * a sqlite specific implementation of a column
         */
        class mysql_column : public column_impl
        {
        private:
            MYSQL_ROW value_;
            MYSQL_RES *res_;
            size_t index_;
            void assert_value() const throw (no_such_column_exception);
        public:

            mysql_column(MYSQL_RES *res, MYSQL_ROW pValue, size_t index);
            mysql_column(const mysql_column &other);
            mysql_column(mysql_column &&other);
            virtual ~mysql_column();
            mysql_column &operator=(const mysql_column &other);
            mysql_column &operator=(mysql_column && other);

            bool is_valid() const;

            sql_blob to_blob() const;

            double to_double() const;

            int to_int() const;

            bool to_bool() const;

            int64_t to_int64() const;

            string to_string() const;

            sql_value to_value() const;

            int type() const;

        };

        class mysql_stmt_column : public column_impl
        {
        private:
            MYSQL_BIND *value_;
            void assert_value() const throw (no_such_column_exception);
        public:

            mysql_stmt_column(MYSQL_BIND *pValue);
            mysql_stmt_column(const mysql_stmt_column &other);
            mysql_stmt_column(mysql_stmt_column &&other);
            virtual ~mysql_stmt_column();
            mysql_stmt_column &operator=(const mysql_stmt_column &other);
            mysql_stmt_column &operator=(mysql_stmt_column && other);

            bool is_valid() const;

            sql_blob to_blob() const;

            double to_double() const;

            int to_int() const;

            bool to_bool() const;

            int64_t to_int64() const;

            string to_string() const;

            sql_value to_value() const;

            int type() const;

        };
    }
}

#endif
