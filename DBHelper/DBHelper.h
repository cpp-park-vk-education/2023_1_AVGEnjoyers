//
// Update by SashaD on 16.04.23.
//

#ifndef BACKEND_CPP_DBHELPER_H
#define BACKEND_CPP_DBHELPER_H
#include <vector>
#include <memory>
#include "../Flat/Flat.h"
#include "../SmartLock/SmartLock.h"
#include "../User/User.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <string>
#include <iostream>
#include <pqxx/pqxx>

#define HOST "localhost"
#define PORT "5432"
#define DBNAME "FlatSharingDB"
#define USER "flat"
#define PASSWORD "123"

class DBHelper {
 private:
  pqxx::connection* _connection;

 public:
  DBHelper(std::string host, std::string port, std::string dbname,
           std::string user, std::string password);

  ~DBHelper();

  void saveFlat(std::unique_ptr<FLat> flatItem);
  void updateFlat(size_t flatId, std::unique_ptr<FLat> flatItemUp);
  FLat getFlat(size_t flatId);
  std::vector<FLat> getFlatsList(size_t offset, size_t amount);
  void saveLock(std::unique_ptr<SmartLock> lockItem);
  SmartLock getLock(size_t lockId);
  void updateLock(size_t lockId, std::unique_ptr<SmartLock> slItem);
  User getUser(size_t userId);
  void saveUser(std::unique_ptr<User> userItem);
  void updateUser(size_t userId, std::unique_ptr<User> userItemUp);
  
};

#endif  // BACKEND_CPP_DBHELPER_H
