#include "cards.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <time.h>

int main()
{
	srand(time(NULL));

	Player player(100);
	Player dealer(900);

	Hand hand_player = Hand();
	Hand hand_dealer = Hand();

	std::string playon = "y";

	while (player.get_cash() > 0 && dealer.get_cash() > 0)
	{
		
		hand_player.clear();
		hand_dealer.clear();

		std::cout << "You have $" << player.get_cash() << ". Enter bet: ";
		int bet; std::cin >> bet;
		while (bet < 1 || bet > player.get_cash()) //checks that the bet is valid
		{
			std::cout << "Sorry. Please enter a valid bet: ";
			std::cin >> bet;
		}

		hand_player.add_card();
		std::cout << "Your cards: \n";
		hand_player.print();
		std::cout << "Your total is " << hand_player.get_value() << ". Do you want another card? (y/n) ";
		std::cin >> playon;
		while (playon == "y")
		{
			hand_player.add_card();
			std::cout << "New card:\n";
			hand_player.print_new_card();
			std::cout << "\nYour cards: \n";
			hand_player.print();
			std::cout << "Your total is " << hand_player.get_value() << ".\n";
			if (hand_player.get_value() > 7.5)
				std::cout << "You busted.";
			else
			{
				std::cout << "Do you want another card? (y/n) ";
				std::cin >> playon;
			}
		}

		if (hand_player.get_value() > 7.5)
		{
			player.lose(bet);
			dealer.win(bet);
			std::cout << "Sorry, you lost " << bet << ". ";
		}
		else
		{
			hand_dealer.add_card();
			std::cout << "Dealer's cards:";
			hand_dealer.print();
			std::cout << "The dealer's total is " << hand_dealer.get_value() << ".\n";
			while (hand_dealer.get_value() < 5.5)
			{
				hand_dealer.add_card();
				std::cout << "New card:\n";
				hand_dealer.print_new_card();
				std::cout << "\nDealer's cards:";
				hand_dealer.print();
				std::cout << "The dealer's total is " << hand_dealer.get_value() << ".\n";
			}

			if (hand_dealer.get_value() > 7.5) // dealer busts
			{
				player.win(bet);
				dealer.lose(bet);
				std::cout << "You win " << bet << "!";
			}
			else if (hand_dealer.get_value() > hand_player.get_value()) // no one busts but dealer is better
			{
				player.lose(bet);
				dealer.win(bet);
				std::cout << "Sorry, you lost " << bet << ". ";
			}
			else // no one busts and you are better
			{
				player.win(bet);
				dealer.lose(bet);
				std::cout << "You win " << bet << "!";
			}
		}

	}

	if (player.get_cash() > 0)
		std::cout << "Congratulations, you beat the casino!\n\nBye!";
	else
		std::cout << "You have no more money... Hit the road jack.";

	return 0;
}