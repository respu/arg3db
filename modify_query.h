/*!
 * @copyright ryan jennings (arg3.com), 2013 under LGPL
 */
#ifndef _ARG3_DB_MODIFY_QUERY_H_
#define _ARG3_DB_MODIFY_QUERY_H_

#include "base_query.h"
#include "sqldb.h"

namespace arg3
{
    namespace db
    {

        class modify_query : public base_query
        {
        public:
            modify_query(const sqldb &db, const string &tableName, const vector<string> &columns);

            modify_query(const sqldb &db, const string &tableName);

            string to_string() const;

            bool execute(bool batch = false);
        };

    }
}

#endif