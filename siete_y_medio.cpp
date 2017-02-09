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
		std::cout << "Your cards: \n\n";
		hand_player.print();
		std::cout << "Your total is " << hand_player.get_value() << ". Do you want another card? (y/n) ";
		std::cin >> playon;
		while (playon == "y")
		{
			hand_player.add_card();
			std::cout << "New card:\n\n";
			hand_player.print_new_card();
			std::cout << "Your cards: \n\n";
			hand_player.print();
			std::cout << "Your total is " << hand_player.get_value() << ".\n";
			if (hand_player.get_value() > 7.5)
			{
				std::cout << "You busted. \n";
				break;
			}
			else
			{
				std::cout << "Do you want another card? (y/n) ";
				std::cin >> playon;
			}
		}

		/**
		if (hand_player.get_value() > 7.5)
		{
			player.lose(bet);
			dealer.win(bet);
			std::cout << "Sorry, you lost " << bet << ". \n\n";
		}
		else
		{
		*/
			hand_dealer.add_card();
			std::cout << "\nDealer's cards:\n\n";
			hand_dealer.print();
			std::cout << "The dealer's total is " << hand_dealer.get_value() << ".\n";
			while (hand_dealer.get_value() < 5.5)
			{
				hand_dealer.add_card();
				std::cout << "New card:\n\n";
				hand_dealer.print_new_card();
				std::cout << "Dealer's cards:\n\n";
				hand_dealer.print();
				std::cout << "The dealer's total is " << hand_dealer.get_value() << ".\n";
			}

			if (hand_dealer.get_value() > 7.5) // dealer busts
			{
				if (hand_player.get_value() > 7.5) // both players bust so a tie is declared
				{
					player.lose(bet);
					dealer.win(bet);
					std::cout << "Both player's bust. Sorry, you lost " << bet << ". \n\n";
				}
				else
				{
					player.win(bet);
					dealer.lose(bet);
					std::cout << "You win " << bet << "! \n\n";
				}
			}
			else if (hand_player.get_value() > 7.5) // dealer didn't bust but you did
			{
				player.lose(bet);
				dealer.win(bet);
				std::cout << "Sorry, you lost " << bet << ". \n\n";
			}
			else if (hand_dealer.get_value() > hand_player.get_value()) // no one busts but dealer is better
			{
				player.lose(bet);
				dealer.win(bet);
				std::cout << "Sorry, you lost " << bet << ". \n\n";
			}
			else if (hand_dealer.get_value() < hand_player.get_value()) // no one busts and you are better
			{
				player.win(bet);
				dealer.lose(bet);
				std::cout << "You win " << bet << "! \n\n";
			}
			else // result is a tie
			{
				std::cout << "Result is a tie. No money is exchanged.\n\n";
			}
		//}

	}

	if (player.get_cash() > 0)
		std::cout << "\n\nCongratulations, you beat the casino!\n\nBye!";
	else
		std::cout << "\n\nYou have no more money... Hit the road jack.\n\n";

	return 0;
}