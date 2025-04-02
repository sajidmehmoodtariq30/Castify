#include "src/header/Database.h"

int main() {
    Database db;

    std::string dsn = "CastifyDSN";
    std::string user = "Sajid Mehmood";
    std::string password = "30127";

    if (db.connect(dsn, user, password)) {
        db.executeQuery("SELECT * FROM Users;");
    }

    return 0;
}
