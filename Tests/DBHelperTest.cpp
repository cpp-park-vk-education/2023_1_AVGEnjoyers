#include <gtest/gtest.h>
#include <pqxx/pqxx>
#include <memory>
#include <string>
#include <vector>
#include "../DBHelper/DBHelper.h"
#include "../Flat/Flat.h"
#include "../SmartLock/SmartLock.h"
#include "../User/User.h"

TEST(DBHelperTest, GetFlatTest) {
  // Arrange
  DBHelper db_helper(HOST, PORT, DBNAME, USER, PASSWORD);
  std::unique_ptr<FLat> flatItem = std::make_unique<FLat>(1000, 50, 1, 1, "Test Address", "Test Description");
  db_helper.saveFlat(std::move(flatItem));

  // Act
  FLat resultFlat = db_helper.getFlat(1);
  boost::property_tree::ptree actualJson = resultFlat.getJson();

  EXPECT_EQ(flatItem->getJson(), actualJson);
}

TEST(DBHelperTest, FlatUpdate) {
  // Arrange
  DBHelper db_helper(HOST, PORT, DBNAME, USER, PASSWORD);
  std::unique_ptr<FLat> flatItem = std::make_unique<FLat>(1000, 50, 1, 1, "Test Address", "Test Description");
  db_helper.saveFlat(std::move(flatItem));

  std::unique_ptr<FLat> flatItemUp = std::make_unique<FLat>(3000, 50, 1, 1, "Test Address", "Test Description");
  db_helper.updateFlat(1, std::move(flatItemUp));

  // Act
  FLat resultFlat = db_helper.getFlat(1);
  boost::property_tree::ptree actualJson = resultFlat.getJson();

  EXPECT_EQ(flatItemUp->getJson(), actualJson);
}

TEST(DBHelperTest, GetFlatsListTest) {
  // Arrange
  DBHelper db_helper(HOST, PORT, DBNAME, USER, PASSWORD);
  std::vector<std::unique_ptr<FLat>> flatItems;
  for (int i = 1; i <= 10; ++i) {
    std::unique_ptr<FLat> flatItem = std::make_unique<FLat>(i * 1000, i * 50, i, i, "Test Address " + std::to_string(i), "Test Description " + std::to_string(i));
    flatItems.push_back(std::move(flatItem));
  }
  for (auto& flatItem : flatItems) {
    db_helper.saveFlat(std::move(flatItem));
  }

  // Act
  std::vector<FLat> resultFlats = db_helper.getFlatsList(0, 5);

  // Assert
  EXPECT_EQ(resultFlats.size(), 5);
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(resultFlats[i].getJson(), flatItems[i]->getJson());
  }
}

TEST(DBHelperTest, GetLock) {
  // Arrange
  DBHelper db_helper(HOST, PORT, DBNAME, USER, PASSWORD);

  // Add a SmartLock to the database
  std::unique_ptr<SmartLock> lockItem = std::make_unique<SmartLock>();
  db_helper.saveLock(std::move(lockItem));

  // Act
  SmartLock retrievedLock = db_helper.getLock(1);

  // Assert
  EXPECT_EQ(retrievedLock.is_open(), true);
}

TEST(DBHelperTest, updateLock) {
  // Arrange
  DBHelper db_helper(HOST, PORT, DBNAME, USER, PASSWORD);

  // Add a SmartLock to the database
  std::unique_ptr<SmartLock> lockItem = std::make_unique<SmartLock>();
  std::unique_ptr<SmartLock> lockItemUp = std::make_unique<SmartLock>();
  db_helper.saveLock(std::move(lockItem));
  db_helper.updateLock(1, std::move(lockItemUp));
  // Act
  SmartLock retrievedLock = db_helper.getLock(1);

  // Assert
  EXPECT_EQ(retrievedLock.is_open(), lockItemUp->is_open());
}

TEST(DBHelperTest, GetUser) {
  // Arrange
  DBHelper db_helper(HOST, PORT, DBNAME, USER, PASSWORD);

  // Add a User to the database
  std::unique_ptr<User> userItem = std::make_unique<User>(1, "John", "Doe", "123456789", "johndoe@mail.ru");
  db_helper.saveUser(std::move(userItem));

  // Act
  User retrievedUser = db_helper.getUser(1);

  // Assert
  EXPECT_EQ(retrievedUser.getJson(), userItem->getJson());
}

TEST(DBHelperTest, UpdateUser) {
  // Arrange
  DBHelper db_helper(HOST, PORT, DBNAME, USER, PASSWORD);

  // Add a User to the database
  std::unique_ptr<User> userItem = std::make_unique<User>(1, "John", "Doe", "123456789", "johndoe@mail.ru");
  db_helper.saveUser(std::move(userItem));

  //Update User
  std::unique_ptr<User> userItemUp = std::make_unique<User>(1, "Sasha", "Qwe", "123456789", "johndoe@mail.ru");
  db_helper.updateUser(1, std::move(userItem));
  // Act

  User retrievedUser = db_helper.getUser(1);

  // Assert
  EXPECT_EQ(retrievedUser.getJson(), userItemUp->getJson());
}




