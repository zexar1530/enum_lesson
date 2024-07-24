#pragma once

#include<map>
#include<vector>
#include<string>

using namespace std;

struct BaseData {
	vector<string> where_colum;
	vector<string> name_colum;
	vector<string> date_colum;
	string name_table;
};

class SqlSelectQueryBuilder
{
private:
	//int count{};	//���������� �������;
	BaseData base;

public:
	//SqlSelectQueryBuilder() {				//��� �������� ������� ��������� *
	//	base.name_colum.push_back("*");	
	//}

	SqlSelectQueryBuilder& AddColum(const string& name_colum) {
		//if (!count)
		//	base.name_colum.pop_back();	//���� ��� ����� �� ����������� *
		//count++;	//����������� ����������
		base.name_colum.push_back(name_colum); //��������� ��� �������
		return *this;	//� ��������� ����
	}

	SqlSelectQueryBuilder& AddFrom(const string& name_table) {
		base.name_table = name_table;
		return *this;
	}

	SqlSelectQueryBuilder& AddWhere(const string& name_colum, const string& date) {
		base.where_colum.push_back(name_colum);
		base.date_colum.push_back(date);
		//count++;
		return *this;
	}

	string BuildQuery() {
		string query;
		string res_select, res_where;
		std::string result = "";

		if (!base.name_colum.empty()) {
			for (int i{}; i < base.name_colum.size(); i++) { // �������� Select
				if (i == base.name_colum.size() - 1)
					res_select = res_select + base.name_colum[i];
				else res_select = res_select + base.name_colum[i] + ", ";
			}
		}
		else res_select = "*";

		for (int i{}; i < base.where_colum.size(); i++) { //�������� Where
			if (i == base.where_colum.size() - 1)
				res_where = res_where + base.where_colum[i] + "=" + base.date_colum[i];
			else res_where = res_where + base.where_colum[i] + "=" + base.date_colum[i] + " AND ";
		}

		query = "SELECT " + res_select + " FROM " + base.name_table + " WHERE " + res_where + "; ";
		return query;	//��������� ������
	}

	SqlSelectQueryBuilder& AddWhere(const std::map<std::string, std::string>& key_val) noexcept {
		for (const auto& kv : key_val) {
			base.where_colum.push_back(kv.first);
			base.date_colum.push_back(kv.second);
		}
		return *this;
	}

	SqlSelectQueryBuilder& AddColumn(const std::vector<std::string>& columns) noexcept {
		for (const auto& column : columns)
			base.name_colum.push_back(column);
		return *this;
	}
};

