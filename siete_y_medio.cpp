#include "cards.h"
#include <iostream>
#include <string>



int main()
{
	Player player(100);
	Player dealer(900);

	Hand hand_player = Hand();
	Hand hand_dealer = Hand();

	bool play_again = true;
	std::string playon = "y";

	while (play_again)
	{

		while (playon == "y")
		{
			std::cout << "You have $" << player.get_cash() << ". Enter bet: ";
			int bet; std::cin >> bet;
			while (bet < 1 || bet > player.get_cash()) //checks that the bet is valid
			{
				std::cout << "Sorry. Please enter a valid bet: ";
				std::cin >> bet;
			}

			std::cout << "Your cards: \n";
			hand_player.print();
			std::cout << "Your total is " << hand_player.get_value() << ". Do you want another card? (y/n)";
			std::cin >> playon;
		}


	}


	return 0;
}