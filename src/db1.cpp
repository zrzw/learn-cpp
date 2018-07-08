#include <iostream>
#include <sqlite3.h>

int main()
{
  sqlite3 *db;
  const char db_name[] = "test.db";
  int rc = sqlite3_open(db_name, &db);
  if(rc){
    std::cout<<"Error opening or creating database"<<std::endl;
    return -1;
  }

  sqlite3_close(db);
  return 0;
}
