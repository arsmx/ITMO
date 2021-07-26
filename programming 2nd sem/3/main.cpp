#include "pugixml.cpp"
#include <iostream>
#include <vector>

using namespace std;

class Data {
private:
    string vehicleType;
    string station; // улица, на которой остановка
    vector<string> routesList;

    struct {
        float latitude; // широта
        float longitude; // долгота
    } stationCoords;

public:
    Data(string type, string stationName, string routes, string coords) :
            vehicleType(type), station(stationName) {
        int startScan = 0;
        for (int i = 0; i <= routes.length(); i++) // сканируем строку маршрутов, разделяем . ,
            if (routes[i] == '.' || routes[i] == ',' || i == routes.length()) {
                routesList.push_back(routes.substr(startScan, i - startScan));
                startScan = i + 1;
            }

        int midScan = coords.find(","); // сохраняем позицию запятой
        stationCoords.latitude = stof(coords.substr(0, midScan)); // широта
        stationCoords.longitude = stof(coords.substr(midScan + 1)); // долгота
    }

    friend void Task1(const vector<Data> &dataList);

    friend void Task2(const vector<Data> &dataList);

    friend void Task3(const vector<Data> &dataList);

    friend void routesCount(Data const &element, vector<pair<string, int>> &routes);

    ~Data() = default;
};

struct routeStructure {
    string type, routeName;
    float routeLength;
    vector<pair<float, float>> routeStationCoords;
};

struct streetStructure {
    string streetName;
    int stationsCount;
    vector<string> routesList;
};

int existRoute(string route, vector<pair<string, int>> &data) {
    for (int i = 0; i < data.size(); i++)
        if (data[i].first == route)
            return i;
    return -1;
}

int existRoute(string route, vector<routeStructure> &data) {
    for (int i = 0; i < data.size(); i++)
        if (data[i].routeName == route)
            return i;
    return -1;
}

bool existRoute(string route, struct streetStructure &data) {
    for (int i = 0; i < data.routesList.size(); i++) {
        if (data.routesList[i] == route)
            return true;
    }
    return false;
}

int existStreet(string street, vector<streetStructure> &data) {
    for (int i = 0; i < data.size(); i++)
        if (data[i].streetName == street)
            return i; // выводим номер улицы, если нашли, иначе -1
    return -1;
}

int maximum(vector<pair<string, int>> &list) {
    int max = 0;
    int maxPos = 0;
    for (int i = 0; i < list.size(); i++) // проходим весь список маршрутов
        if (list[i].second > max) {
            max = list[i].second;
            maxPos = i; // сохраняем остановку с самым большим кол-вом маршрутов
        }
    return maxPos;
}

void routesCount(Data const &element, vector<pair<string, int>> &routes) {
    for (int j = 0; j < element.routesList.size(); j++) {
        int routePosition = existRoute(element.routesList[j], routes);
        if (routePosition == -1) // создаем остановку и один маршрут
            routes.push_back(make_pair(element.routesList[j], 1));
        else // прибавляем маршрут к уже существующей остановке
            routes[routePosition].second++;
    }
}

void Task1(const vector<Data> &dataList) {
    vector<pair<string, int>> BusRoutes; // маршрут, кол-во остановок
    vector<pair<string, int>> TramRoutes;
    vector<pair<string, int>> TrolleyRoutes;

    for (int i = 0; i < dataList.size(); i++) {

        if (dataList[i].vehicleType == "Автобус")
            routesCount(dataList[i], BusRoutes);

        if (dataList[i].vehicleType == "Трамвай")
            routesCount(dataList[i], TramRoutes);

        if (dataList[i].vehicleType == "Троллейбус")
            routesCount(dataList[i], TrolleyRoutes);
    }

    cout << "1. Маршрут с наибольшим количеством остановок по отдельным видам транспорта" << endl;
    cout << "Автобус: " << BusRoutes[maximum(BusRoutes)].first << " остановок\n";
    cout << "Трамвай: " << TramRoutes[maximum(TramRoutes)].first << " остановок\n";
    cout << "Троллейбус: " << TrolleyRoutes[maximum(TrolleyRoutes)].first << " остановок\n\n";
}

void Task2(const vector<Data> &dataList) {
    vector<routeStructure> routeScheme;

    for (int i = 0; i < dataList.size(); i++) // для каждой остановки
        for (int j = 0; j < dataList[i].routesList.size(); j++) { // каждый проходящий через нее маршрут
            int routePosition = existRoute(dataList[i].routesList[j], routeScheme);
            routeStructure tempRoute;

            if (routePosition == -1) { // если в списке еще нет маршрута, то записываем
                tempRoute.routeName = dataList[i].routesList[j];
                tempRoute.type = dataList[i].vehicleType;
                tempRoute.routeLength = 0; // дописываем координаты
                tempRoute.routeStationCoords.push_back(
                        make_pair(dataList[i].stationCoords.latitude, dataList[i].stationCoords.longitude));
                routeScheme.push_back(tempRoute);
            } else // иначе дописываем координаты в существующий маршрут
                routeScheme[routePosition].routeStationCoords.push_back(
                        make_pair(dataList[i].stationCoords.latitude, dataList[i].stationCoords.longitude));
        }

    float maxLengthBus = 0, maxLengthTram = 0, maxLengthTrolley = 0;
    int maxPosBus = -1, maxPosTram = -1, maxPosTrolley = -1;

    for (int i = 0; i < routeScheme.size(); i++) { // проходим все остановки
        float routeLength = 0;
        bool checkedStations[routeScheme[i].routeStationCoords.size()][routeScheme[i].routeStationCoords.size()];

        for (int y = 0; y < routeScheme[i].routeStationCoords.size(); y++)
            for (int z = 0; z < routeScheme[i].routeStationCoords.size(); z++)
                checkedStations[y][z] = false; // заполняем массив непроверенных остановок

        for (int j = 0; j < routeScheme[i].routeStationCoords.size() - 1; j++) {
            float nextStationLength = INT32_MAX;
            int nextStationPosition = -1;

            for (int k = 0; k < routeScheme[i].routeStationCoords.size(); k++) {
                if (k == j) continue;
                if (checkedStations[j][k] || checkedStations[k][j]) continue;

                float distance = sqrt(
                        pow(routeScheme[i].routeStationCoords[j].first - routeScheme[i].routeStationCoords[k].first,
                            2) +
                        pow(routeScheme[i].routeStationCoords[j].second - routeScheme[i].routeStationCoords[k].second,
                            2));

                if (distance < nextStationLength) {
                    nextStationLength = distance; // записываем расстояние до соседней станции
                    nextStationPosition = k;
                }
            }

            if (nextStationLength == INT32_MAX) // обнуляем расстояние, если нет соседней станции
                nextStationLength = 0;
            routeLength += nextStationLength;

            checkedStations[j][nextStationPosition] = true;
            checkedStations[nextStationPosition][j] = true;
        }

        if (routeScheme[i].type == "Автобус" and routeLength > maxLengthBus) {
            maxLengthBus = routeLength;
            maxPosBus = i;
        }
        if (routeScheme[i].type == "Трамвай" and routeLength > maxLengthTram) {
            maxLengthTram = routeLength;
            maxPosTram = i;
        }
        if (routeScheme[i].type == "Троллейбус" and routeLength > maxLengthTrolley) {
            maxLengthTrolley = routeLength;
            maxPosTrolley = i;
        }

        routeScheme[i].routeLength = routeLength;
    }

    cout << "2. Наиболее длинный маршрут (основываясь на координатах) по отдельным видам транспорта \n";
    cout << "Автобус: " << routeScheme[maxPosBus].routeName << " Протяженность: " << maxLengthBus*111 << " км\n";
    cout << "Трамвай: " << routeScheme[maxPosTram].routeName << " Протяженность: " << maxLengthTram*111 << " км\n";
    cout << "Троллейбус: " << routeScheme[maxPosTrolley].routeName << " Протяженность: " << maxLengthTrolley*111
         << " км\n\n";
}

void Task3(const vector<Data> &dataList) {
    vector<streetStructure> stationsCount;

    for (int i = 0; i < dataList.size(); i++) {
        int streetPosition = -1; // разделитель - запятая
        streetPosition = dataList[i].station.find(",");

        if (streetPosition == -1) { // если запятой нет
            int streetPosition = existStreet(dataList[i].station, stationsCount); // если нет в списке, заносим в него через временный

           if (streetPosition == -1) {
                streetStructure streetTemp;
                streetTemp.streetName = dataList[i].station;

                for (int j = 0; j < dataList[i].routesList.size(); j++)
                    streetTemp.routesList.push_back(dataList[i].routesList[j]);

                stationsCount.push_back(streetTemp);
            } else {
                for (int j = 0; j < dataList[i].routesList.size(); j++)
                    if (!existRoute(dataList[i].routesList[j], stationsCount[streetPosition]))
                        stationsCount[streetPosition].routesList.push_back(dataList[i].routesList[j]);
            }

        } else {
            string firstStreet = dataList[i].station.substr(0, streetPosition);
            string secondStreet = dataList[i].station.substr(streetPosition + 2);
            int streetPositionFirst = existStreet(firstStreet, stationsCount);
            int streetPositionSecond = existStreet(secondStreet, stationsCount);

            if (streetPositionFirst == -1) {
                streetStructure streetTemp;
                streetTemp.streetName = firstStreet;

                for (int j = 0; j < dataList[i].routesList.size(); j++)
                    streetTemp.routesList.push_back(dataList[i].routesList[j]);

                stationsCount.push_back(streetTemp);
            } else {
                for (int j = 0; j < dataList[i].routesList.size(); j++)
                    if (!existRoute(dataList[i].routesList[j], stationsCount[streetPositionFirst]))
                        stationsCount[streetPositionFirst].routesList.push_back(dataList[i].routesList[j]);
            }

            if (streetPositionSecond == -1) {
                streetStructure streetTemp;
                streetTemp.streetName = secondStreet;

                for (int j = 0; j < dataList[i].routesList.size(); j++)
                    streetTemp.routesList.push_back(dataList[i].routesList[j]);

                stationsCount.push_back(streetTemp);
            } else {
                for (int j = 0; j < dataList[i].routesList.size(); j++)
                    if (!existRoute(dataList[i].routesList[j], stationsCount[streetPositionSecond]))
                        stationsCount[streetPositionSecond].routesList.push_back(dataList[i].routesList[j]);
            }
        }
    }

    int maxStationsCount = 0;
    int maxStationsPos = -1;

    for (int i = 0; i < stationsCount.size(); i++) {
        if (stationsCount[i].streetName == "") continue;

        if (stationsCount[i].routesList.size() > maxStationsCount) {
            maxStationsCount = stationsCount[i].routesList.size();
            maxStationsPos = i;
        }
    }

    cout << "3. Улица с наибольшим числом остановок: " << stationsCount[maxStationsPos].streetName
         << ", остановок: " << stationsCount[maxStationsPos].routesList.size();
}


int main() {
    system("chcp 65001");
    cout << "\n";
    pugi::xml_document doc; // DAO
    pugi::xml_parse_result resultData = doc.load_file("data.xml");
    vector<Data> dataList;

    for (const auto &childElement : doc.child("dataset")) {
        dataList.push_back(Data(
                (string) childElement.child("type_of_vehicle").child_value(),
                childElement.child("location").child_value(),
                (string) childElement.child("routes").child_value(),
                (string) childElement.child("coordinates").child_value())
        );
    }
    Task1(dataList);
    Task2(dataList);
    Task3(dataList);
	return 0;
}