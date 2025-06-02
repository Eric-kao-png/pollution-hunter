#include "DataManager.hpp"

DataManager::DataManager () : fs(DATA_PATH) {
      loadData();
      difficulty = determineDifficulty();
}

void DataManager::loadData () {
      std::string dataString;
      getline(fs, dataString);

      std::istringstream iss(dataString);
      std::string year, month, day;
      getline(iss, year, ',');
      getline(iss, month, ',');
      getline(iss, day, ',');
      iss >> pm25;
      
      date = year + "/" + month + "/" + day;
}

Difficulty DataManager::determineDifficulty () {
      if (0 <= pm25 && pm25 < 15.4) {
            return Difficulty::easy;
      } else if (15.4 <= pm25 && pm25 < 35.4) {
            return Difficulty::midium;
      } else if (35.4 <= pm25 && pm25 < 54.4) {
            return Difficulty::hard;
      } else if (54.4 <= pm25) {
            return Difficulty::very_hard;
      } else {
            return Difficulty::easy;
      }
}