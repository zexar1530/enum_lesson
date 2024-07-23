﻿#include"SqlSelectQueryBuilder.h"
#include <iostream>
#include<assert.h>

int main()
{
    SqlSelectQueryBuilder query_builder;
    query_builder.AddColum("name").AddColum("phone");
    query_builder.AddFrom("students");
    query_builder.AddWhere("id", "42").AddWhere("name", "John");

    assert(query_builder.BuildQuery() == "SELECT name, phone FROM students WHERE id=42 AND name=John; ");

    return 0;
}

