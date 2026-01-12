#include <iostream>
#include <string>

class Database {
public:
    virtual ~Database() = default;
    virtual void Query(const std::string& sql) = 0;
};

class RealDatabase : public Database {
public:
    void Query(const std::string& sql) override {
        std::cout << "Executing query: " << sql << "\n";
    }
};

class DatabaseProxy : public Database {
private:
    RealDatabase realDatabase;
    bool hasAccess;
    
public:
    DatabaseProxy(bool access) : hasAccess(access) {}
    
    void Query(const std::string& sql) override {
        if (hasAccess) {
            realDatabase.Query(sql);
        } else {
            std::cout << "Access denied. Query cannot be executed.\n";
        }
    }
};

int main() {
    DatabaseProxy userDb(false);
    DatabaseProxy adminDb(true);
    
    userDb.Query("SELECT * FROM users");
    adminDb.Query("SELECT * FROM users");
    
    return 0;
}
