#include <iostream>
#include <string>
#include <locale>
#include <ctime>
#include <cstdlib>

struct Card {
    std::string name;
    int value;

    Card(const std::string cardName, int cardValue) : name(cardName), value(cardValue) {}
};

struct Player {
    std::string name;
    double balance;

    Player(const std::string playerName, double playerBalance) : name(playerName), balance(playerBalance) {}
};

void printGameStatus(const Player& player, const Player& dealer) {
    std::cout << "~~~~~> Статус игры <~~~~~" << std::endl;
    std::cout << "Ваше имя: " << player.name << std::endl;
    std::cout << "Ваш текущий баланс: " << player.balance << " USD" << std::endl;
    std::cout << "Дилер: " << dealer.name << std::endl;
    std::cout << "Баланс дилера: " << dealer.balance << " USD" << std::endl;
}

int main() {
    std::locale::global(std::locale("Russian"));

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    Card cards[52] = {
        {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5},
        {"6", 6}, {"7", 7}, {"8", 8}, {"9", 9},
        {"10", 10}, {"Jack", 10}, {"Queen", 10}, {"King", 10},
        {"Ace", 11}, {"2", 2}, {"3", 3}, {"4", 4},
        {"5", 5}, {"6", 6}, {"7", 7}, {"8", 8},
        {"9", 9}, {"10", 10}, {"Jack", 10}, {"Queen", 10},
        {"King", 10}, {"Ace", 11}, {"2", 2}, {"3", 3},
        {"4", 4}, {"5", 5}, {"6", 6}, {"7", 7},
        {"8", 8}, {"9", 9}, {"10", 10}, {"Jack", 10},
        {"Queen", 10}, {"King", 10}, {"Ace", 11}, {"2", 2},
        {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6},
        {"7", 7}, {"8", 8}, {"9", 9}, {"10", 10},
        {"Jack", 10}, {"Queen", 10}, {"King", 10}, {"Ace", 11}
    };

    std::cout << "~~~~~> Добро пожаловать в Black Jack <~~~~~" << std::endl;
    std::string playerName;
    std::cout << "Введите ваше имя: ";
    std::cin >> playerName;

    std::string choice;

    Player player(playerName, 4.00);
    Player dealer("Дилер", 10.00);

    while (player.balance != 0 && dealer.balance != 0) {
        std::cout << "Желаете ли вы сыграть в партию? (Y-yes/N-no)" << std::endl;
        std::cin >> choice;

        if (choice != "Y") {
            break;
        }

        double stake;

        do {
            printGameStatus(player, dealer);

            std::cout << "Выберите вашу ставку (мин. ставка 1 USD): ";
            std::cin >> stake;

            if (stake < 1.00) {
                std::cout << "Минимальная ставка должна быть 1 USD." << std::endl;
            }

        } while (stake < 1.00);

        player.balance = player.balance - stake;

        int totalPointsPlayer = 0;
        int totalPointsDealer = 0;
        int randomIndex1 = std::rand() % 52;
        int randomIndex2 = std::rand() % 52;
        totalPointsPlayer += cards[randomIndex1].value + cards[randomIndex2].value;

        std::cout << "Ваши карты: " << cards[randomIndex1].name << "," << cards[randomIndex2].name << std::endl;
        std::cout << "Ваши текущие очки: " << totalPointsPlayer << std::endl;
        std::cout << "Ваша текущая ставка: " << stake << " USD" << std::endl;

        while (true) {
            std::cout << "Хотите взять еще карту? (Y-yes/N-no)" << std::endl;
            std::cin >> choice;

            if (choice != "Y") {
                break;
            }

            int randomIndex = std::rand() % 52;
            totalPointsPlayer += cards[randomIndex].value;

            std::cout << "Вы получили дополнительную карту: " << cards[randomIndex].name << std::endl;
            std::cout << "Ваши текущие очки: " << totalPointsPlayer << std::endl;

            if (totalPointsPlayer > 21) {
                std::cout << "Вы перебрали! Вы проиграли." << std::endl;
                dealer.balance += stake;
                break;
            }
        }

        if (totalPointsPlayer <= 21) { 
            while (totalPointsDealer < totalPointsPlayer) {
                int randomIndex = std::rand() % 52;
                totalPointsDealer += cards[randomIndex].value;

                std::cout << "Дилер взял дополнительную карту: " << cards[randomIndex].name << std::endl;
            }
        }

        std::cout << "Ваши окончательные очки: " << totalPointsPlayer << std::endl;
        std::cout << "Очки дилера: " << totalPointsDealer << std::endl;

        if (totalPointsDealer > 21 || (totalPointsPlayer <= 21 && totalPointsPlayer >= totalPointsDealer)) {
            std::cout << "Вы выиграли!" << std::endl;
            player.balance += stake * 2;
            dealer.balance -= stake;
        }
        else if (totalPointsPlayer == totalPointsDealer) {
            std::cout << "Ничья!" << std::endl;
            player.balance += stake;
        }
        else {
            std::cout << "Вы проиграли." << std::endl;
            dealer.balance += stake;
        }

        printGameStatus(player, dealer);
    }

    std::cout << "Игра завершена. Ваш баланс или баланс дилера стали равны 0." << std::endl;

    return 0;
}
