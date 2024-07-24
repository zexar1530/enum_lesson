#include"SqlSelectQueryBuilder.h"
#include <iostream>
#include<assert.h>

int main()
{
    SqlSelectQueryBuilder query_builder;
    //query_builder.AddColum("name").AddColum("phone");
    query_builder.AddColumn({ "name", "phone" });
    query_builder.AddFrom("students");
    //query_builder.AddWhere("id", "42").AddWhere("name", "John");
    map<string, string> where_map = {{"id", "42"}, {"name", "John"}};
    query_builder.AddWhere(where_map);

    string query{ query_builder.BuildQuery() };

    assert(query == "SELECT name, phone FROM students WHERE id=42 AND name=John; ");
    cout << query_builder.BuildQuery();

    return 0;
}

