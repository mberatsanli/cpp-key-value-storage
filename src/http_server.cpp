#include <httplib.h>
#include <json.hpp>
#include "kvstore.h"
#include <iostream>

using json = nlohmann::json;

class KVStoreServer {
public:
    KVStoreServer(const std::string& db_path, int port) 
        : store(db_path), port(port) {}

    void start() {
        httplib::Server svr;

        // GET /api/v1/kv/:key
        svr.Get("/api/v1/kv/:key", [this](const httplib::Request& req, httplib::Response& res) {
            try {
                const std::string& key = req.path_params.at("key");
                std::string value = store.get(key);
                
                json response = {
                    {"key", key},
                    {"value", value}
                };
                
                res.set_content(response.dump(), "application/json");
            } catch (const std::exception& e) {
                json error = {{"error", e.what()}};
                res.status = 404;
                res.set_content(error.dump(), "application/json");
            }
        });

        // PUT /api/v1/kv/:key
        svr.Put("/api/v1/kv/:key", [this](const httplib::Request& req, httplib::Response& res) {
            try {
                const std::string& key = req.path_params.at("key");
                json body = json::parse(req.body);
                
                if (!body.contains("value")) {
                    throw std::runtime_error("Missing 'value' in request body");
                }
                
                std::string value = body["value"];
                store.put(key, value);
                
                json response = {
                    {"status", "success"},
                    {"key", key},
                    {"value", value}
                };
                
                res.set_content(response.dump(), "application/json");
            } catch (const std::exception& e) {
                json error = {{"error", e.what()}};
                res.status = 400;
                res.set_content(error.dump(), "application/json");
            }
        });

        // DELETE /api/v1/kv/:key
        svr.Delete("/api/v1/kv/:key", [this](const httplib::Request& req, httplib::Response& res) {
            try {
                const std::string& key = req.path_params.at("key");
                store.remove(key);
                
                json response = {
                    {"status", "success"},
                    {"key", key}
                };
                
                res.set_content(response.dump(), "application/json");
            } catch (const std::exception& e) {
                json error = {{"error", e.what()}};
                res.status = 404;
                res.set_content(error.dump(), "application/json");
            }
        });

        std::cout << "Server starting on port " << port << "..." << std::endl;
        svr.listen("0.0.0.0", port);
    }

private:
    KVStore store;
    int port;
};

int main(int argc, char* argv[]) {
    try {
        int port = 8080;
        if (argc > 1) {
            port = std::stoi(argv[1]);
        }

        std::string db_path = "./data";
        if (argc > 2) {
            db_path = argv[2];
        }

        KVStoreServer server(db_path, port);
        server.start();
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
} 