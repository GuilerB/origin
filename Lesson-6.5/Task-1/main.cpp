#include <pqxx/pqxx>
#include <iostream>
#include <string>
#include <vector>

class Client_Base {
private:
    pqxx::connection conn;  
public:
    Client_Base(const std::string& conn_str) : conn(conn_str) {
        if (!conn.is_open()) {
            throw std::runtime_error("Connection failed");
        }
        std::cout << "Connected to database" << std::endl;
    }

    // create tables
    void createTables() {
        pqxx::work txn(conn);  
        txn.exec("CREATE TABLE IF NOT EXISTS clients ("
            "client_id SERIAL PRIMARY KEY, "
            "first_name VARCHAR(50) NOT NULL, "
            "last_name VARCHAR(50) NOT NULL, "
            "email VARCHAR(100) UNIQUE NOT NULL)");

        txn.exec("CREATE TABLE IF NOT EXISTS client_phones ("
            "phone_id SERIAL PRIMARY KEY, "
            "client_id INTEGER NOT NULL REFERENCES clients(client_id) ON DELETE CASCADE, "
            "phone_number VARCHAR(20) NOT NULL UNIQUE)");
        txn.commit();
        std::cout << "Tables created" << std::endl;
    }

    // add client
    int addClient(const std::string& fname, const std::string& lname, const std::string& email) {
        pqxx::work txn(conn);
        pqxx::result r = txn.exec(
            "INSERT INTO clients (first_name, last_name, email) "
            "VALUES ('" + txn.esc(fname) + "', '" + txn.esc(lname) + "', '" + txn.esc(email) + "') "
            "RETURNING client_id");
        int id = r[0][0].as<int>();
        txn.commit();
        std::cout << "Client added, ID: " << id << std::endl;
        return id;
    }
    // add phone
    void addPhone(int client_id, const std::string& phone) {
        pqxx::work txn(conn);
        txn.exec(
            "INSERT INTO client_phones (client_id, phone_number) "
            "VALUES (" + std::to_string(client_id) + ", '" + txn.esc(phone) + "')");
        txn.commit();
        std::cout << "Phone added" << std::endl;
    }

    // update client
    void updateClient(int client_id, const std::string& fname = "",
        const std::string& lname = "", const std::string& email = "") {
        pqxx::work txn(conn);
        std::string query = "UPDATE clients SET ";
        bool first = true;

        if (!fname.empty()) {
            query += "first_name = '" + txn.esc(fname) + "'";
            first = false;
        }
        if (!lname.empty()) {
            if (!first) query += ", ";
            query += "last_name = '" + txn.esc(lname) + "'";
            first = false;
        }
        if (!email.empty()) {
            if (!first) query += ", ";
            query += "email = '" + txn.esc(email) + "'";
        }

        query += " WHERE client_id = " + std::to_string(client_id);
        txn.exec(query);
        txn.commit();
        std::cout << "Client updated" << std::endl;
    }

    // delete phone number
    void deletePhone(int client_id, const std::string& phone) {
        pqxx::work txn(conn);
        txn.exec(
            "DELETE FROM client_phones "
            "WHERE client_id = " + std::to_string(client_id) +
            " AND phone_number = '" + txn.esc(phone) + "'");
        txn.commit();
        std::cout << "Phone deleted" << std::endl;
    }

    // delete a client
    void deleteClient(int client_id) {
        pqxx::work txn(conn);
        txn.exec("DELETE FROM clients WHERE client_id = " + std::to_string(client_id));
        txn.commit();
        std::cout << "Client deleted" << std::endl;
    }

    // delete all rows in a table
    void deleteAllRows(std::string& table) {
        pqxx::work txn(conn);
        txn.exec("DROP TABLE " + table + " CASCADE;");
        txn.commit();
        std::cout << table + " deleted" << std::endl;
    }
     
    // find clients
    void findClients(const std::string& search) {
        pqxx::work txn(conn);

        pqxx::result r = txn.exec(
            "SELECT c.client_id, c.first_name, c.last_name, c.email FROM clients c "
            "LEFT JOIN client_phones cp ON c.client_id = cp.client_id "
            "WHERE c.first_name ILIKE '%" + txn.esc(search) + "%' OR "
            "c.last_name ILIKE '%" + txn.esc(search) + "%' OR "
            "c.email ILIKE '%" + txn.esc(search) + "%' OR "
            "cp.phone_number ILIKE '%" + txn.esc(search) + "%' "
            "ORDER BY c.client_id");

        std::cout << "\nFound " << r.size() << " client(s) for '" << search << "':" << std::endl;

        for (int i = 0; i < r.size(); i++) {
            auto row = r[i];
            std::cout << "ID: " << row[0].as<int>() << std::endl;
            std::cout << "Name: " << row[1].as<std::string>() << " "
                << row[2].as<std::string>() << std::endl;
            std::cout << "Email: " << row[3].as<std::string>() << std::endl;

            pqxx::result phones = txn.exec(
                "SELECT phone_number FROM client_phones "
                "WHERE client_id = " + row[0].as<std::string>());

            std::cout << "Phones: ";
            for (int j = 0; j < phones.size(); j++) {
                if (j > 0) std::cout << ", ";
                std::cout << phones[j][0].as<std::string>();
            }
            if (phones.size() == 0) {
                std::cout << "none";
            }
            std::cout << "\n---" << std::endl;
        }

        if (r.size() == 0) {
            std::cout << "No clients found" << std::endl;
        }
    }

    // show client info
    void showClientInfo(int client_id) {
        pqxx::work txn(conn);

        pqxx::result r = txn.exec(
            "SELECT first_name, last_name, email FROM clients "
            "WHERE client_id = " + std::to_string(client_id));

        if (r.size() == 0) {
            std::cout << "Client " << client_id << " not found" << std::endl;
            return;
        }

        std::cout << "\nClient " << client_id << ":" << std::endl;
        std::cout << "Name: " << r[0][0].as<std::string>() << " "
            << r[0][1].as<std::string>() << std::endl;
        std::cout << "Email: " << r[0][2].as<std::string>() << std::endl;

        pqxx::result phones = txn.exec(
            "SELECT phone_number FROM client_phones "
            "WHERE client_id = " + std::to_string(client_id));

        std::cout << "Phones: ";
        for (int i = 0; i < phones.size(); i++) {
            if (i > 0) std::cout << ", ";
            std::cout << phones[i][0].as<std::string>();
        }
        if (phones.size() == 0) {
            std::cout << "none";
        }
        std::cout << std::endl;
    }

    // show all
    void showAllClients() {
        pqxx::work txn(conn);

        pqxx::result r = txn.exec(
            "SELECT client_id, first_name, last_name FROM clients ORDER BY client_id");

        std::cout << "\nAll clients (" << r.size() << "):" << std::endl;

        for (int i = 0; i < r.size(); i++) {
            auto row = r[i];
            std::cout << row[0].as<int>() << ". "
                << row[1].as<std::string>() << " "
                << row[2].as<std::string>() << std::endl;
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    system("chcp 1251"); // настраиваем кодировку консоли
    std::cout << "\n\n\n";

    try {

        std::string conn_str = "host=localhost port = 5432 dbname=clientdb1 user=postgres password=0";
        Client_Base mgr(conn_str);

        std::cout << "=== Client Database System ===\n" << std::endl;
       
        std::cout << "\n" << std::endl;

        // Create tables
        mgr.createTables();
        std::cout << "Tables ready" << std::endl;

        // Add clients
        std::cout << "\nAdding clients..." << std::endl;
        int id1 = mgr.addClient("Andrey", "Viktorov", "andrey@mail.com");
        std::cout << "\nAndrey added..." << std::endl;
        mgr.addPhone(id1, "+79161234567");
        std::cout << "\nAndrey phone added..." << std::endl;

        int id2 = mgr.addClient("George", "Allison", "george@mail.com");
        mgr.addPhone(id2, "+79261234567");

        // Show all
        mgr.showAllClients();

        // Search
        std::cout << "\n--- Search ---" << std::endl;
        mgr.findClients("Andrey");
        mgr.findClients("george@mail.com");
        mgr.findClients("+7916");

        // Update
        std::cout << "\n--- Update test ---" << std::endl;
        mgr.updateClient(id1, "Andrey", "Viktorov", "andrey.new@mail.com");
        mgr.showClientInfo(id1);

        // Delete a phone number
        std::cout << "\n--- Delete phone ---" << std::endl;
        mgr.deletePhone(id1, "+79161234567");
        mgr.showClientInfo(id1);

        // Delete a client
        std::cout << "\n--- Delete client  ---" << std::endl;
        mgr.deleteClient(id2);
        mgr.showAllClients();

        std::cout << "\n=== All tests passed ===" << std::endl;

        // Delete data from tables

        std::string clients = "clients";
        std::string client_phones = "client_phones";

        mgr.deleteAllRows(clients);
        mgr.deleteAllRows(client_phones);
        std::cout << "\n" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}   
    