//custom
#include "../global.h"
#include "../logger.h"
#include "../sqlite3_wrapper.h"

//std
#include <string>

sqlite3_wrapper::database DB;

class test
{
public:
	test(){}
	int call_back(int columns, char ** response, char ** column_name)
	{
		if(strcmp(response[0], "abc") != 0){
			return 1;
		}
		return 0;
	}

	int call_back_with_object(std::string * str, int columns, char ** response, char ** column_name)
	{
		if(*str != "test"){
			return 1;
		}
		if(strcmp(response[0], "abc") != 0){
			return 1;
		}
		return 0;
	}

	int call_back_with_object_reference(std::string & str, int columns, char ** response, char ** column_name)
	{
		if(str != "test"){
			return 1;
		}
		if(strcmp(response[0], "abc") != 0){
			return 1;
		}
		return 0;
	}
};

int call_back(int columns, char ** response, char ** column_name)
{
	if(strcmp(response[0], "abc") != 0){
		return 1;
	}
	return 0;
}

int call_back_with_object(std::string * str, int columns, char ** response, char ** column_name)
{
	if(*str != "test"){
		return 1;
	}
	if(strcmp(response[0], "abc") != 0){
		return 1;
	}
	return 0;
}

int call_back_with_object_reference(std::string & str, int columns, char ** response, char ** column_name)
{
	if(str != "test"){
		return 1;
	}
	if(strcmp(response[0], "abc") != 0){
		return 1;
	}
	return 0;
}

void test_call_backs()
{
	DB.query("DROP TABLE IF EXISTS sqlite3_wrapper");
	if(DB.query("CREATE TABLE sqlite3_wrapper(test_text TEXT)") != 0){
		LOGGER; exit(1);
	}
	if(DB.query("INSERT INTO sqlite3_wrapper(test_text) VALUES ('abc')") != 0){
		LOGGER; exit(1);
	}
	//function call back
	if(DB.query("SELECT test_text FROM sqlite3_wrapper", call_back) != 0){
		LOGGER; exit(1);
	}
	//function call back with object
	std::string str = "test";
	if(DB.query("SELECT test_text FROM sqlite3_wrapper", call_back_with_object, &str) != 0){
		LOGGER; exit(1);
	}
	//function call back with an object by reference
	if(DB.query("SELECT test_text FROM sqlite3_wrapper", call_back_with_object_reference, str) != 0){
		LOGGER; exit(1);
	}
	//member function call back
	test Test;
	if(DB.query("SELECT test_text FROM sqlite3_wrapper", &Test, &test::call_back) != 0){
		LOGGER; exit(1);
	}
	//member function call back with object
	if(DB.query("SELECT test_text FROM sqlite3_wrapper", &Test, &test::call_back_with_object, &str) != 0){
		LOGGER; exit(1);
	}
	//member function call back with object by reference
	if(DB.query("SELECT test_text FROM sqlite3_wrapper", &Test, &test::call_back_with_object_reference, str) != 0){
		LOGGER; exit(1);
	}
}

void test_blob_funcs()
{
	DB.query("DROP TABLE IF EXISTS sqlite3_wrapper");
	if(DB.query("CREATE TABLE sqlite3_wrapper(test_blob BLOB)") != 0){
		LOGGER; exit(1);
	}

	boost::int64_t rowid;
	rowid = DB.blob_allocate("INSERT INTO sqlite3_wrapper(test_blob) VALUES(?)", 1);
	rowid = DB.blob_allocate("UPDATE sqlite3_wrapper SET test_blob = ?", 4);
	sqlite3_wrapper::blob Blob("sqlite3_wrapper", "test_blob", rowid);
	const char * write_buff = "ABC";
	Blob.write(write_buff, 4, 0);
	char read_buff[4];
	Blob.read(read_buff, 4, 0);

	if(strcmp(write_buff, read_buff) != 0){
		LOGGER; exit(1);
	}
}

int main()
{
	test_call_backs();
	test_blob_funcs();

	return 0;
}
