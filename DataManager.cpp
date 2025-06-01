#include "DataManager.hpp"



DataManager::DataManager () : fs(DATA_PATH) {
      loadData();
      determineDifficulity();
}

void DataManager::loadData () {
      std::string year, month, day, pm25String;
      getline(fs, year, ',');
      getline(fs, month, ',');
      getline(fs, day, ',');
      getline(fs, pm25String);
      
      date = year + "/" + month + "/" + day;
      pm25 = std::stoi(pm25String);
}

Difficulity DataManager::determineDifficulity () {
      if (0 <= pm25 && pm25 < 15.4) {
            return Difficulity::easy;
      } else if (15.4 <= pm25 && pm25 < 35.4) {
            return Difficulity::midium;
      } else if (35.4 <= pm25 && pm25 < 54.4) {
            return Difficulity::hard;
      } else if (54.4 <= pm25) {
            return Difficulity::very_hard;
      } else {
            return Difficulity::easy;
      }
}